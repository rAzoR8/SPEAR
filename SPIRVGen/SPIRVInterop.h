#ifndef SPEAR_SPIRVINTEROP_H
#define SPEAR_SPIRVINTEROP_H

#ifndef DONT_INCLUDE_VULKAN_HEADER
#include <vulkan/vulkan.hpp>
#endif

#include "SPIRVModule.h"
#include "Logger.h"
#include "ByteStream.h"
#include "CRC32.h"
#include "HashUtils.h"

namespace Spear
{
	//---------------------------------------------------------------------------------------------------
	inline vk::ShaderStageFlagBits GetShaderStage(const SPIRVModule& _Module)
	{
		switch (_Module.GetExectionModel())
		{
		case spv::ExecutionModelVertex: return vk::ShaderStageFlagBits::eVertex;
		case spv::ExecutionModelTessellationControl: return vk::ShaderStageFlagBits::eTessellationControl;
		case spv::ExecutionModelTessellationEvaluation: return vk::ShaderStageFlagBits::eTessellationEvaluation;
		case spv::ExecutionModelGeometry: return vk::ShaderStageFlagBits::eGeometry;
		case spv::ExecutionModelFragment: return vk::ShaderStageFlagBits::eFragment;
		case spv::ExecutionModelGLCompute: return vk::ShaderStageFlagBits::eCompute;
		case spv::ExecutionModelKernel: return vk::ShaderStageFlagBits::eCompute;
		default:
			return vk::ShaderStageFlagBits::eAll;
		}
	}
	//---------------------------------------------------------------------------------------------------

	inline vk::DescriptorType GetDescriptorType(const VariableInfo& _Var)
	{
		// TODO: CombinedImageSampler
		switch (_Var.Type.GetType())
		{
		case spv::OpTypeSampler:
			return vk::DescriptorType::eSampler;
		case spv::OpTypeImage:
			switch (_Var.Type.GetDimension())
			{
			case spv::DimSubpassData:
				return vk::DescriptorType::eInputAttachment;
				break;
			case spv::DimBuffer:
				// TODO: texel buffers
				break;
			default: // dim1d 2d 3d etc
				switch (_Var.Type.GetTexSamplerAccess())
				{
				case kTexSamplerAccess_Runtime:
					return _Var.bTexSampled ? vk::DescriptorType::eSampledImage : vk::DescriptorType::eStorageImage;
					break;
				case kTexSamplerAccess_Sampled:
					return vk::DescriptorType::eSampledImage;
					break;
				case kTexSamplerAccess_Storage:
					return vk::DescriptorType::eStorageImage;
				}
				break;
			}
			break;
		case spv::OpTypeSampledImage:
			return vk::DescriptorType::eSampledImage;
		default: // assume this is a buffer
			switch (_Var.kStorageClass)
			{
			case spv::StorageClassUniform:
			case spv::StorageClassUniformConstant:
				return vk::DescriptorType::eUniformBuffer;
			case spv::StorageClassStorageBuffer:
				return vk::DescriptorType::eStorageBuffer;
			default:
				break;
			}
			break;
		}

		HFATAL("Unsupported descriptor type");
		return vk::DescriptorType::eSampler;
	}
	//---------------------------------------------------------------------------------------------------


	// Element of a descriptor set (input)
	inline vk::DescriptorSetLayoutBinding CreateDescriptorSetLayoutBinding(const VariableInfo& _InputVar)
	{
		vk::DescriptorSetLayoutBinding Binding{};
		Binding.stageFlags = static_cast<vk::ShaderStageFlagBits>(_InputVar.uStageFlags);
		Binding.binding = _InputVar.uBinding;
		Binding.descriptorCount = _InputVar.Type.GetType() == spv::OpTypeArray ? _InputVar.Type.GetDimension() : 1u;
		Binding.descriptorType = GetDescriptorType(_InputVar);
		Binding.pImmutableSamplers = nullptr;

		return Binding;
	}

	//---------------------------------------------------------------------------------------------------
	inline vk::DescriptorSetLayout CreateDescriptorSetLayout(const std::vector<VariableInfo>& _SetVars, vk::Device _hDevice, const vk::AllocationCallbacks* _pAllocators)
	{
		vk::DescriptorSetLayoutCreateInfo Info{};
		std::vector<vk::DescriptorSetLayoutBinding> Bindings;
		
		for (const VariableInfo& Var : _SetVars)
		{		
			Bindings.push_back(CreateDescriptorSetLayoutBinding(Var));
		}

		Info.bindingCount = static_cast<uint32_t>(Bindings.size());
		Info.pBindings = Bindings.data();
		
		return _hDevice.createDescriptorSetLayout(Info, _pAllocators);
	}
	//---------------------------------------------------------------------------------------------------

	// returns hash (pImmutableSamplers excluded by default)
	inline size_t CreateDescriptorSetLayoutBindings(const std::vector<VariableInfo>& _SetVars, std::vector<vk::DescriptorSetLayoutBinding>& _OutBindings, const bool _bHashSamplerName = false)
	{
		hlx::Hasher uHash = 0u;
		for (const VariableInfo& Var : _SetVars)
		{
			vk::DescriptorSetLayoutBinding Binding = CreateDescriptorSetLayoutBinding(Var);

			uHash << Binding.binding << Binding.descriptorCount << Binding.descriptorType << (uint32_t)Binding.stageFlags;
			if (_bHashSamplerName && Var.Type.IsSampler() && Var.sName.empty() == false)
			{
				uHash << Var.sName;
			}

			_OutBindings.push_back(Binding);
		}

		return uHash;
	}
	//---------------------------------------------------------------------------------------------------

	constexpr size_t kMaxDescriptorSets = 16u;
	using TVarSet = std::vector<VariableInfo>;

	template <size_t N = kMaxDescriptorSets> // returns last used set, or -1 if empty
	inline int32_t SortIntoDescriptorSets(const SPIRVModule& _Module, std::array<TVarSet, N>& _OutDescriptorSets)
	{
		int32_t iLastSet = -1;
		for (const VariableInfo& Var : _Module.GetVariables())
		{
			switch (Var.kStorageClass)
			{
			case spv::StorageClassUniform:
			case spv::StorageClassUniformConstant:
			case spv::StorageClassImage:
			case spv::StorageClassStorageBuffer:
				break;
			default:
				continue; // skip non resource classes (incomplete list)
			}

			HASSERT(Var.uDescriptorSet < _OutDescriptorSets.size(), "Invalid descriptor set index");
			iLastSet = std::max(static_cast<int32_t>(Var.uDescriptorSet), iLastSet);

			TVarSet& Set = _OutDescriptorSets[Var.uDescriptorSet];
			
			auto it = std::find_if(Set.begin(), Set.end(), [&](const VariableInfo& _Var) {return Var.uBinding == _Var.uBinding; });
			if (it == Set.end())
			{
				Set.push_back(Var);
			}
			else
			{
				VariableInfo& OldVar = *it;
				if (OldVar.ComputeHash() == Var.ComputeHash())
				{
					OldVar.uStageFlags |= Var.uStageFlags; // concat shader usage
				}
				else
				{
					HERROR("Variable %s at binding %d of set %d does not match its previous definition [%s]", WCSTR(Var.sName), Var.uBinding, Var.uDescriptorSet, WCSTR(OldVar.sName));
				}
			}
		}

		return iLastSet;
	}
	//---------------------------------------------------------------------------------------------------

	struct SpecConstFactory
	{
		SpecConstFactory() : m_Stream(m_Data) {}

		// TODO: compute hash over stream and entries to avoid recompiling the same shader

		template <class T>
		struct Constant
		{
			friend struct SpecConstFactory;

			Constant& operator=(const T& _Value)
			{
				if (_Value != Value)
				{
					Parent.SetChangedFlag();
					Value = _Value;
				}
			}

			operator T() { return Value; }
		private:

			Constant(SpecConstFactory& _Parent) : Value(_Value), Parent(_Parent) {}
		private:
			T& Value;
			SpecConstFactory& Parent;
		};

		template <class T>
		friend struct Constant;

		template <class T>
		Constant<T> SetConstant(const T& _Value, const VariableInfo& _Var)
		{
			HASSERT(_Var.uSpecConstId != HUNDEFINED32, "Variable is not a specialization constant");
			HASSERT(_Var.Type.GetSize() != sizeof(T), "Variable size mismatch");

			vk::SpecializationMapEntry Entry{};
			Entry.constantID = _Var.uSpecConstId;
			Entry.offset = static_cast<uint32_t>(m_Stream.get_offset());
			Entry.size = static_cast<uint32_t>(sizeof(T));

			m_Entries.push_back(std::move(Entry));
			m_Stream << _Value;

			m_bChanged = true;

			return Constant<T>(*this, *reinterpret_cast<T*>(m_Stream.get_data(Entry.offset)));
		}

		vk::SpecializationInfo GetInfo() const
		{
			vk::SpecializationInfo Info{};
			Info.dataSize = static_cast<uint32_t>(m_Data.size());
			Info.mapEntryCount = static_cast<uint32_t>(m_Entries.size());
			Info.pData = m_Data.data();
			Info.pMapEntries = m_Entries.data();

			return Info;
		}

		// Make sure to destruct all Constant<T> instances before calling this
		void Reset()
		{
			m_Entries.clear();
			m_Stream.clear();
			m_bChanged = false;
		}

		const bool HasChanged() const { m_bChanged; }

		uint64_t ComputeHash() const
		{
			uint64_t uHash = hlx::CRC32(m_Data.data(), m_Data.size());
			AccessUnionElement<uint64_t, uint32_t>(uHash, 1) = hlx::CRC32(m_Entries.data(), m_Entries.size() * sizeof(vk::SpecializationMapEntry));
			return uHash;
		}

	private:
		void SetChangedFlag() { m_bChanged = true; }
	private:
		bool m_bChanged = false;
		std::vector<vk::SpecializationMapEntry> m_Entries;
		hlx::bytes m_Data;
		hlx::bytestream m_Stream;
	};
	//---------------------------------------------------------------------------------------------------

	struct PushConstantFactory
	{
		PushConstantFactory() : m_Stream(m_Data){}

		template <class T>
		struct Constant
		{
			friend struct PushConstantFactory;

			Constant& operator=(const T& _Value)
			{
				if (_Value != Value)
				{
					Parent.SetChangedFlag(uOffset, (uint32_t)sizeof(T));
					Value = _Value;
				}
			}

			operator T() { return Value; }
		private:

			Constant(PushConstantFactory& _Parent, T& _Value , const uint32_t _uOffset) :
				Value(_Value), Parent(_Parent), uOffset(_uOffset) {}
		private:
			const uint32_t uOffset;
			T& Value;
			PushConstantFactory& Parent;
		};

		template <class T>
		friend struct Constant;

		template <class T>
		Constant<T> AddConstant(const T& _Value, const vk::ShaderStageFlags _kStages)
		{
			const uint32_t uOffset = static_cast<uint32_t>(m_Stream.get_offset());
			SetChangedFlag(uOffset, (uint32_t)sizeof(T));

			// here we create a range for each variable T since T can be a struct too

			vk::PushConstantRange& Range = m_Ranges.emplace_back();
			Range.offset = uOffset;
			Range.stageFlags = _kStages;
			Range.size = (uint32_t)sizeof(T);

			m_Stream <<_Value;			
			return Constant<T>(*this, *reinterpret_cast<T*>(m_Stream.get_data(uOffset)), uOffset);
		}

		// to be called after vulkan uploaded the push constants
		void ResetChangedFlag() { uStartOffset = HUNDEFINED32; uEndOffset = 0u; }
		const bool HasChanged() const { return  uStartOffset != HUNDEFINED32 &&(uEndOffset-uStartOffset) > 0; }

		const uint32_t GetRangeCount() const { return static_cast<uint32_t>(m_Ranges.size()); }
		const vk::PushConstantRange* GetRanges() const { return m_Ranges.data(); }
		// hash over ranges (not data!)
		const size_t ComputeRangeHash() const
		{
			size_t uHash = 0u;
			for (const vk::PushConstantRange& Range : m_Ranges)
			{
				uHash = hlx::AddHash(uHash, Range.offset);
				uHash = hlx::AddHash(uHash, (uint32_t)Range.stageFlags);
				uHash = hlx::AddHash(uHash, Range.size);
			}
			return uHash;
		}
		const void* GetValues() const { return m_Data.data(); }

		// Make sure to destruct all Constant<T> instances before calling this
		void Reset()
		{
			ResetChangedFlag();
			m_Ranges.clear();
			m_Stream.clear();
		}

	private:
		void SetChangedFlag(const uint32_t _uOffset, const uint32_t _uSize)
		{
			uStartOffset = std::min(uStartOffset, _uOffset);
			uEndOffset = std::max(uEndOffset, _uOffset + _uSize);
		}

	private:
		// range
		uint32_t uStartOffset = HUNDEFINED32;
		uint32_t uEndOffset = 0u;

		std::vector<vk::PushConstantRange> m_Ranges;
		hlx::bytes m_Data;
		hlx::bytestream m_Stream;
	};

	//---------------------------------------------------------------------------------------------------
	// creates the pipeline layout for only one module
	inline vk::PipelineLayout CreatePipelineLayout(const SPIRVModule& _Module, vk::Device _hDevice, const vk::AllocationCallbacks* _pAllocators = nullptr, const PushConstantFactory* _pPushConstants = nullptr)
	{
		vk::PipelineLayoutCreateInfo Info{};

		Info.pPushConstantRanges = _pPushConstants != nullptr ? _pPushConstants->GetRanges() : nullptr;
		Info.pushConstantRangeCount = _pPushConstants != nullptr ? _pPushConstants->GetRangeCount() : 0u;

		std::array<TVarSet, kMaxDescriptorSets> Sets;
		uint32_t uLastSet = SortIntoDescriptorSets(_Module, Sets);

		std::vector<vk::DescriptorSetLayout> Layouts(uLastSet);

		// empty sets are default initialized to null handles
		for (uint32_t uSet = 0u; uSet < uLastSet; ++uSet)
		{
			if (Sets[uSet].empty() == false)
			{
				Layouts[uSet] = CreateDescriptorSetLayout(Sets[uSet], _hDevice, _pAllocators);
			}
		}
		
		Info.pSetLayouts = Layouts.data();
		Info.setLayoutCount = static_cast<uint32_t>(Layouts.size());

		return _hDevice.createPipelineLayout(Info, _pAllocators);
	}
	//---------------------------------------------------------------------------------------------------

	template <class Selector, class Element>
	inline Element Select(const Selector _kSelector, const std::initializer_list<Selector>& _Selectors, const std::initializer_list<Element>& _Elements)
	{
		std::initializer_list<Element>::const_iterator eit = _Elements.begin();
		for (auto sit = _Selectors.begin(); sit != _Selectors.end(); ++sit, ++eit)
		{
			if (*sit == _kSelector)
				return *eit;
		}

		return {};
	}
	//---------------------------------------------------------------------------------------------------

	// converts variable type (vertex shader input) to vk format, images etc not supported
	// not all types are supported (e.g. unorm, snorm, scaled, compressed etc)
	inline vk::Format TypeToFormat(const SPIRVType& _Type)
	{
		const spv::Op kType = _Type.GetType();
		const spv::Op kSubType = _Type.GetSubTypes().empty() ? spv::OpNop : _Type.GetSubTypes().front().GetType();
		const uint32_t uDim = _Type.GetDimension();

		switch (kType)
		{
		case spv::OpTypeInt:
			if (_Type.GetSign()) // signed
				return Select(uDim, {8u, 16u, 32u}, { vk::Format::eR8Sint, vk::Format::eR16Sint, vk::Format::eR32Sint }); // bitdepth
			else
				return Select(uDim, { 8u, 16u, 32u }, { vk::Format::eR8Uint, vk::Format::eR16Uint, vk::Format::eR32Uint }); // bitdepth
		case spv::OpTypeFloat:
			return Select(uDim, { 16u, 32u }, { vk::Format::eR16Sfloat, vk::Format::eR32Sfloat }); // bitdepth
		case spv::OpTypeVector:
			HASSERT(kSubType != spv::OpNop, "Invalid subtype");
			switch (kSubType) // 32 bit format assumed
			{
			case spv::OpTypeInt:
				if (_Type.GetSign()) // signed
					return Select(uDim, { 2u, 3u, 4u }, { vk::Format::eR32G32Sint, vk::Format::eR32G32B32Sint, vk::Format::eR32G32B32A32Sint});
				else
					return Select(uDim, { 2u, 3u, 4u }, { vk::Format::eR32G32Uint, vk::Format::eR32G32B32Uint, vk::Format::eR32G32B32A32Uint});
			case spv::OpTypeFloat:
				return Select(uDim, { 2u, 3u, 4u }, { vk::Format::eR32G32Sfloat, vk::Format::eR32G32B32Sfloat, vk::Format::eR32G32B32A32Sfloat});
			default: break;
			}			
			break;
		default: break;
		}

		return vk::Format::eUndefined;
	}

	//---------------------------------------------------------------------------------------------------

	struct VertexLayoutFactory
	{
		// valid as long as VertexLayoutFactory is valid and GetVertexLayout() has not been called again
		vk::PipelineVertexInputStateCreateInfo GetVertexLayout(const std::vector<VariableInfo>& _Vars)
		{
			m_Attributes.resize(0);
			m_Bindings.resize(0); // clean data
		
			for (const VariableInfo& Var : _Vars)
			{
				if (Var.kStorageClass == spv::StorageClassInput && Var.bBuiltIn == false)
				{
					HASSERT(Var.uBinding < 16u, "Invalid binding (to high)");

					auto it = std::find_if(m_Bindings.begin(), m_Bindings.end(), [&](const vk::VertexInputBindingDescription& _Binding) {return _Binding.binding == Var.uBinding; });
					if (it == m_Bindings.end())
					{
						it = m_Bindings.insert(m_Bindings.end(), {});
					}

					vk::VertexInputBindingDescription& Binding = *it;
					Binding.binding = Var.uBinding;
					// variables with the same binding should be forced to have the same inputrate
					Binding.inputRate = Var.bInstanceData ? vk::VertexInputRate::eInstance : vk::VertexInputRate::eVertex;

					vk::VertexInputAttributeDescription Attrib{};
					Attrib.binding = Var.uBinding;
					Attrib.location = Var.uLocation;
					Attrib.format = TypeToFormat(Var.Type);
					Attrib.offset = Binding.stride;

					Binding.stride += Var.Type.GetSize();

					HASSERT(Attrib.format != vk::Format::eUndefined, "Unknown vertex attribute format");

					m_Attributes.push_back(std::move(Attrib));
				}
			}

			vk::PipelineVertexInputStateCreateInfo Layout{};
			Layout.pNext = nullptr;
			Layout.vertexAttributeDescriptionCount = static_cast<uint32_t>(m_Attributes.size());
			Layout.vertexBindingDescriptionCount = static_cast<uint32_t>(m_Bindings.size());
			Layout.pVertexAttributeDescriptions = m_Attributes.data();
			Layout.pVertexBindingDescriptions = m_Bindings.data();

			return Layout;
		}

		inline size_t ComputeHash() const
		{
			size_t uHash = 0u;
			for (const auto& Binding : m_Bindings)
			{
				uHash = hlx::AddHash(uHash, Binding.binding);
				uHash = hlx::AddHash(uHash, Binding.inputRate);
				uHash = hlx::AddHash(uHash, Binding.stride);
			}

			for (const auto& Attribute : m_Attributes)
			{
				uHash = hlx::AddHash(uHash, Attribute.binding);
				uHash = hlx::AddHash(uHash, Attribute.format);
				uHash = hlx::AddHash(uHash, Attribute.offset);
				uHash = hlx::AddHash(uHash, Attribute.location);
			}

			return uHash;
		}

	private:
		std::vector<vk::VertexInputAttributeDescription> m_Attributes;
		std::vector<vk::VertexInputBindingDescription> m_Bindings; // buffer slots
	};

	//---------------------------------------------------------------------------------------------------

	inline vk::ShaderModuleCreateInfo GetShaderModuleInfo(const SPIRVModule& _Module)
	{
		vk::ShaderModuleCreateInfo Info{};
		Info.codeSize = static_cast<uint32_t>(_Module.GetCode().size() * sizeof(uint32_t));
		Info.pCode = _Module.GetCode().data();
		return Info;
	}

	inline vk::ShaderModule CreateShaderModule(vk::Device _hDevice, const SPIRVModule& _Module, vk::AllocationCallbacks* _pAllocCallbacks = nullptr)
	{
		vk::ShaderModuleCreateInfo Info(GetShaderModuleInfo(_Module));
		vk::ShaderModule vkModule{};
		const vk::Result kResult = _hDevice.createShaderModule(&Info, _pAllocCallbacks, &vkModule);
		if (kResult != vk::Result::eSuccess)
		{
			HERROR("Failed to create shader module %s [%s]", _Module.GetEntryPoint().c_str(), vk::to_string(kResult).c_str());
		}

		return vkModule;
	}

	inline vk::PipelineShaderStageCreateInfo CreateShaderStage(vk::Device _hDevice, const SPIRVModule& _Module, const vk::SpecializationInfo* _pSpecInfo = nullptr, vk::AllocationCallbacks* _pAllocCallbacks = nullptr)
	{
		vk::PipelineShaderStageCreateInfo ShaderStage{};

		ShaderStage.stage = GetShaderStage(_Module);
		ShaderStage.module = CreateShaderModule(_hDevice, _Module, _pAllocCallbacks);
		ShaderStage.pName = _Module.GetEntryPoint().c_str();
		ShaderStage.pSpecializationInfo = _pSpecInfo;

		return ShaderStage;
	}
} // Spear

#endif // !SPEAR_SPIRVINTEROP_H