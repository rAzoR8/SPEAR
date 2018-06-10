//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPAR_SPIRVVARIABLE_H
#define SPAR_SPIRVVARIABLE_H

#include "SPIRVConstant.h"
#include "GetStructMember.h"
#include "SPIRVDecoration.h"
#include "SPIRVAssembler.h"
#include "HashUtils.h"

// enable old var load/store behaviour for now
#define HDIRECT_MEMACCESS

namespace Spear
{
	// get value of var_t<> based on type
	template<class T>
	auto get_arg_value(const T& var)
	{
		if constexpr(is_var<T>)
		{
			return var.Value;
		}
		else
		{
			return var;
		}
	}

	template <class T, class ...Ts>
	const T& get_first_arg(const T& _first, const Ts& ..._args) { return _first; }

	//forward decl
	template <class T, bool Assemble, spv::StorageClass Class>
	struct var_t;

	//---------------------------------------------------------------------------------------------------
	template <bool Assemble, class T, spv::StorageClass C1 = spv::StorageClassFunction>
	inline var_t<T, Assemble, C1> make_var(const T& _Value)
	{
		return var_t<T, Assemble, C1>(_Value);
	}

#ifndef mvar
#define mvar(x) Spear::make_var<Assemble>((x))
#endif

	//---------------------------------------------------------------------------------------------------
	// just copy the result id
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_intermediate(const var_t<T, Assemble, C1>& _Var)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble)
		{
			var.uResultId = _Var.Load();
		}
		else
		{
			var.Value = _Var.Value;
		}

		return var;
	}

#ifndef mivar
#define mivar(x) Spear::make_intermediate((x))
#endif

	//---------------------------------------------------------------------------------------------------

	// creates a intermediate constant, not an OpVariable!
	template <bool Assemble, class ...Ts, class Ret = va_type_t<Ts...>>
	inline var_t<Ret, Assemble, spv::StorageClassFunction> make_const(const Ts& ..._Args)
	{
		return var_t<Ret, Assemble, spv::StorageClassFunction>(TIntermediate(), _Args...);
	}

#ifndef mcvar
#define mcvar(x) Spear::make_const<Assemble>((x))
#endif

	//---------------------------------------------------------------------------------------------------
	// Create a intermediate vector with dimension N from constants _Values
	template <bool Assemble, uint32_t N, class T, typename = std::enable_if_t<is_scalar<T>>>
	inline var_t<vec_type_t<T, N>, Assemble, spv::StorageClassFunction> make_const_vec(const std::array<T, N>& _Values)
	{
		auto var = var_t<vec_type_t<T, N>, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			if constexpr(N > 1)
			{
				for (uint32_t i = 0; i < N; ++i)
				{
					var.Value[i] = _Values[i];
				}
			}
			else
			{
				var.Value = _Values.front();
			}
		}
		else
		{
			if constexpr(N > 1)
			{
				var.uResultId = GlobalAssembler.AddConstant(SPIRVConstant::MakeVec(_Values));
			}
			else
			{
				var.uResultId = GlobalAssembler.AddConstant(SPIRVConstant::Make(_Values.front()));
			}
		}

		return var;
	}

	// convert V to U
	template <class U, class V, bool Assemble, spv::StorageClass C1>
	inline uint32_t convert_op(const var_t<V, Assemble, C1>& _Other)
	{
		_Other.Load();

		if constexpr(std::is_same_v<U, V>)
		{
			return _Other.uResultId;
		}
		else
		{
			const spv::Op kType = GetConvertOp<V, U>();
			HASSERT(kType != spv::OpNop, "Invalid variable type conversion!");
			const uint32_t uTypeId = GlobalAssembler.AddType(SPIRVType::FromType<U>()); // target type

			return GlobalAssembler.EmplaceOperation(kType, uTypeId, SPIRVOperand(kOperandType_Intermediate, _Other.uResultId));
		}
	}

	//---------------------------------------------------------------------------------------------------


	template <class T, bool Assemble, spv::StorageClass Class, class ...Ts>
	const var_t<T, Assemble, Class>& get_first_var(const var_t<T, Assemble, Class>& _first, const Ts& ..._args) { return _first; }

	// convert a list of arguments to a vector of SPIRVOperands, if the argument is a variable, its result ID will be pushed to the vector, otherwise it will be decomposed to uint32_t literals
	inline void GetOperandsFromArgumentList(std::vector<SPIRVOperand>& _OutOperands) {}

	template <class T, class ...Ts>
	inline void GetOperandsFromArgumentList(std::vector<SPIRVOperand>& _OutOperands, const T& _First, const Ts& ... _Args)
	{
		if constexpr(is_var<T>)
		{
			_OutOperands.push_back(SPIRVOperand::Intermediate(_First.Load()));
		}
		else
		{
			for (const uint32_t& uLiteral : MakeLiterals(_First))
			{
				_OutOperands.push_back(SPIRVOperand::Literal(uLiteral));
			}
		}

		if constexpr(sizeof...(_Args) > 0)
		{		
			GetOperandsFromArgumentList(_OutOperands, _Args...);
		}
	}

	using TImageOperands = hlx::Flag<spv::ImageOperandsMask>;

	inline const uint32_t MakeSampledImage(const SPIRVType& _ImgType, const uint32_t _uImageId, const uint32_t _uSamplerId)
	{
		// OpSampledImage uSampledImgType ImgId SamplerId
        return GlobalAssembler.EmplaceOperation(
            spv::OpSampledImage, // OpCode
            GlobalAssembler.AddType(SPIRVType::SampledImage(_ImgType)), // result type
            SPIRVOperand::Intermediate(_uImageId), // first operand
            SPIRVOperand::Intermediate(_uSamplerId)); // second operand

		// TODO: store uOpSampledImageId in a map in case the same sampler is reused with this image
	}

	enum EOpTypeBase : uint32_t
	{
		kOpTypeBase_Result,
		kOpTypeBase_Operand1,
		kOpTypeBase_Operand2,
		kOpTypeBase_Operand3
	};

	enum LSType : uint32_t
	{
		kLSType_Load = 0u,
		kLSType_Store = 1u,
		//kLSType_Intermediate = 2,
	};

	// load store info
	struct LSInfo
	{
		LSType kType = kLSType_Load;
		uint32_t uResultId = HUNDEFINED32;
		uint32_t uScopeLevel = HUNDEFINED32;
		uint32_t uScopeId = HUNDEFINED32;
	};

	struct ComponentInfo
	{
		uint32_t uComponentId = HUNDEFINED32;
		uint32_t uLastStoredId = HUNDEFINED32; // last result written to this var
	};

	constexpr uint32_t kAlignmentSize = 16u;

	template <bool Assemble>
	struct var_decoration {};

	template <>
	struct var_decoration<false>
	{
		var_decoration() noexcept {}
		var_decoration(const var_decoration& _Other) noexcept {}
		var_decoration(var_decoration&& _Other) noexcept {}
		var_decoration(const spv::StorageClass _kStorageClass) noexcept {};
		virtual ~var_decoration() {};

		inline const var_decoration& operator=(var_decoration&& _Other) const noexcept { return *this; }
		inline const var_decoration& operator=(const var_decoration& _Other) const noexcept { return *this; }
		template <class T>
		inline const var_decoration& operator=(T&& _Other) const { return *this; }
		template <class T>
		inline const var_decoration& operator=(const T& _Other) const { return *this; }
		inline void Store() const noexcept {};
		inline uint32_t Load() const noexcept { return HUNDEFINED32; };
		inline uint32_t GetLastStore() const noexcept { return HUNDEFINED32; };

		inline void Decorate(const SPIRVDecoration& _Decoration) noexcept {};
		inline void SetBinding(const uint32_t _uBinding, const uint32_t uDescriptorSet) noexcept {}
		inline void SetLocation(const uint32_t _uLocation) noexcept {}
		inline void SetIdentifier(const uint32_t _uIdentifier) noexcept {}
		inline void MaterializeDecorations() const noexcept {};
		inline void CreateAccessChain() const noexcept {}
		inline void SetName(const std::string& _sName) noexcept {};
	};

	template <>
	struct var_decoration<true>
	{
		mutable uint32_t uVarId = HUNDEFINED32; // result id OpVar or OpAccessChain
		mutable uint32_t uResultId = HUNDEFINED32; // result of arithmetic instructions or OpLoad
		mutable uint32_t uBaseId = HUNDEFINED32; // base VarId from parent structure
		mutable uint32_t uBaseTypeId = HUNDEFINED32; // type of base parent sturcture
		spv::StorageClass kStorageClass = spv::StorageClassMax;
		mutable uint32_t uTypeId = HUNDEFINED32;
		uint32_t uMemberOffset = HUNDEFINED32;
		uint32_t uMemberIndex = HUNDEFINED32; // relative to the parent sturcture

		uint32_t uDescriptorSet = HUNDEFINED32; // res input
		uint32_t uBinding = HUNDEFINED32; // local to res input
		uint32_t uLocation = HUNDEFINED32; // res output
		uint32_t uSpecConstId = HUNDEFINED32; // used in vulkan api to set data for specialization
		uint32_t uInputAttachmentIndex = HUNDEFINED32; // subpass output index
		mutable bool bTexSampled = false; // indicates that the var texture has been sampled in the code
		mutable bool bTexStored = false; // indicates that the var texture has been stored in the code
		bool bInstanceData = false; // only valid for StorageClassInput in vertex stage
		bool bBuiltIn = false; //only valid for StorageClassInput, used for VertexIndex and other system values
		mutable bool bMaterializedName = false;



#ifdef HDIRECT_MEMACCESS
        mutable uint32_t uLastStoreId = HUNDEFINED32;
#else
        mutable std::vector<LSInfo> MemAccess;
#endif

		std::string sName; // user can set this to identify the variable stored in the module

		// for structs
		std::vector<uint32_t> AccessChain;
		SPIRVOperation* pVarOp = nullptr;

		SPIRVType Type;
		mutable std::vector<SPIRVDecoration> Decorations;

		// dim & indices -> component
		mutable std::unordered_map<uint64_t, ComponentInfo> ExtractedComponents;

		void Decorate(const SPIRVDecoration& _Decoration);
		void MaterializeDecorations() const;
		void SetBinding(const uint32_t _uBinding, const uint32_t uDescriptorSet);
		void SetLocation(const uint32_t _uLocation);
		void SetName(const std::string& _sName);
		void CreateAccessChain() const;

		uint32_t GetLastStore() const;

		void Store() const;
		uint32_t Load() const;
		
		var_decoration(const spv::StorageClass _kStorageClass) : kStorageClass(_kStorageClass) {};
		var_decoration(const var_decoration<true>& _Other);
		var_decoration(var_decoration<true>&& _Other) noexcept;
		virtual ~var_decoration();

		const var_decoration& operator=(const var_decoration& _Other) const;
		//const var_decoration& operator=(var_decoration&& _Other) const noexcept;
	};

	//---------------------------------------------------------------------------------------------------

	struct TIntermediate {};

	template <typename T, bool Assemble = true, spv::StorageClass Class = spv::StorageClassFunction>
	struct var_t : public var_decoration<Assemble>
	{
		typedef TSPVVarTag SPVVarTag;
		typedef T ValueType;
		typedef base_type_t<T> BaseType;
		typedef var_t<T, Assemble, Class> VarType;

		static constexpr bool AssembleMode = Assemble;
		static constexpr spv::StorageClass StorageClass = Class;

		mutable T Value;

		// generates OpVar
		template <class... Ts>
		var_t(const Ts& ... _args);

		// does not generate OpVar, uResultId needs to be assigned
		template <class... Ts>
		var_t(TIntermediate, const Ts& ... _args);

		// calls SetName
		var_t(const char* _sName);
		// calls SetName
		var_t(std::string_view _sName);

		template <spv::StorageClass C1>
		var_t(const var_t<T, Assemble, C1>& _Other);

		template <class U>
		const var_t& operator=(const U& _Other) const;

		// workaround for lambda ambiguity problem
		template <class U>
		var_t& operator=(const U& _Other) { static_cast<const var_t*>(this)->operator=(_Other); return *this; };

		template <spv::StorageClass C1>
		const var_t& operator+=(const var_t<T, Assemble, C1>& _Other) const;
		template <spv::StorageClass C1>
		const var_t& operator-=(const var_t<T, Assemble, C1>& _Other) const;

		template <class U, typename = std::enable_if_t<is_convertible<U, BaseType>>>
		const var_t& operator+=(const U& _Other) const { return operator+=(make_const<Assemble>((BaseType)_Other)); }
		template <class U, typename = std::enable_if_t<is_convertible<U, BaseType>>>
		const var_t& operator-=(const U& _Other) const { return operator-=(make_const<Assemble>((BaseType)_Other)); }

		template <class U, spv::StorageClass C1>
		const var_t& operator*=(const var_t<U, Assemble, C1>& _Other) const;

		// mutable mul with constant
		template <class U, typename = std::enable_if_t<is_convertible<U, BaseType>>>
		const var_t& operator*=(const U& _Other) const { return operator*=(make_const<Assemble>((BaseType)_Other));	}
	
		template <class U, spv::StorageClass C1>
		const var_t& operator/=(const var_t<U, Assemble, C1>& _Other) const;
		
		// mutable div with constant
		template <class U, typename = std::enable_if_t<is_convertible<U, BaseType>>>
		const var_t& operator/=(const U& _Other) const { return operator*=(make_const<Assemble>((BaseType)1 / (BaseType)_Other)); }
		
		var_t<T, Assemble, spv::StorageClassFunction> operator!() const;

		const var_t& operator++() const; // mutable
		var_t<T, Assemble, spv::StorageClassFunction> operator++(int) const; // immutable

		const var_t& operator--() const; // mutable
		var_t<T, Assemble, spv::StorageClassFunction> operator--(int) const; // immutable

		// negation
		var_t<T, Assemble, spv::StorageClassFunction> operator-() const;

		const T* operator->() const { return &Value; }

#pragma region ArrayAccess
		var_t<uint32_t, Assemble, spv::StorageClassFunction> Length() const
		{
			static_assert(is_array<T>, "Unsupported type (array expected)");
			return var_t<uint32_t, Assemble, spv::StorageClassFunction>(T::Size);
		}

		template <class Index, spv::StorageClass C1, class U = T, typename = std::enable_if_t<is_array<U> && is_integer_type<Index>>>
		inline var_t<array_element_t<U>, Assemble, spv::StorageClassFunction> operator[](const var_t<Index, Assemble, C1>& _Index) const
		{
			static_assert(is_array<U>, "Unsupported type (array expected)");
			auto var = var_t<array_element_t<U>, Assemble, spv::StorageClassFunction>(TIntermediate());

			if constexpr(Assemble)
			{
				const uint32_t uIndexId = _Index.Load();

				const uint32_t uPtrTypeId = GlobalAssembler.AddType(SPIRVType::Pointer(var.Type, kStorageClass));
				SPIRVOperation OpAccessChain(spv::OpAccessChain, uPtrTypeId, SPIRVOperand(kOperandType_Intermediate, uBaseId != HUNDEFINED32 ? uBaseId : uVarId));

				for (const uint32_t& uMemberIdx : AccessChain)
				{
					OpAccessChain.AddIntermediate(GlobalAssembler.AddConstant(SPIRVConstant::Make(uMemberIdx)));
				}

				OpAccessChain.AddIntermediate(uIndexId);

				var.uVarId = GlobalAssembler.AddOperation(std::move(OpAccessChain));
			}
			else
			{
				var.Value = Value[_Index.Value];
			}

			return var;
		}

		template <class Index, class U = T, typename = std::enable_if_t<is_array<U> && is_integer_type<Index>>>
		inline var_t<array_element_t<U>, Assemble, spv::StorageClassFunction> operator[](const Index& _Index) const
		{
			return this->operator[](make_const<Assemble>(_Index));
		}

#pragma endregion

#pragma region VectorAccess
		template <size_t Dim, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3>
		static constexpr bool Monotonic = !((Dim >= 1 && v0 != 0) || (Dim >= 2 && v1 != 1) || (Dim >= 3 && v2 != 2) || (Dim >= 4 && v3 != 3));

		template <size_t Dim>
		using TExtractType = var_t<vec_type_t<BaseType, Dim>, Assemble, spv::StorageClassFunction>;

#include "SPIRVVectorComponentAccess.h"
#pragma endregion

#pragma region sample_tex
		template <
			class ReturnType,
			spv::StorageClass C1,
			class TexCoordT = tex_coord_t<T>,
			class ...Ts, // image operands variables
			typename = std::enable_if_t<is_texture<T>>>
			var_t<ReturnType, Assemble, spv::StorageClassFunction> TextureAccess(
				const uint32_t _uImageId, // _uImageId is either the result of a image.Load() or OpSampledImage operation
				const var_t<TexCoordT, Assemble, C1>& _Coords,
				const spv::Op _kSampleOp,
				const uint32_t _uDRefOrCompId = HUNDEFINED32, // only valid when used with Dref image operations, _uDRefVarId is the result of a Load() operation
				const TImageOperands _kImageOps = spv::ImageOperandsMaskNone, // number of bits set needs to equal number of _ImageOperands arguments
				const Ts& ..._ImageOperands) const
		{
			auto var = var_t<ReturnType, Assemble, spv::StorageClassFunction>(TIntermediate());

			if constexpr(Assemble)
			{
				bTexSampled = true;

				// Result Type must be a vector of four components of floating point type or integer type.
				// Its components must be the same as Sampled Type of the underlying OpTypeImage(unless that underlying	Sampled Type is OpTypeVoid).
				using SampleType = tex_sample_t<T>;

				const uint32_t uReturnTypeId = _uDRefOrCompId == HUNDEFINED32 ? GlobalAssembler.AddType(SPIRVType::FromType<SampleType>()) : GlobalAssembler.AddType(SPIRVType::FromType<ReturnType>());
				const uint32_t uCoordId = _Coords.Load();

				std::vector<SPIRVOperand> SampleOperands = { SPIRVOperand::Intermediate(_uImageId),  SPIRVOperand::Intermediate(uCoordId) };

				// TODO: replace _uDRefOrCompId with a vector if Ids to be inserted after coords (for OpImageDrefGather)
				// add Dref <id> or Component <id> after CoordId and before following ImageOperands
				if (_uDRefOrCompId != HUNDEFINED32)
				{
					SampleOperands.push_back(SPIRVOperand::Intermediate(_uDRefOrCompId));
				}

				// variable number of image operations
				if (_kImageOps.None() == false)
				{
					SampleOperands.push_back(SPIRVOperand::Literal(static_cast<uint32_t>(_kImageOps)));
					GetOperandsFromArgumentList(SampleOperands, _ImageOperands...);
				}

				// TODO: check for some operations like OpImageSampleProjExplicitLod ImageOperands are mandatory so _ImageOperands... must not be empty

				// OpImageSampleImplicitLod uReturnTypeId uOpSampledImageId uCoordId
				const uint32_t uSampleResultId = GlobalAssembler.EmplaceOperation(_kSampleOp, uReturnTypeId, std::move(SampleOperands));

				if (std::is_same_v<SampleType, ReturnType> == false && _uDRefOrCompId == HUNDEFINED32)
				{
					// TODO: use vector access instead
					const uint32_t uElemTypeId = GlobalAssembler.AddType(SPIRVType::FromType<base_type_t<ReturnType>>());

					constexpr uint32_t N{ Dimension<ReturnType> };

					if constexpr (N > 1)
					{
						const uint32_t uRealReturnTypeId = GlobalAssembler.AddType(SPIRVType::FromType<ReturnType>());
						SPIRVOperation OpConstruct(spv::OpCompositeConstruct, uRealReturnTypeId);

						for (uint32_t n = 0u; n < Dimension<ReturnType>; ++n)
						{
							OpConstruct.AddIntermediate(
                                GlobalAssembler.EmplaceOperation(
                                spv::OpCompositeExtract,
                                uElemTypeId,
                                SPIRVOperand(kOperandType_Intermediate, uSampleResultId), // var id to extract from
                                SPIRVOperand(kOperandType_Literal, n) // extraction index
                                )
                            );
						}

						// composite constructs treated as intermediates as they cant be loaded
						var.uResultId = GlobalAssembler.AddOperation(std::move(OpConstruct));
					}
					else
					{
						var.uResultId = GlobalAssembler.EmplaceOperation(
                            spv::OpCompositeExtract,
                            uElemTypeId,
                            SPIRVOperand::Intermediate(uSampleResultId), // var id to extract from
                            SPIRVOperand::Literal(0u) // extraction index
                        );
					}

					// TODO: store Extracted ids
				}
				else
				{
					var.uResultId = uSampleResultId;
				}
			}

			return var;
		}

		//---------------------------------------------------------------------------------------------------
		// Sample an image with an implicit level of detail.
		template <
			class ReturnType = tex_component_t<T>,
			spv::StorageClass C1,
			spv::StorageClass C2,
			class TexCoordT = tex_coord_t<T>,
			class ...Ts, // image operands variables
			typename = std::enable_if_t<is_texture<T>>>
			var_t<ReturnType, Assemble, spv::StorageClassFunction> Sample(
				const var_t<sampler_t, Assemble, C1>& _Sampler,
				const var_t<TexCoordT, Assemble, C2>& _Coords,
				const spv::Op _kSampleOp = spv::OpImageSampleImplicitLod,
				const TImageOperands _kImageOps = spv::ImageOperandsMaskNone, // number of bits set needs to equal number of _ImageOperands arguments
				const Ts& ..._ImageOperands) const
		{
			return TextureAccess<ReturnType>(MakeSampledImage(Type, Load(), _Sampler.Load()), _Coords, _kSampleOp, HUNDEFINED32, _kImageOps, _ImageOperands...);
		}

		//---------------------------------------------------------------------------------------------------
		// similar to HLSL SampleLevel
		template <
			class ReturnType = tex_component_t<T>,
			spv::StorageClass C1,
			spv::StorageClass C2,
			spv::StorageClass C3,
			class TexCoordT = tex_coord_t<T>,
			typename = std::enable_if_t<is_texture<T>>>
			var_t<ReturnType, Assemble, spv::StorageClassFunction> SampleLOD(
				const var_t<sampler_t, Assemble, C1>& _Sampler,
				const var_t<TexCoordT, Assemble, C2>& _Coords,
				const var_t<float, Assemble, C3>& _Lod) const
		{
			// A following operand is the explicit level-of-detail to use. Only valid with explicit-lod instructions. For sampling operations, it must be a floating-point type scalar. For fetch operations, it must be an
			// integer type scalar. This can only be used with an OpTypeImage that has a Dim operand of 1D, 2D,3D, or Cube, and the MS operand must be 0.
			return TextureAccess<ReturnType>(MakeSampledImage(Type, Load(), _Sampler.Load()), _Coords, spv::OpImageSampleExplicitLod, HUNDEFINED32, spv::ImageOperandsLodMask, _Lod);
		}

		//---------------------------------------------------------------------------------------------------

		// Sample an image doing depth-comparison with an implicit level of detail. (assuming OpImageSampleDrefImplicitLod)
		template <
			class ReturnType = base_type_t<tex_component_t<T>>,
			spv::StorageClass C1,
			spv::StorageClass C2,
			spv::StorageClass C3,
			class TexCoordT = tex_coord_t<T>,
			class ...Ts, // image operands variables
			typename = std::enable_if_t<is_texture<T>>>
			var_t<ReturnType, Assemble, spv::StorageClassFunction> SampleDref(
				const var_t<sampler_t, Assemble, C1>& _Sampler,
				const var_t<TexCoordT, Assemble, C2>& _Coords,
				const var_t<float, Assemble, C3>& _Dref, // depth-comparison reference value 
				const spv::Op _kSampleOp = spv::OpImageSampleDrefImplicitLod,
				const TImageOperands _kImageOps = spv::ImageOperandsMaskNone, // number of bits set needs to equal number of _ImageOperands arguments
				const Ts& ..._ImageOperands) const
		{
			return TextureAccess<ReturnType>(MakeSampledImage(Type, Load(), _Sampler.Load()), _Coords, _kSampleOp, _Dref.Load(), _kImageOps, _ImageOperands...);
		}

		//---------------------------------------------------------------------------------------------------
		// Fetch a single texel from a sampled image
		template <
			class ReturnType = tex_component_t<T>,
			spv::StorageClass C1,
			class TexCoordT = tex_gather_coord_t<T>, // uint vector
			class ...Ts, // image operands variables
			typename = std::enable_if_t<is_texture<T>>>
			var_t<ReturnType, Assemble, spv::StorageClassFunction> Fetch(
				const var_t<TexCoordT, Assemble, C1>& _Coords,
				const TImageOperands _kImageOps = spv::ImageOperandsMaskNone, // number of bits set needs to equal number of _ImageOperands arguments
				const Ts& ..._ImageOperands) const
		{
			return TextureAccess<ReturnType>(Load(), _Coords, spv::OpImageFetch, HUNDEFINED32, _kImageOps, _ImageOperands...);
		}

		//---------------------------------------------------------------------------------------------------
		// Gathers the requested component from four texels.
		template <
			class ReturnType = tex_sample_t<T>,
			spv::StorageClass C1,
			spv::StorageClass C2,
			spv::StorageClass C3,
			class TexCoordT = tex_coord_t<T>,
			class ...Ts, // image operands variables
			typename = std::enable_if_t<is_texture<T>>>
			var_t<ReturnType, Assemble, spv::StorageClassFunction> Gather(
				const var_t<sampler_t, Assemble, C1>& _Sampler,
				const var_t<TexCoordT, Assemble, C2>& _Coords,
				const var_t<uint32_t, Assemble, C3>& _Component, // Component is the component number that will be gathered from all four texels. It must be 0, 1, 2 or 3
				const TImageOperands _kImageOps = spv::ImageOperandsMaskNone, // number of bits set needs to equal number of _ImageOperands arguments
				const Ts& ..._ImageOperands) const
		{
			return TextureAccess<ReturnType>(MakeSampledImage(Type, Load(), _Sampler.Load()), _Coords, spv::OpImageGather, _Component.Load(), _kImageOps, _ImageOperands...);
		}
#pragma endregion

#pragma region texture_size
		template <class Tex = T, class ...Ts> // args must be emty or var_t<int32> for LoD
		inline std::enable_if_t<is_texture<Tex>, var_t<vec_type_t<int32_t, tex_real_dim_v<Tex>>, Assemble, spv::StorageClassFunction>> Dimensions(const Ts& ... _args) const
		{
			auto var = var_t<vec_type_t<int32_t, tex_real_dim_v<Tex>>, Assemble, spv::StorageClassFunction>(TIntermediate());

			constexpr size_t uArgs = sizeof...(_args);

			std::vector<SPIRVOperand> Operands(1u, SPIRVOperand::Intermediate(Load()));

			if constexpr(Assemble)
			{
				spv::Op kSizeOp = spv::OpNop;
				if constexpr (uArgs > 0)
				{
					const auto& lod = get_first_var(_args...);
					//using LodType = decltype(lod);
					//static_assert(is_integer_type<typename LodType::ValueType>, "LoD argument type must be int32_t");

					kSizeOp = spv::OpImageQuerySizeLod;
					Operands.push_back(SPIRVOperand::Intermediate(lod.Load()));
				}
				else
				{
					kSizeOp = spv::OpImageQuerySize;
				}

				var.uResultId = GlobalAssembler.EmplaceOperation(kSizeOp, var.uTypeId, std::move(Operands));
			}
			else
			{
				// TODO: no image size info implemented atm
			}

			return var;
		}
#pragma endregion

	private:

		template <class... Ts>
		void InitVar(const Ts& ..._args);

#pragma region InsertComponent
		// identity
		template <
			size_t Dim,
			uint32_t v0,
			uint32_t v1 = HUNDEFINED32,
			uint32_t v2 = HUNDEFINED32,
			uint32_t v3 = HUNDEFINED32,
			spv::StorageClass C1,
			typename = std::enable_if_t<is_vector<T> && Dim == Dimension<T> && Monotonic<Dim, v0, v1, v2, v3>>>
			const var_t& InsertComponent(const var_t<T, Assemble, C1>& _Var) const
		{
			return operator=(_Var);
		}

		// swizzle / shuffle
		template <
			size_t Dim,
			uint32_t v0,
			uint32_t v1 = HUNDEFINED32,
			uint32_t v2 = HUNDEFINED32,
			uint32_t v3 = HUNDEFINED32,
			spv::StorageClass C1,
			class VecT = vec_type_t<BaseType, Dim>,
			typename = std::enable_if_t<is_vector<T>>>
			const var_t& InsertComponent(const var_t<VecT, Assemble, C1>& _Var) const
		{
			if constexpr(Assemble == false)
			{
				if constexpr(Dim > 1)
				{
					if constexpr(is_valid_index<T, v0>() && is_valid_index<VecT, 0>()) Value[v0] = _Var.Value[0];
					if constexpr(is_valid_index<T, v1>() && is_valid_index<VecT, 1>()) Value[v1] = _Var.Value[1];
					if constexpr(is_valid_index<T, v2>() && is_valid_index<VecT, 2>()) Value[v2] = _Var.Value[2];
					if constexpr(is_valid_index<T, v3>() && is_valid_index<VecT, 3>()) Value[v3] = _Var.Value[3];
				}
				else
				{
					if constexpr(Dimension<T> > 1 && is_valid_index<T, v0>())
					{
						Value[v0] = _Var.Value;
					}
					else
					{
						Value = _Var.Value;
					}
				}
			}
			else if (uSpecConstId == HUNDEFINED32)
			{
				constexpr uint32_t N = Dimension<T>;
				Load();
				_Var.Load();

				if constexpr(Dim == 1u)
				{
                    constexpr uint32_t uDest = hlx::min(v0, v1, v2, v3);
                    static_assert(uDest < N, "Invalid destination index");

					uResultId = GlobalAssembler.EmplaceOperation(
                        spv::OpCompositeInsert,
                        uTypeId,
                        SPIRVOperand::Intermediate(_Var.uResultId), // part to insert
                        SPIRVOperand::Intermediate(uResultId),  // compsite object
                        SPIRVOperand::Literal(uDest) // destination
                    );
				}
				else
				{
					// vector 1 (this) + vector 2
					// xyzw xy
					// 0123 45
					// vector1.xz = vector2.xy
					// 4153

					const std::array<uint32_t, 4> Indices = { v0, v1, v2, v3 };
					std::vector<uint32_t> Target(N);

					uint32_t n = N;
					for (uint32_t i = 0; i < N; ++i)
					{
						const uint32_t& j = Indices[i];
						Target[i] = i;// copy from vector 1
						if (j < Dim)
						{
							Target[j] = n++; // take from concated vector 2
						}
					}
					//HASSERT(n == Dim+N, "Index missmatch");

					SPIRVOperation OpVectorShuffle(spv::OpVectorShuffle, uTypeId);
					OpVectorShuffle.AddIntermediate(uResultId); // vector 1
					OpVectorShuffle.AddIntermediate(_Var.uResultId); // vector 2
					OpVectorShuffle.AddLiterals(Target);

					uResultId = GlobalAssembler.AddOperation(std::move(OpVectorShuffle));
				}

				Store();
			}

			return *this;
		}

#pragma endregion

#pragma region ExtractComponent		
		// swizzle / shuffle
		template <
			size_t Dim,
			uint32_t v0,
			uint32_t v1 = HUNDEFINED32,
			uint32_t v2 = HUNDEFINED32,
			uint32_t v3 = HUNDEFINED32,
			class VecT = vec_type_t<BaseType, Dim>> // not a struct
			var_t<VecT, Assemble, spv::StorageClassFunction> ExtractComponent() const
		{
			auto var = var_t<VecT, Assemble, spv::StorageClassFunction>(TIntermediate());

			if constexpr(Assemble == false)
			{
				if constexpr(Dim > 1)
				{
					if constexpr(is_valid_index<T, v0>()) var.Value[0] = Value[v0];
					if constexpr(is_valid_index<T, v1>()) var.Value[1] = Value[v1];
					if constexpr(is_valid_index<T, v2>()) var.Value[2] = Value[v2];
					if constexpr(is_valid_index<T, v3>()) var.Value[3] = Value[v3];
				}
				else
				{
					var.Value = Value[v0];
				}
			}
			else // Assemble
			{
				Load();

				// identity
				if constexpr(std::is_same_v<VecT, T> && Monotonic<Dim, v0, v1, v2, v3>)
				{
					var.uResultId = uResultId;
					return var;
				}

				const uint64_t uComponentHash = hlx::Hash(Dim, v0, v1, v2, v3);
				auto comp_it = ExtractedComponents.find(uComponentHash);
				
				// check if this component has already been extracted and variable was not overwritten since then
				if (comp_it != ExtractedComponents.end())
				{
					const ComponentInfo& Comp = comp_it->second;
					if (Comp.uLastStoredId == GetLastStore())
					{
						var.uResultId = Comp.uComponentId;
						return var;
					}
				}

				const uint32_t uElemTypeId = GlobalAssembler.AddType(SPIRVType::FromType<base_type_t<T>>());
				std::array<uint32_t, 4> Indices = { v0, v1, v2, v3 };
				SPIRVOperation Op;

				if constexpr(Dim > 1)
				{
					if constexpr(std::is_same_v<VecT, T>)// VectorShuffle
					{
						Op = SPIRVOperation(spv::OpVectorShuffle, var.uTypeId);
						Op.AddIntermediate(uResultId); // comp1
						Op.AddIntermediate(uResultId); // comp2
						for (const uint32_t& i : Indices)
						{
							if (i < 4u)
							{
								Op.AddLiteral(i); // extraction index
							}
						}
					}
					else // extract and construct
					{
						Op = SPIRVOperation(spv::OpCompositeConstruct, var.uTypeId);
						for (const uint32_t& i : Indices)
						{
							if (i < 4u)
							{
								Op.AddIntermediate(GlobalAssembler.EmplaceOperation(
                                    spv::OpCompositeExtract,
                                    uElemTypeId,
                                    SPIRVOperand::Intermediate(uResultId), // var id to extract from
                                    SPIRVOperand::Literal(i))  // extraction index
                                );
							}
						}
					}
				}
				else // Dim == 1
				{
					// TODO: use AccessChain instead?
					Op = SPIRVOperation(
                        spv::OpCompositeExtract,
                        uElemTypeId,
                        SPIRVOperand::Intermediate(uResultId), // var id to extract from
                        SPIRVOperand::Literal(v0) // extraction index
                    ); 
				}

				var.uResultId = GlobalAssembler.AddOperation(std::move(Op));

				// cache extracted component
				ComponentInfo Comp{};

				Comp.uLastStoredId = GetLastStore();
				Comp.uComponentId = var.uResultId;

				ExtractedComponents.insert_or_assign(uComponentHash, Comp);
			}

			return var;
		}
#pragma endregion

	private:
		// two operands (self + other) mutible
		template <class U, class OpFunc, spv::StorageClass C1, class ...Ops>
		const var_t<T, Assemble, Class>& make_op2(const var_t<U, Assemble, C1>& _Other, const OpFunc& _OpFunc, const Ops ..._Ops) const;

		// one operand (self) immutable
		template <class OpFunc, class ...Ops>
		var_t<T, Assemble, spv::StorageClassFunction> make_op1_immutable(const OpFunc& _OpFunc, const Ops ..._Ops) const;

		// one operand (self) mutable
		template <class OpFunc, class ...Ops>
		const var_t<T, Assemble, spv::StorageClassFunction>& make_op1_mutable(const OpFunc& _OpFunc, const Ops ..._Ops) const;
	};

	//---------------------------------------------------------------------------------------------------
	// HELPER FUNCTIONS
	//---------------------------------------------------------------------------------------------------
#pragma region helper_functions
	//---------------------------------------------------------------------------------------------------

	// intermediate converts V to U
	template <class U, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_convertible<U, V> && !std::is_same_v<U, V>>>
	inline var_t<U, Assemble, spv::StorageClassFunction> spv_cast(const var_t<V, Assemble, C1>& _Other)
	{
		auto var = var_t<U, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = (U)_Other.Value;
		}
		else
		{
			var.uResultId = convert_op<U, V>(_Other);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	template <class T>
	inline uint32_t OpTypeDecider(const uint32_t _kOp)
	{
		return _kOp;
	}

	template <class OperandType>
	uint32_t OpTypeDecider(const uint32_t _FloatOp, const uint32_t _SIntOp, const uint32_t _UIntOp = spv::OpNop, const spv::Op _BoolOp = spv::OpNop)
	{
		if (std::is_same_v<OperandType, float>)
			return _FloatOp;

		if (std::is_same_v<OperandType, bool>)
			return _BoolOp;

		if (_UIntOp == spv::OpNop)
		{
			if (std::is_same_v<OperandType, int32_t> || std::is_same_v<OperandType, uint32_t>)
				return _SIntOp;
		}
		else
		{
			if (std::is_same_v<OperandType, int32_t>)
				return _SIntOp;
			else if (std::is_same_v<OperandType, uint32_t>)
				return _UIntOp;
		}

		return spv::OpNop;
	}

	template <class Result, class Operand1 = Result, class Operand2 = Result, class Operand3 = Result, class ...Ops>
	uint32_t OpTypeDeciderEx(const EOpTypeBase _kOpBase, const Ops ..._Ops)
	{
		if constexpr(sizeof...(_Ops) == 1)
		{
			return OpTypeDecider<base_type_t<Result>>(_Ops...);
		}
		else
		{
			switch (_kOpBase)
			{
			case kOpTypeBase_Result: return OpTypeDecider<base_type_t<Result>>(_Ops...);
			case kOpTypeBase_Operand1: return OpTypeDecider<base_type_t<Operand1>>(_Ops...);
			case kOpTypeBase_Operand2: return OpTypeDecider<base_type_t<Operand2>>(_Ops...);
			case kOpTypeBase_Operand3: return OpTypeDecider<base_type_t<Operand3>>(_Ops...);
			default: return spv::OpNop;
			}
		}
	}

	//---------------------------------------------------------------------------------------------------

	template <class U, spv::StorageClass C1, class ...Ts>
	inline void LoadVariables(const var_t<U, true, C1>& var, const Ts& ... vars)
	{
		var.Load();

		if constexpr(sizeof...(vars) > 0)
		{
			LoadVariables(vars...);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// make operation with mutable operation with two operands (self + other)
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, class OpFunc, spv::StorageClass C1, class ...Ops>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::make_op2(const var_t<U, Assemble, C1>& _Other, const OpFunc& _OpFunc, const Ops ..._Ops) const
	{
		if constexpr(Assemble == false)
		{
			_OpFunc(Value, _Other.Value);
		}
		else if(uSpecConstId == HUNDEFINED32) // Assemble
		{
			LoadVariables(*this, _Other);

			const spv::Op kOpCode = (spv::Op)OpTypeDecider<BaseType>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			uResultId = GlobalAssembler.EmplaceOperation(
                kOpCode,
                uTypeId,  // result type
                SPIRVOperand(kOperandType_Intermediate, uResultId),
                SPIRVOperand(kOperandType_Intermediate, _Other.uResultId)
            );

			Store();
		}

		return *this;
	}

	//---------------------------------------------------------------------------------------------------
	// make immutable operation (returns intermediate var) with one operand (self)
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class OpFunc, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> var_t<T, Assemble, Class>::make_op1_immutable(const OpFunc& _OpFunc, const Ops ..._Ops) const
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(Value);
		}
		else // Assemble
		{
			Load();

			const spv::Op kOpCode = (spv::Op)OpTypeDecider<BaseType>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");
			HASSERT(uTypeId != HUNDEFINED32, "Invalid type");

			var.uResultId = GlobalAssembler.EmplaceOperation(kOpCode, uTypeId, SPIRVOperand(kOperandType_Intermediate, uResultId));
		}

		return var;
	}
	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class OpFunc, class ...Ops>
	inline const var_t<T, Assemble, spv::StorageClassFunction>& var_t<T, Assemble, Class>::make_op1_mutable(const OpFunc& _OpFunc, const Ops ..._Ops) const
	{
		if constexpr(Assemble == false)
		{
			_OpFunc(Value);
		}
		else if(uSpecConstId == HUNDEFINED32) // Assemble
		{
			Load();

			const spv::Op kOpCode = (spv::Op)OpTypeDecider<BaseType>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

            uResultId = GlobalAssembler.EmplaceOperation(kOpCode, uTypeId, SPIRVOperand(kOperandType_Intermediate, uResultId));

			Store();
		}

		return *this;
	}
	//---------------------------------------------------------------------------------------------------

#pragma endregion

	//---------------------------------------------------------------------------------------------------
	// assignment operator
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator=(const U& _Other) const
	{
		if constexpr (is_var<U>)
		{
			if constexpr (Assemble)
			{
				if constexpr(std::is_same_v<U::ValueType, T>)
				{
					var_decoration<Assemble>::operator=(_Other);
				}
				else
				{
					constexpr bool bConvertible = is_convertible<U::ValueType, BaseType> && Dimension<U::ValueType> == Dimension<T>;
					static_assert(bConvertible, "Types not convertible");

					_Other.Load();

					const spv::Op kType = GetConvertOp<U, T>();
					HASSERT(kType != spv::OpNop, "Invalid variable type conversion!");

					uResultId = GlobalAssembler.EmplaceOperation(kType, uTypeId, SPIRVOperand(kOperandType_Intermediate, _Other.uResultId));
					Store();
				}
			}
			else
			{
				Value = (T)_Other.Value;
			}
		}
		else // constant assignment
		{
			if constexpr (Assemble)
			{
				var_decoration<Assemble>::operator=(make_const<Assemble>((T)_Other));
			}
			else
			{
				Value = (T)_Other;
			}
		}
		return *this;
	}

	//---------------------------------------------------------------------------------------------------
	// CONSTRUCTORS
	//---------------------------------------------------------------------------------------------------

#pragma region constructors
	//---------------------------------------------------------------------------------------------------
	// copy constructor
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline var_t<T, Assemble, Class>::var_t(const var_t<T, Assemble, C1>& _Other) :
		var_decoration<Assemble>(_Other),
		Value(_Other.Value)
	{
	}

	//---------------------------------------------------------------------------------------------------
	// name constructor
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, Class>::var_t(const char* _sName) :
		var_decoration<Assemble>(Class)
	{
		SetName(_sName);
		InitVar();
	}

	//---------------------------------------------------------------------------------------------------
	// name constructor
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, Class>::var_t(std::string_view _sName) : 
		var_decoration<Assemble>(Class)
	{
		SetName(std::string(_sName.data(), _sName.size()));
		InitVar();
	}

	//---------------------------------------------------------------------------------------------------
	// set, binding & location helper
	template<typename T, bool Assemble, spv::StorageClass Class>
	void LocationHelper(var_t<T, Assemble, Class>& _Var, const uint32_t _uLocation, const bool _bInput)
	{
		if constexpr(Assemble)
		{
			uint32_t uLocation = _uLocation != HUNDEFINED32 ? _uLocation : (_bInput ? GlobalAssembler.GetCurrentInputLocation() : GlobalAssembler.GetCurrentOutputLocation());
			HASSERT(uLocation != HUNDEFINED32, "Invalid location for variable %s", _Var.sName.c_str());
			_Var.SetLocation(uLocation);
		}
	}

	template<typename T, bool Assemble, spv::StorageClass Class>
	void BindingSetHelper(var_t<T, Assemble, Class>& _Var, const uint32_t _uBinding, const uint32_t _uSet)
	{
		if constexpr(Assemble)
		{
			uint32_t uSet = _uSet != HUNDEFINED32 ? _uSet : GlobalAssembler.GetDefaultSet();
			uint32_t uBinding = _uBinding != HUNDEFINED32 ? _uBinding : GlobalAssembler.GetCurrentBinding(uSet);
			HASSERT(uBinding != HUNDEFINED32 && uSet != HUNDEFINED32, "Invalid set and binding for variable %s", _Var.sName.c_str());
			_Var.SetBinding(uBinding, uSet);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// input variable constructor
	template <typename T, bool Assemble = true, uint32_t Location = HUNDEFINED32, bool InstanceData = false>
	struct var_in_t : public var_t<T, Assemble, spv::StorageClassInput>
	{
		template<class ...Ts>
		var_in_t(const Ts& ...args) : var_t<T, Assemble, spv::StorageClassInput>(args...) { LocationHelper(*this, Location, true); bInstanceData = InstanceData; }
		
		template <spv::StorageClass C1>
		const var_in_t& operator=(const var_t<T, Assemble, C1>& _Other) const { var_t<T, Assemble, spv::StorageClassInput>::operator=(_Other); return *this; }
	};
	//---------------------------------------------------------------------------------------------------
	// output variable constructor
	template <typename T, bool Assemble = true, uint32_t Location = HUNDEFINED32>
	struct var_out_t : public var_t<T, Assemble, spv::StorageClassOutput>
	{
		template<class ...Ts>
		var_out_t(const Ts& ...args) : var_t<T, Assemble, spv::StorageClassOutput>(args...) { LocationHelper(*this, Location, false); }
	};
	//---------------------------------------------------------------------------------------------------
	// uniform variable constructor
	template <typename T, bool Assemble = true, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32>
	struct var_uniform_t : public var_t<T, Assemble, spv::StorageClassUniform>
	{
		template<class ...Ts>
		var_uniform_t(const Ts& ...args) : var_t<T, Assemble, spv::StorageClassUniform>(args...) { BindingSetHelper(*this, Binding, Set); }
	};
	//---------------------------------------------------------------------------------------------------
	// uniform constant variable constructor
	template <typename T, bool Assemble = true, uint32_t Binding = HUNDEFINED32, uint32_t Set = HUNDEFINED32, uint32_t Location = HUNDEFINED32>
	struct var_uniform_constant_t : public var_t<T, Assemble, spv::StorageClassUniformConstant>
	{
		template<class ...Ts>
		var_uniform_constant_t(const Ts& ...args) : var_t<T, Assemble, spv::StorageClassUniformConstant>(args...) { BindingSetHelper(*this, Binding, Set); LocationHelper(*this, Location, true); }
	};

	//---------------------------------------------------------------------------------------------------
	// Specialization constant constructor
	template <typename T, bool Assemble = true, uint32_t SpecId = HUNDEFINED32>
	struct var_spec_const_t : public var_t<T, Assemble, spv::StorageClassMax>
	{
		template <class ...Ts>
		var_spec_const_t(const Ts&... _args) : var_t<T, Assemble, spv::StorageClassMax>(TIntermediate())
		{
			if constexpr(Assemble)
			{
				constexpr size_t uArgs = sizeof...(_args);
				static_assert(uArgs > 0, "Speialization constant needs default values");

				if constexpr(uArgs > 0)
				{
					SPIRVConstant Constant = SPIRVConstant::Make(va_type_var(_args...), true);
					uResultId = GlobalAssembler.AddConstant(Constant);

					uSpecConstId = (SpecId != HUNDEFINED32) ? SpecId : GlobalAssembler.GetCurrentSpecConstId();
					HASSERT(uSpecConstId != HUNDEFINED32, "Unspecified specialization constant id");

					GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationSpecId, uSpecConstId).MakeOperation(uResultId));
				}
			}
		}
		// todo: delete assignment/copy operators/constructors
	};

	//---------------------------------------------------------------------------------------------------
	// subpass constructor
	template <typename T, bool Assemble = true, bool Depth = false, uint32_t InputAttachmentIndex = HUNDEFINED32, class SubT = cond_t<Depth, tex_depth_subpass_t<T>, tex_color_subpass_t<T>>>
	struct var_subpass_t : public var_t<SubT, Assemble, spv::StorageClassUniformConstant>
	{
		template <class ...Ts>
		var_subpass_t(const Ts&... _args) : var_t<SubT, Assemble, spv::StorageClassUniformConstant>(_args...)
		{
			if constexpr(Assemble)
			{
				uInputAttachmentIndex = (InputAttachmentIndex != HUNDEFINED32) ? InputAttachmentIndex : GlobalAssembler.GetCurrentInputAttchmentIndex();
				HASSERT(uInputAttachmentIndex != HUNDEFINED32, "Invalid input attachment index for variable %s", sName.c_str());
				
				GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationInputAttachmentIndex, uInputAttachmentIndex).MakeOperation(uVarId));
			}
		}
	};

	//---------------------------------------------------------------------------------------------------
	// push constant constructor
	template <typename T, bool Assemble = true>
	struct var_push_const_t : public var_t<T, Assemble, spv::StorageClassPushConstant>
	{
	};

	//---------------------------------------------------------------------------------------------------
	// builtin variables
	template <spv::BuiltIn kBuiltIn, class T, bool Assemble, spv::StorageClass Class>
	struct var_builtin_t : public var_t<T, Assemble, Class>
	{
		var_builtin_t(const T& _DefaultValue = {}) : var_t<T, Assemble, Class>(_DefaultValue)
		{
			if constexpr(Assemble)
			{
				bBuiltIn = true;
				Decorate(SPIRVDecoration(spv::DecorationBuiltIn, kBuiltIn));
			}
		}
	};

	//---------------------------------------------------------------------------------------------------
	// per vertex builtin
	template<bool Assemble>
	struct var_per_vertex_t
	{
		SPVStruct
		SPVBuiltIn

		var_t<float4_t, Assemble, spv::StorageClassOutput> kPostion;
		var_t<float, Assemble, spv::StorageClassOutput> kPointSize;

		//https://www.khronos.org/opengl/wiki/Built-in_Variable_(GLSL)
		// these are actually arrays of userdefined size:
		//var_t<float, Assemble, spv::StorageClassOutput> kClipDistance;
		//var_t<float, Assemble, spv::StorageClassOutput> kCullDistance;
	};

	template <bool Assemble = true>
	struct var_per_vertex : public var_t<var_per_vertex_t<Assemble>, Assemble, spv::StorageClassOutput>
	{
		var_per_vertex() : VarType() //var_t<var_per_vertex_t<Assemble>, Assemble, spv::StorageClassOutput>()
		{
			if constexpr(Assemble)
			{
				bBuiltIn = true;
				Value.kPostion.bBuiltIn = true;
				Value.kPointSize.bBuiltIn = true;
				//Value.kClipDistance.bBuiltIn = true;
				//Value.kCullDistance.bBuiltIn = true;

				GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationBuiltIn, spv::BuiltInPosition).MakeOperation(uTypeId, Value.kPostion.uMemberIndex));
				GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationBuiltIn, spv::BuiltInPointSize).MakeOperation(uTypeId, Value.kPointSize.uMemberIndex));
				//GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationBuiltIn, spv::BuiltInClipDistance).MakeOperation(uTypeId, Value.kClipDistance.uMemberIndex));
				//GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationBuiltIn, spv::BuiltInCullDistance).MakeOperation(uTypeId, Value.kCullDistance.uMemberIndex));
			}
		}
	};

	//---------------------------------------------------------------------------------------------------
	// re-initialize struct member variable
	template <class T, spv::StorageClass Class>
	void InitVar(var_t<T, true, Class>& _Member, SPIRVType& _Type, std::vector<uint32_t> _AccessChain, const spv::StorageClass _kStorageClass, uint32_t& _uCurOffset, uint32_t& _uCurBoundary)
	{
		// override var id from previous init (should be generated on load with access chain)
		_Member.uVarId = HUNDEFINED32;
		// actual stuff happening here
		_Member.AccessChain = _AccessChain;
		_Member.kStorageClass = _kStorageClass;

		// translate bool members to int (taken from example)
		using VarT = std::conditional_t<std::is_same_v<T, bool>, int32_t, T>;

		_Member.Type = SPIRVType::FromType<VarT>();
		_Member.uTypeId = GlobalAssembler.AddType(_Member.Type);
		_Type.Member(_Member.Type); // struct type

		// member offset, check for 16byte allignment
		if (_uCurOffset + sizeof(VarT) <= _uCurBoundary)
		{
			_Member.uMemberOffset = _uCurOffset;
		}
		else
		{
			_Member.uMemberOffset = _uCurBoundary;
			_uCurBoundary += kAlignmentSize;
		}

		_uCurOffset += sizeof(VarT);
	}
	//---------------------------------------------------------------------------------------------------
	// recursively initialize all struct members
	template <size_t n, size_t N, class T>
	void InitStruct(
		T& _Struct,
		SPIRVType& _Type,
		std::vector<var_decoration<true>*>& _Members,
		std::vector<uint32_t> _AccessChain,
		const uint32_t _uMemberIndex,
		const spv::StorageClass _kStorageClass,
		uint32_t& _uCurOffset,
		uint32_t& _uCurBoundary)
	{
		if constexpr(n < N && has_struct_tag<T>::value)
		{
			uint32_t uIndex = _uMemberIndex;
			auto& member = hlx::get<n>(_Struct);
			using MemberType = std::remove_reference_t<std::remove_cv_t<decltype(member)>>;

			if constexpr(has_struct_tag<MemberType>::value)
			{
				member.uMemberIndex = uIndex++;
				_AccessChain.push_back(member.uMemberIndex);
				SPIRVType NestedType(spv::OpTypeStruct);
				InitStruct<0, hlx::aggregate_arity<decltype(member)>, MemberType>(member, NestedType, _AccessChain, uIndex, _kStorageClass, _uCurOffset, _uCurBoundary);
				_Type.Member(NestedType);
			}
			else if constexpr(has_var_tag<MemberType>::value)
			{
				member.uMemberIndex = uIndex++;
				std::vector<uint32_t> FinalChain(_AccessChain);
				FinalChain.push_back(member.uMemberIndex);
				InitVar(member, _Type, FinalChain, _kStorageClass, _uCurOffset, _uCurBoundary);
				_Members.push_back(&member);
			}

			InitStruct<n + 1, N, T>(_Struct, _Type, _Members, _AccessChain, uIndex, _kStorageClass, _uCurOffset, _uCurBoundary);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// extract all components from any T that is of var_t<> type and pass the index to _Op as an argument
	// non var_t<> type arguments are converted to spirv constants and passed to _Op
	template <class T, class ...Ts>
	void ExtractCompnents(SPIRVOperation& _Op, const T& _First, const Ts& ..._Rest)
	{
		if constexpr(is_var<T>)
		{
			using VarT = decltype(_First.Value);
			constexpr size_t N = Dimension<VarT>;
			uint32_t uTypeId = GlobalAssembler.AddType(SPIRVType::FromType<base_type_t<VarT>>());
			_First.Load();

			if constexpr(N == 1)
			{
				// directly take the result id
				_Op.AddIntermediate(_First.uResultId);
			}
			else
			{
				// extract all components of variable
				for (uint32_t n = 0u; n < N; ++n)
				{
					SPIRVOperation OpExtract(spv::OpCompositeExtract, uTypeId, SPIRVOperand(kOperandType_Intermediate, _First.uResultId)); // var id to extract from
					OpExtract.AddLiterals(_First.AccessChain); // can be empty
					OpExtract.AddLiteral(n); // extraction index

					_Op.AddIntermediate(GlobalAssembler.AddOperation(std::move(OpExtract)));
				}
			}
		}
		else
		{
			// create component constant
			_Op.AddIntermediate(GlobalAssembler.AddConstant(SPIRVConstant::Make(_First)));
		}

		constexpr size_t uArgs = sizeof...(_Rest);
		if constexpr(uArgs > 0)
		{
			ExtractCompnents(_Op, _Rest...);
		}
	}

	//---------------------------------------------------------------------------------------------------
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class ...Ts>
	inline void var_t<T, Assemble, Class>::InitVar(const Ts& ..._args)
	{
		constexpr size_t uArgs = sizeof...(_args);
		if constexpr(Assemble)
		{
			std::vector<var_decoration<true>*> Members;
			if constexpr(has_struct_tag<T>::value)
			{
				static_assert(uArgs == 0, "spv struct can't be value initialized");
				Type = SPIRVType::Struct();

				uint32_t uMemberOffset = 0u;
				uint32_t uAlignmentBoundary = kAlignmentSize;
				InitStruct<0, hlx::aggregate_arity<T>, T>(Value, Type, Members, {}, 0u, kStorageClass, uMemberOffset, uAlignmentBoundary);

				HASSERTD(Type == SPIRVType::FromType<T>(), "Reconstructed type mismatch");

				uTypeId = GlobalAssembler.AddType(Type);
				GlobalAssembler.AddOperation(SPIRVDecoration(spv::DecorationBlock).MakeOperation(uTypeId));
			}
			else
			{
				Type = SPIRVType::FromType<T>();
				uTypeId = GlobalAssembler.AddType(Type);
			}

			// pointer type
			const uint32_t uPtrTypeId = GlobalAssembler.AddType(SPIRVType::Pointer(Type, kStorageClass));

			// OpVariable:
			// Allocate an object in memory, resulting in a pointer to it, which can be used with OpLoad and OpStore.
			// Result Type must be an OpTypePointer. Its Type operand is the type of object in memory.
			// Storage Class is the Storage Class of the memory holding the object. It cannot be Generic.
			// Initializer is optional. If Initializer is present, it will be the initial value of the variable’s memory content.
			// Initializer must be an <id> from a constant instruction or a global(module scope) OpVariable instruction.
			// Initializer must have the same type as the type pointed to by Result Type.

			// argument list has var_t<> initializers
			constexpr bool bHasVar = has_var<Ts...>;
			if constexpr(bHasVar && uArgs > 1u)
			{
                SPIRVOperation OpCreateVar(spv::OpCompositeConstruct, uTypeId); // uPtrTypeId
				ExtractCompnents(OpCreateVar, _args...);

				// composite constructs treated as intermediates as they cant be loaded
				uResultId = GlobalAssembler.AddOperation(std::move(OpCreateVar));
			}
			else
			{
				SPIRVOperation OpCreateVar(spv::OpVariable, uPtrTypeId, // result type
					SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(kStorageClass))); // variable storage location	

				if constexpr(bHasVar) // exactly one var
				{
					// convert to T
					uResultId = convert_op<T>(_args...);
				}
				else if constexpr(uArgs > 0u)
				{
					OpCreateVar.AddIntermediate(GlobalAssembler.AddConstant(SPIRVConstant::Make(va_type_var(_args...))));
				}

				uVarId = GlobalAssembler.AddOperation(std::move(OpCreateVar), &pVarOp);
			}

			// correct sturct member variables
			for (var_decoration<true>* pMember : Members)
			{
				pMember->uBaseId = uVarId;
				pMember->uBaseTypeId = uTypeId;

				// fix storage class in OpVar
				{
					HASSERT(pVarOp != nullptr && pVarOp->GetOpCode() == spv::OpVariable, "Invalid variable op");
					auto& Operands = pMember->pVarOp->GetOperands();
					HASSERT(Operands.size() > 0u, "Invalid number of variable operands");
					Operands.front().uId = (uint32_t)kStorageClass;
				}

				// builtin types dont have offsets
				if constexpr(is_builtin<T> == false)
				{
					// Create member offset decoration
					SPIRVDecoration MemberDecl(spv::DecorationOffset, pMember->uMemberOffset, pMember->AccessChain.back());
					GlobalAssembler.AddOperation(MemberDecl.MakeOperation(uTypeId));
				}
			}
		}
	}

	//---------------------------------------------------------------------------------------------------
	// the all mighty variable default constructor
	template<typename T, bool Assemble, spv::StorageClass C1>
	template<class ...Ts>
	inline var_t<T, Assemble, C1>::var_t(const Ts& ..._args) :
		var_decoration<Assemble>(C1),
		Value(get_arg_value(_args)...)
	{
		InitVar(_args...);
	}

	//---------------------------------------------------------------------------------------------------
	// Intermediate variable constructor
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class ...Ts>
	inline var_t<T, Assemble, Class>::var_t(TIntermediate, const Ts& ..._args) :
		var_decoration<Assemble>(Class),
		Value(_args...)
	{
		if constexpr(Assemble)
		{
			Type = SPIRVType::FromType<T>();
			uTypeId = GlobalAssembler.AddType(Type);
			if constexpr (sizeof...(_args) > 0)
			{
				uResultId = GlobalAssembler.AddConstant(SPIRVConstant::Make(va_type_var(_args...)));
			}
		}
	}

#pragma endregion

	//---------------------------------------------------------------------------------------------------
	// OPERATIONS
	//---------------------------------------------------------------------------------------------------
#pragma region Operations

	//---------------------------------------------------------------------------------------------------
	// mutable add
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator+=(const var_t<T, Assemble, C1>& _Other) const
	{
		return make_op2(_Other, [](T& v1, const T& v2) { v1 += v2; }, spv::OpFAdd, spv::OpIAdd);
	}

	//---------------------------------------------------------------------------------------------------
	// mutable sub
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator-=(const var_t<T, Assemble, C1>& _Other) const
	{
		return make_op2(_Other, [](T& v1, const T& v2) { v1 -= v2; }, spv::OpFSub, spv::OpISub);
	}

	//---------------------------------------------------------------------------------------------------
	// mutable mul
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator*=(const var_t<U, Assemble, C1>& _Other) const
	{
		// square matrix mul
		if constexpr(is_square_matrix<T> && std::is_same_v<T, U>)
			return make_op2(_Other, [](T& v1, const U& v2) { v1 *= v2; }, spv::OpMatrixTimesMatrix);
		if constexpr(is_vector<T> && is_scalar<U>)
			return make_op2(_Other, [](T& v1, const U& v2) { v1 *= v2; }, spv::OpVectorTimesScalar);
		else
			return make_op2(_Other, [](T& v1, const U& v2) { v1 *= v2; }, spv::OpFMul, spv::OpIMul);
	}


	//---------------------------------------------------------------------------------------------------
	// mutable div
	template<typename T, bool Assemble, spv::StorageClass Class>
	template<class U, spv::StorageClass C1>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator/=(const var_t<U, Assemble, C1>& _Other) const
	{
		static_assert(std::is_same_v<T, U>, "Unsupported result type");
		return make_op2(_Other, [](T& v1, const U& v2) { v1 /= v2; }, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
	}

	//---------------------------------------------------------------------------------------------------
	// logical negation
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> var_t<T, Assemble, Class>::operator!() const
	{
		return make_op1_immutable([](T& _Value) -> T { return !_Value; }, spv::OpLogicalNot);
	}

	// increment mutable
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator++() const
	{
		static_assert(hlx::is_of_type<T, float, double, int32_t, uint32_t>(), "Incompatible variable type");
		return make_op2(make_const<Assemble>((T)1), [](T& v1, const T& v2) { v1 += v2; }, spv::OpFAdd, spv::OpIAdd);
	}

	// increment immutable
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> var_t<T, Assemble, Class>::operator++(int) const
	{
		var_t<T, Assemble, spv::StorageClassFunction> PreEval(*this);
		++(*this); // call mutable increment
		return PreEval;
	}

	// decrement mutable
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline const var_t<T, Assemble, Class>& var_t<T, Assemble, Class>::operator--() const
	{
		static_assert(hlx::is_of_type<T, float, double, int32_t, uint32_t>(), "Incompatible variable type");
		return make_op2(make_const<Assemble>((T)1), [](T& v1, const T& v2) { v1 -= v2; }, spv::OpFSub, spv::OpISub);
	}
	//decrement immutable
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> var_t<T, Assemble, Class>::operator--(int) const
	{
		var_t<T, Assemble, spv::StorageClassFunction> PreEval(*this);
		--(*this); // call mutable decrement
		return PreEval;
	}
	// Arithmetic Negation
	template<typename T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> var_t<T, Assemble, Class>::operator-() const
	{
		return make_op1_immutable([](T& _Value) -> T { return -_Value; }, spv::OpFNegate, spv::OpSNegate);
	}
	//---------------------------------------------------------------------------------------------------
#pragma endregion

} // !Spear

#endif // !SPAR_SPIRVVARIABLE_H
