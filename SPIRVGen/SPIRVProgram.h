//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVPROGRAM_H
#define SPEAR_SPIRVPROGRAM_H

#include "SPIRVQuaternion.h"
#include "SPIRVComplex.h"
#include "SPIRVBranchOperations.h"

namespace Spear
{
	template <bool Assemble>
	class SPIRVProgram
	{
		friend class SPIRVAssembler;
	public:
		static constexpr bool bAssembleProg = Assemble;
#pragma region type_defs

		// extract underlying variable type
		//template <class T>
		//using underlying_var_t = cond_t<is_var<T>, var_value_t<T>, T>;

		template <class T>
		using var = var_t<T, Assemble, spv::StorageClassFunction>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using var_in = var_in_t<T, Assemble, Location>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using var_out = var_out_t<T, Assemble, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32>
		using var_uniform = var_uniform_t<T, Assemble, Binding, Set>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using var_uniform_constant = var_uniform_constant_t<T, Assemble, Binding, Set, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32>
		using CBuffer = var_uniform_t<T, Assemble, Binding, Set>;

		template <class T, uint32_t Size, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32>
		using Array = var_uniform_t<array_t<T, Size>, Assemble, Binding, Set>;

		template <class T>
		using ArrayElement = var<T>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using VertexInput = var_in_t<T, Assemble, Location, false>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using InstanceInput = var_in_t<T, Assemble, Location, true>;

		const var_per_vertex<Assemble> kPerVertex;

		const var_builtin_t<spv::BuiltInVertexIndex, int, Assemble, spv::StorageClassInput> kVertexIndex;
		const var_builtin_t<spv::BuiltInInstanceIndex, int, Assemble, spv::StorageClassInput> kInstanceIndex;
		const var_builtin_t<spv::BuiltInDrawIndex, int, Assemble, spv::StorageClassInput> kDrawIndex;

		const var_builtin_t<spv::BuiltInBaseVertex, int, Assemble, spv::StorageClassInput> kBaseVertex;
		const var_builtin_t<spv::BuiltInBaseInstance, int, Assemble, spv::StorageClassInput> kBaseInstance;

		const var_builtin_t<spv::BuiltInFragCoord, float4_t, Assemble, spv::StorageClassInput> kFragCoord;
		const var_builtin_t<spv::BuiltInFragDepth, float, Assemble, spv::StorageClassInput> kFragDepth;

		using s32 = var<int32_t>;
		using s64 = var<int64_t>;
		using int2 = var<int2_t>;
		using int3 = var<int3_t>;
		using int4 = var<int4_t>;

		using u32 = var<uint32_t>;
		using u64 = var<uint64_t>;
		using uint2 = var<uint2_t>;
		using uint3 = var<uint3_t>;
		using uint4 = var<uint4_t>;

		using f32 = var<float>;
		using f64 = var<double>;
		using float2 = var<float2_t>;
		using float3 = var<float3_t>;
		using float4 = var<float4_t>;

		using quaternion = SPIRVQuaternion<Assemble, spv::StorageClassFunction>;
		using complex = SPIRVComplex<Assemble, spv::StorageClassFunction>;
		using boolean = var<bool>;

		using float2x2 = var<float2x2_t>;
		using float3x3 = var<float3x3_t>;
		using float3x4 = var<float3x4_t>;
		using float4x3 = var<float4x3_t>;
		using float4x4 = var<float4x4_t>;
		using matrix = var<float4x4_t>;

		template <class T, uint32_t SpecId = HUNDEFINED32>
		using SpecConst = var_spec_const_t<T, Assemble, SpecId>;

		using SamplerState = var_uniform_constant<sampler_t>;
		// TODO: SamplerComparisonState

		// float4 component texture types
		using Texture1D = var_uniform_constant<tex1d_t<float4_t>>;
		using Texture2D = var_uniform_constant<tex2d_t<float4_t>>;
		using Texture3D = var_uniform_constant<tex3d_t<float4_t>>;
		using TextureCube = var_uniform_constant<tex_cube_t<float4_t>>;

		// generic texture types
		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using Texture1DEx = var_uniform_constant<tex1d_t<T>, Binding, Set, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using Texture2DEx = var_uniform_constant<tex2d_t<T>, Binding, Set, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using Texture3DEx = var_uniform_constant<tex3d_t<T>, Binding, Set, Location>;

		template <class T, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
		using TextureCubeEx = var_uniform_constant<tex_cube_t<T>, Binding, Set, Location>;

		template <class T, uint32_t Location = HUNDEFINED32>
		using RenderTargetEx = var_out_t<T, Assemble, Location>;

		using RenderTarget = var_out_t<float4_t, Assemble>;

		template <class T, uint32_t InputAttachmentIndex = HUNDEFINED32>
		using SubPassColorEx = var_subpass_t<T, Assemble, false, InputAttachmentIndex>;

		template <class T, uint32_t InputAttachmentIndex = HUNDEFINED32>
		using SubPassDepthEx = var_subpass_t<T, Assemble, true, InputAttachmentIndex>;

		using SubPassColor = var_subpass_t<float4_t, Assemble, false>;
		using SubPassDepth = var_subpass_t<float, Assemble, true>;

		template <class T>
		using PushConstant = var_push_const_t<T, Assemble>;

		// TODO: array types

#pragma endregion
		SPIRVProgram(
			const spv::ExecutionModel _kExecutionModel = spv::ExecutionModelFragment,
			const spv::ExecutionMode _kMode = spv::ExecutionModeOriginLowerLeft,
			const std::string& _sEntryPoint = "main",
			const std::vector<std::string>& _Extensions = { ExtGLSL450 },
			const std::vector<spv::Capability>& _Capabilities = {spv::CapabilityShader});

		virtual ~SPIRVProgram();

		template <class TProg, class... Ts>
		void Execute(Ts&& ..._args);

		inline const spv::ExecutionModel GetExecutionModel() const { return m_kExecutionModel; }
		inline const spv::ExecutionMode GetExecutionMode() const { return m_kExecutionMode; }
		inline const std::string& GetEntryPoint() const { return m_sEntryPoint; }

		inline const std::vector<std::string>& GetExtensions() const { return m_Extensions; }
		// should only be called in the constructor of the derived program
		inline void AddExtension(const std::string& _sExtension) { m_Extensions.push_back(_sExtension); }

		inline const std::vector<spv::Capability>& GetCapabilities() const { return m_Capabilities; }
		// should only be called in the constructor of the derived program
		inline void AddCapability(const spv::Capability _kCapability) { m_Capabilities.push_back(_kCapability); }

	protected:
		const spv::ExecutionModel m_kExecutionModel;
		const spv::ExecutionMode m_kExecutionMode;
		const std::string m_sEntryPoint;
		std::vector<std::string> m_Extensions;
		std::vector<spv::Capability> m_Capabilities;
	};

	//---------------------------------------------------------------------------------------------------
	// Predefined stage programs
	template <bool Assemble = true>
	class VertexProgram : public SPIRVProgram<Assemble>
	{
	public:
		VertexProgram(
			const std::string& _sEntryPoint = "vertex_main",
			const std::vector<std::string>& _Extensions = { ExtGLSL450 },
			const std::vector<spv::Capability>& _Capabilities = { spv::CapabilityShader })
			: SPIRVProgram<Assemble>(spv::ExecutionModelVertex, spv::ExecutionModeMax, _sEntryPoint, _Extensions, _Capabilities) {}
		virtual ~VertexProgram() {}
	};

	template <bool Assemble = true>
	class FragmentProgram : public SPIRVProgram<Assemble>
	{
	public:
		FragmentProgram(
			const std::string& _sEntryPoint = "fragment_main",
			const spv::ExecutionMode _kMode = spv::ExecutionModeOriginLowerLeft,
			const std::vector<std::string>& _Extensions = { ExtGLSL450 },
			const std::vector<spv::Capability>& _Capabilities = { spv::CapabilityShader, spv::CapabilityInputAttachment })
			: SPIRVProgram<Assemble>(spv::ExecutionModelFragment, _kMode, _sEntryPoint, _Extensions, _Capabilities) {}
		virtual ~FragmentProgram() {}
	};

#pragma endregion

	//---------------------------------------------------------------------------------------------------
	template <bool Assemble>
	SPIRVProgram<Assemble>::SPIRVProgram(
		const spv::ExecutionModel _kExecutionModel,
		const spv::ExecutionMode _kExecutionMode,
		const std::string& _sEntryPoint,
		const std::vector<std::string>& _Extensions,
		const std::vector<spv::Capability>& _Capabilities) :
		m_kExecutionModel(_kExecutionModel),
		m_kExecutionMode(_kExecutionMode),
		m_sEntryPoint(_sEntryPoint),
		m_Extensions(_Extensions),
		m_Capabilities(_Capabilities)
	{
	}

	//---------------------------------------------------------------------------------------------------
	template <bool Assemble>
	SPIRVProgram<Assemble>::~SPIRVProgram()
	{
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template <class TProg, class... Ts>
	inline void SPIRVProgram<Assemble>::Execute(Ts&& ..._args)
	{
		((TProg*)this)->operator()(std::forward<Ts>(_args)...);
	}
	//---------------------------------------------------------------------------------------------------	
}; // !Spear

#endif // !SPEAR_SPIRVPROGRAM_H
