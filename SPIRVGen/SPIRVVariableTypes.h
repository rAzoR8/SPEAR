//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVVARIABLETYPES_H
#define SPEAR_SPIRVVARIABLETYPES_H

//http://glm.g-truc.net/0.9.8/glm-0.9.8.pdf
//#include <glm\fwd.hpp> // forward decls
#include <glm/glm.hpp> 
#include <vulkan\spirv.hpp>
#include "FunctionalUtils.h"
#include "Vector.h"

namespace Spear
{
	template <bool Cond, class U, class V>
	using cond_t = std::conditional_t<Cond, U, V>;

	using float2_t = glm::vec2;
	using float3_t = glm::vec3;
	using float4_t = glm::vec4;
	using quaternion_t = glm::quat;

	using int2_t = glm::i32vec2;
	using int3_t = glm::i32vec3;
	using int4_t = glm::i32vec4;
	
	using uint2_t = glm::u32vec2;
	using uint3_t = glm::u32vec3;
	using uint4_t = glm::u32vec4;

	using bool2_t = hlx::VecType<bool, 2>;
	using bool3_t = hlx::VecType<bool, 3>;
	using bool4_t = hlx::VecType<bool, 4>;

	using float2x2_t = glm::mat2x2;
	using float3x3_t = glm::mat3x3;
	using float3x4_t = glm::mat3x4; // transposed wrt to open gl
	using float4x3_t = glm::mat4x3; // transposed wrt to open gl
	using float4x4_t = glm::mat4x4;
	using matrix_t = glm::mat4x4;

#pragma region base_type
	template <class VecT>
	struct base_type { typedef std::false_type type; };

	template <>
	struct base_type<bool> { typedef bool type; };

	template <>
	struct base_type<bool2_t> { typedef bool type; };

	template <>
	struct base_type<bool3_t> { typedef bool type; };

	template <>
	struct base_type<bool4_t> { typedef bool type; };

	template <>
	struct base_type<float> { typedef float type; };

	template <>
	struct base_type<double> { typedef double type; };

	template <>
	struct base_type<float2_t> { typedef float type; };

	template <>
	struct base_type<float3_t> { typedef float type; };

	template <>
	struct base_type<float4_t> { typedef float type; };

	template <>
	struct base_type<quaternion_t> { typedef float type; };

	template <>
	struct base_type<int32_t> { typedef int32_t type; };

	template <>
	struct base_type<int64_t> { typedef int64_t type; };

	template <>
	struct base_type<int2_t> { typedef int32_t type; };

	template <>
	struct base_type<int3_t> { typedef int32_t type; };

	template <>
	struct base_type<int4_t> { typedef int32_t type; };

	template <>
	struct base_type<uint32_t> { typedef uint32_t type; };

	template <>
	struct base_type<uint64_t> { typedef uint64_t type; };

	template <>
	struct base_type<uint2_t> { typedef uint32_t type; };

	template <>
	struct base_type<uint3_t> { typedef uint32_t type; };

	template <>
	struct base_type<uint4_t> { typedef uint32_t type; };

	template <>
	struct base_type<float2x2_t> { typedef float type; };

	template <>
	struct base_type<float3x3_t> { typedef float type; };

	template <>
	struct base_type<float3x4_t> { typedef float type; };

	template <>
	struct base_type<float4x3_t> { typedef float type; };

	template <>
	struct base_type<float4x4_t> { typedef float type; };

	template <class VecT>
	using base_type_t = typename base_type<VecT>::type;
#pragma endregion

	template <class T>
	constexpr size_t Dimension = sizeof(T) / sizeof(base_type_t<T>);

#pragma region primitive_type

	// TODO: half, unorm etc
	template <class T>
	struct primitive_type { typedef std::false_type type; };

	template <>
	struct primitive_type<bool> { typedef bool type; };

	template <>
	struct primitive_type<float> { typedef float type; };

	template <>
	struct primitive_type<double> { typedef double type; };

	template <>
	struct primitive_type<int16_t> { typedef int16_t type; };

	template <>
	struct primitive_type<int32_t> { typedef int32_t type; };

	template <>
	struct primitive_type<int64_t> { typedef int64_t type; };

	template <>
	struct primitive_type<uint16_t> { typedef uint16_t type; };

	template <>
	struct primitive_type<uint32_t> { typedef uint32_t type; };

	template <>
	struct primitive_type<uint64_t> { typedef uint64_t type; };

	template <class T>
	using primitive_type_t = typename primitive_type<T>::type; //typename std::decay_t<T>
#pragma endregion

#pragma region col_type
	template <class MatrixT>
	struct col_type { typedef std::false_type type; };

	template<>
	struct col_type<float2x2_t> { typedef float2_t type; };

	template<>
	struct col_type<float3x3_t> { typedef float3_t type; };

	template<>
	struct col_type<float3x4_t> { typedef float4_t type; };

	template<>
	struct col_type<float4x3_t> { typedef float3_t type; };

	template<>
	struct col_type<float4x4_t> { typedef float4_t type; };

	template <class T>
	using col_type_t = typename col_type<T>::type;
#pragma endregion

#pragma region row_type
	template <class MatrixT>
	struct row_type { typedef std::false_type type; };

	template<>
	struct row_type<float2x2_t> { typedef float2_t type; };

	template<>
	struct row_type<float3x3_t> { typedef float3_t type; };

	template<>
	struct row_type<float3x4_t> { typedef float3_t type; };

	template<>
	struct row_type<float4x3_t> { typedef float4_t type; };

	template<>
	struct row_type<float4x4_t> { typedef float4_t type; };

	template <class T>
	using row_type_t = typename row_type<T>::type;
#pragma endregion

#pragma region mat_type
	template <class Row, class Col>
	struct mat_type { typedef std::false_type type; };

	template <>
	struct mat_type<float2_t, float2_t> { typedef float2x2_t type; };

	template <>
	struct mat_type<float3_t, float3_t> { typedef float3x3_t type; };

	template <>
	struct mat_type<float4_t, float3_t> { typedef float4x3_t type; };

	template <>
	struct mat_type<float3_t, float4_t> { typedef float3x4_t type; };

	template <>
	struct mat_type<float4_t, float4_t> { typedef float4x4_t type; };

	template <class Row, class Col>
	using mat_type_t = typename mat_type<Row, Col>::type;
#pragma endregion

#pragma region mat_type_dim
	template <class T, size_t Row, size_t Col>
	struct mat_type_dim { typedef std::false_type type; };

	template <>
	struct mat_type_dim<float, 2, 2> { typedef float2x2_t type; };

	template <>
	struct mat_type_dim<float, 3, 3> { typedef float3x3_t type; };

	template <>
	struct mat_type_dim<float, 3, 4> { typedef float3x4_t type; };

	template <>
	struct mat_type_dim<float, 4, 3> { typedef float4x3_t type; };

	template <>
	struct mat_type_dim<float, 4, 4> { typedef float4x4_t type; };

	template <class T, size_t Row, size_t Col>
	using mat_type_dim_t = typename mat_type_dim<T, Row, Col>::type;
#pragma endregion

#pragma region mat_dims
	template <class T, class Row = row_type_t<T>, class Col = col_type_t<T>>
	struct mat_dim { static constexpr uint32_t Rows = Dimension<Row>; static constexpr uint32_t Cols = Dimension<Col>; };
#pragma endregion

#pragma region va_type
	// create type from typelist
	template <class ...Ts>
	struct va_type { typedef std::false_type type; };

	template <>
	struct va_type<float> { typedef float type; };
	template <>
	struct va_type<float, float> { typedef float2_t type; };
	template <>
	struct va_type<float, float, float> { typedef float3_t type; };
	template <>
	struct va_type<float, float, float, float> { typedef float4_t type; };

	template <>
	struct va_type<float, float2_t> { typedef float3_t type; };

	template <>
	struct va_type<float2_t, float> { typedef float3_t type; };

	template <>
	struct va_type<float, float3_t> { typedef float4_t type; };

	template <>
	struct va_type<float3_t, float> { typedef float4_t type; };

	// todo: more variants

	template <>
	struct va_type<float2_t> { typedef float2_t type; };
	template <>
	struct va_type<float3_t> { typedef float3_t type; };
	template <>
	struct va_type<float4_t> { typedef float4_t type; };

	template <>
	struct va_type<double> { typedef double type; };

	template <>
	struct va_type<int32_t> { typedef int32_t type; };
	template <>
	struct va_type<int32_t, int32_t> { typedef int2_t type; };
	template <>
	struct va_type<int32_t, int32_t, int32_t> { typedef int3_t type; };
	template <>
	struct va_type<int32_t, int32_t, int32_t, int32_t> { typedef int4_t type; };

	template <>
	struct va_type<int2_t> { typedef int2_t type; };
	template <>
	struct va_type<int3_t> { typedef int3_t type; };
	template <>
	struct va_type<int4_t> { typedef int4_t type; };

	template <>
	struct va_type<int64_t> { typedef int64_t type; };

	template <>
	struct va_type<uint32_t> { typedef uint32_t type; };
	template <>
	struct va_type<uint32_t, uint32_t> { typedef uint2_t type; };
	template <>
	struct va_type<uint32_t, uint32_t, uint32_t> { typedef uint3_t type; };
	template <>
	struct va_type<uint32_t, uint32_t, uint32_t, uint32_t> { typedef uint4_t type; };

	template <>
	struct va_type<uint2_t> { typedef uint2_t type; };
	template <>
	struct va_type<uint3_t> { typedef uint3_t type; };
	template <>
	struct va_type<uint4_t> { typedef uint4_t type; };

	template <>
	struct va_type<uint64_t> { typedef uint64_t type; };

	template <>
	struct va_type<bool> { typedef bool type; };
	template <>
	struct va_type<bool, bool> { typedef bool2_t type; };
	template <>
	struct va_type<bool, bool, bool> { typedef bool3_t type; };
	template <>
	struct va_type<bool, bool, bool, bool> { typedef bool4_t type; };

	template <>
	struct va_type<bool2_t> { typedef bool2_t type; };
	template <>
	struct va_type<bool3_t> { typedef bool3_t type; };
	template <>
	struct va_type<bool4_t> { typedef bool4_t type; };

	template <>
	struct va_type<float2x2_t> { typedef float2x2_t type; };
	template <>
	struct va_type<float3x3_t> { typedef float3x3_t type; };
	template <>
	struct va_type<float3x4_t> { typedef float3x4_t type; };
	template <>
	struct va_type<float4x3_t> { typedef float4x3_t type; };
	template <>
	struct va_type<float4x4_t> { typedef float4x4_t type; };

	template <class ...Ts>
	using va_type_t = typename va_type<typename std::decay_t<Ts>...>::type;

	template <class ...Ts, class Ret = va_type_t<Ts...>>
	inline Ret va_type_var(const Ts&... _args) { return Ret{ _args... }; }

#pragma endregion

#pragma region vec_type
	// create vector type from base type and dimension
	template <class T, size_t Dim>
	struct vec_type { typedef std::false_type type; }; // could also use glm::vec<Dim, T, highpr> but then dim == 1 is not a base type

	template<>
	struct vec_type<float, 1> { typedef float type; };

	template<>
	struct vec_type<float, 2> { typedef float2_t type; };

	template<>
	struct vec_type<float, 3> { typedef float3_t type; };

	template<>
	struct vec_type<float, 4> { typedef float4_t type; };

	template<>
	struct vec_type<int32_t, 1> { typedef int32_t type; };

	template<>
	struct vec_type<int32_t, 2> { typedef int2_t type; };

	template<>
	struct vec_type<int32_t, 3> { typedef int3_t type; };

	template<>
	struct vec_type<int32_t, 4> { typedef int4_t type; };

	template<>
	struct vec_type<uint32_t, 1> { typedef uint32_t type; };

	template<>
	struct vec_type<uint32_t, 2> { typedef uint2_t type; };

	template<>
	struct vec_type<uint32_t, 3> { typedef uint3_t type; };

	template<>
	struct vec_type<uint32_t, 4> { typedef uint4_t type; };

	template<>
	struct vec_type<bool, 1> { typedef bool type; };

	template<>
	struct vec_type<bool, 2> { typedef bool2_t type; };

	template<>
	struct vec_type<bool, 3> { typedef bool3_t type; };

	template<>
	struct vec_type<bool, 4> { typedef bool4_t type; };

	template <class T, size_t Dim>
	using vec_type_t = typename vec_type<T, Dim>::type;
#pragma endregion

	template <class T>
	using condition_t = vec_type_t<bool, Dimension<T>>; // result vector of conditional operation on T

	template <class T>
	constexpr bool is_scalar = std::is_same_v<T, base_type_t<T>>;

	template <class T>
	constexpr bool is_vector =
		hlx::is_of_type<T,
		bool2_t, bool3_t, bool4_t,
		int2_t, int3_t, int4_t,
		uint2_t, uint3_t, uint4_t,
		float2_t, float3_t, float4_t,
		quaternion_t>();

	template <class T>
	constexpr bool is_vector_float = hlx::is_of_type<T, float2_t, float3_t, float4_t, quaternion_t>();

	template <class T>
	constexpr bool is_vector_int = hlx::is_of_type<T, int2_t, int3_t, int4_t>();

	template <class T>
	constexpr bool is_vector_uint = hlx::is_of_type<T, uint2_t, uint3_t, uint4_t>();

	template <class T>
	constexpr bool is_vector_bool = hlx::is_of_type<T, bool2_t, bool3_t, bool4_t>();

	template <class T>
	constexpr bool is_vector_integer = hlx::is_of_type<T, int2_t, int3_t, int4_t, uint2_t, uint3_t, uint4_t>();

	template <class T>
	constexpr bool is_matrix = hlx::is_of_type<T, float2x2_t, float3x3_t, float3x4_t, float4x3_t, float4x4_t>();

	template <class T>
	constexpr bool is_square_matrix = hlx::is_of_type<T, float2x2_t, float3x3_t, float4x4_t>();

	// TODO: unorm etc
	template <class T>
	constexpr bool is_bool_type = std::is_same_v<T, bool>;

	template <class T>
	constexpr bool is_int_type = hlx::is_of_type<T, int8_t, int16_t, int32_t, int64_t>();

	template <class T>
	constexpr bool is_uint_type = hlx::is_of_type<T, uint8_t, uint16_t, uint32_t, uint64_t>();

	template <class T>
	constexpr bool is_integer_type = is_int_type<T> || is_uint_type<T>;

	template <class T>
	constexpr bool is_float_type = hlx::is_of_type<T, float, double>();

	template <class T>
	constexpr bool is_numeric_type = hlx::is_of_type<T, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, float, double>();

	template <class T>
	constexpr bool is_base_bool = std::is_same_v<bool, base_type_t<T>>;

	template <class T>
	constexpr bool is_base_float = is_float_type<base_type_t<T>>;

	template <class T>
	constexpr bool is_base_int = is_int_type<base_type_t<T>>;

	template <class T>
	constexpr bool is_base_uint = is_uint_type<base_type_t<T>>;

	template <class T>
	constexpr bool is_base_integer = is_base_int<T> || is_base_uint<T>;

	// not c++ convertible but OpConvertXtoY should exist for this type
	template <class U, class V> // rename to numeric convertible?
	constexpr bool is_convertible = /*Dimension<U> == Dimension<V> &&*/ is_numeric_type<base_type_t<U>> && is_numeric_type<base_type_t<V>>;

#pragma region texture_types

	enum ETexDepthType : uint32_t
	{
		kTexDepthType_NonDepth = 0,
		kTexDepthType_Depth,
		kTexDepthType_Unspecified
	};

	// Sampled	indicates whether or not this image will be accessed in combination with a sampler, and must be one of the following values :
	//	0 indicates this is only known at run time, not at compile time
	//	1 indicates will be used with sampler
	//	2 indicates will be used without a sampler (a storage image)
	enum ETexSamplerAccess : uint32_t
	{
		kTexSamplerAccess_Runtime = 0, 
		kTexSamplerAccess_Sampled = 1,
		kTexSamplerAccess_Storage = 2
	};

	constexpr uint32_t SPVDimToRealDim(const spv::Dim _Dim)
	{
		if (_Dim <= spv::Dim3D)
			return _Dim + 1u;

		if (_Dim == spv::DimSubpassData || _Dim == spv::DimCube)
			return 2u;

		return 0u;
	}

	// Image Format can be Unknown, depending on the client API
	// we omit the format, since it should be coming from the api anyway
	template <
		class T,
		spv::Dim _Dim,
		bool _Array = false,
		ETexDepthType _DType = kTexDepthType_NonDepth,
		bool _MultiSampled = false,
		ETexSamplerAccess _SAccess = kTexSamplerAccess_Sampled>
	struct tex_t
	{
		typedef T TexComponentType; // pixel storage type
		typedef vec_type_t<base_type_t<T>, 4> TexSampleType; // returned by a sample / fetch
		typedef vec_type_t<float, SPVDimToRealDim(_Dim) + _Array> TexCoordType; // UV coord vector type
		typedef vec_type_t<uint32_t, SPVDimToRealDim(_Dim) + _Array> TexGatherCoordType; // UV coord vector type
		static constexpr spv::Dim Dim = _Dim; // 1 2 3
		static constexpr bool Array = _Array; // is array
		static constexpr ETexDepthType DepthType = _DType;
		static constexpr bool MultiSampled = _MultiSampled;
		static constexpr ETexSamplerAccess SamplerAccess = _SAccess;
	};

	template<class, class = std::void_t<> >
	struct is_texture_impl : std::false_type { };

	template<class T>
	struct is_texture_impl<T, std::void_t<typename T::TexComponentType>> : std::true_type { };

	template <class T>
	constexpr bool is_texture = is_texture_impl<T>::value;

	template <class T = float4_t>
	using tex1d_t = tex_t<T, spv::Dim1D>;

	template <class T = float4_t>
	using tex2d_t = tex_t<T, spv::Dim2D>;

	template <class T = float4_t>
	using tex3d_t = tex_t<T, spv::Dim3D>;

	template <class T = float4_t>
	using tex_cube_t = tex_t<T, spv::DimCube>;

	template <class T = float4_t>
	using tex_color_subpass_t = tex_t<T, spv::DimSubpassData, false, kTexDepthType_NonDepth>;

	template <class T = float4_t>
	using tex_depth_subpass_t = tex_t<T, spv::DimSubpassData, false, kTexDepthType_Depth>;

	template <class T = float4_t>
	using tex_color_storage_t = tex_t<T, spv::Dim2D, false, kTexDepthType_NonDepth, false, kTexSamplerAccess_Storage>;

	template <class T = float>
	using tex_depth_storage_t = tex_t<T, spv::Dim2D, false, kTexDepthType_Depth, false, kTexSamplerAccess_Storage>;

	// TODO: array types

	template <class TexT> // TexT = tex_t variant
	using tex_component_t = typename TexT::TexComponentType;

	template <class TexT> // TexT = tex_t variant
	using tex_coord_t = typename TexT::TexCoordType;

	template <class TexT> // TexT = tex_t variant
	using tex_gather_coord_t = typename TexT::TexGatherCoordType;

	template <class TexT> // TexT = tex_t variant
	using tex_sample_t = typename TexT::TexSampleType;

	template <class TexT> // TexT = tex_t variant
	constexpr spv::Dim tex_dim_v = TexT::Dim;

	template <class TexT> // TexT = tex_t variant
	constexpr uint32_t tex_real_dim_v = SPVDimToRealDim(TexT::Dim);

#pragma endregion

	struct sampler_t {};

	template <class T>
	constexpr bool is_sampler = std::is_same_v<std::decay_t<T>, sampler_t>;

	template<class T, uint32_t Index>
	constexpr bool is_valid_index()
	{
		if constexpr(is_vector<T> || is_matrix<T>)
		{
			return Index < Dimension<T>;
		}
		else
		{
			return false;
		}
	}

	template <class T>
	constexpr bool is_valid_type = !std::is_same_v<std::false_type, T>;

	template <class U, class V>
	using longer_type_t = cond_t<Dimension<U> >= Dimension<V>, U, V>;

#pragma region mul result tpye
	// result type of a multiplication
	template <class M/*, class V*/> // M times V
	using matxvec_t = col_type_t<M>;

	template <class M/*, class V*/> // M times V
	using vecxmat_t = row_type_t<M>;

	template <class M, class N> // M times N
	using matxmat_t = mat_type_t<row_type_t<N>, col_type_t<M>>;

	template <class L, class R, class ElseT> // L * R
	using cond_mm_t = cond_t<is_matrix<L> && is_matrix<R>, matxmat_t<L, R>, ElseT>;

	template <class L, class R, class ElseT> // L * R
	using cond_mv_t = cond_t<is_matrix<L> && is_vector<R>, matxvec_t<L>, ElseT>;

	template <class L, class R, class ElseT> // L * R
	using conc_vm_t = cond_t<is_vector<L> && is_matrix<R>, vecxmat_t<R>, ElseT>;

	// TODO: exclude quaternion to disable standard Mul overload
	template <class L, class R> // L * R
	using mul_result_t = cond_mm_t<L, R, cond_mv_t<L, R, conc_vm_t<L, R, longer_type_t<L, R>>>>;
#pragma endregion

	// convert U to V
	template <class U, class V/*, typename = std::enable_if_t<Dimension<U> == Dimension<V>>*/>
	constexpr spv::Op GetConvertOp()
	{
		static_assert(Dimension<U> == Dimension<V>, "Type dimmensions mismatch");

		if constexpr(is_base_float<U> && is_base_int<V>)
			return spv::OpConvertFToS;
		else if constexpr(is_base_float<U> && is_base_uint<V>)
			return spv::OpConvertFToU;
		else if constexpr(is_base_int<U> && is_base_float<V>)
			return spv::OpConvertSToF;
		else if constexpr(is_base_uint<U> && is_base_float<V>)
			return spv::OpConvertUToF;
		else
			return spv::OpNop;
	}

#pragma region array traits
	struct TSPVArrayTag {};
	template <class T, uint32_t _Size>
	struct array_t : public std::array<T, _Size>
	{
		typedef TSPVArrayTag SPVArrayTag;
		typedef T ElementType;
		static constexpr uint32_t Size = _Size;
		static constexpr bool bDynamic = false;
	};

	//template <class T>
	//struct dyn_array_t : public std::vector<T>
	//{
	//	dyn_array_t(const uint32_t& _Size) : std::vector<T>(_Size), Size(_Size){}

	//	typedef TSPVArrayTag SPVArrayTag;
	//	typedef T ElementType;
	//	const uint32_t Size;
	//	static constexpr bool bDynamic = false;
	//};

	template<class, class = std::void_t<> >
	struct is_array_impl : std::false_type { };

	template<class T>
	struct is_array_impl<T, std::void_t<typename T::SPVArrayTag>> : std::true_type { };

	template<class T>
	constexpr bool is_array = is_array_impl<T>::value;

	template<class T>
	using array_element_t = typename T::ElementType;

#pragma endregion

#pragma region variable traits
	struct TSPVStructTag {};
	struct TSPVVarTag {};
	struct TSPVBuiltInTag {};

#ifndef SPVStruct
#define SPVStruct typedef Spear::TSPVStructTag SPVStructTag;
#endif

#ifndef SPVBuiltIn
#define SPVBuiltIn typedef Spear::TSPVBuiltInTag SPVBuiltInTag;
#endif

	template< class, class = std::void_t<> >
	struct has_struct_tag : std::false_type { };

	template< class T >
	struct has_struct_tag<T, std::void_t<typename T::SPVStructTag>> : std::true_type { };

	template<class T>
	constexpr bool is_struct = has_struct_tag<T>::value;
	//---------------------------------------------------------------------------------------------------

	template< class, class = std::void_t<> >
	struct has_var_tag : std::false_type { };

	template< class T >
	struct has_var_tag<T, std::void_t<typename T::SPVVarTag>> : std::true_type { };

	template<class T>
	constexpr bool is_var = has_var_tag<T>::value;
	//---------------------------------------------------------------------------------------------------

	template< class, class = std::void_t<> >
	struct has_builtin_tag : std::false_type { };

	template< class T >
	struct has_builtin_tag<T, std::void_t<typename T::SPVBuiltInTag>> : std::true_type { };

	template<class T>
	constexpr bool is_builtin = has_builtin_tag<T>::value;
	//---------------------------------------------------------------------------------------------------

	template<class T>
	using var_value_t = typename T::ValueType;

	// check if any parameter has the variable tag
	template <class ...Ts>
	constexpr bool has_var = std::disjunction_v<has_var_tag<Ts>...>;
#pragma endregion

}; // Spear

#endif // !SPEAR_SPIRVVARIABLETYPES_H
