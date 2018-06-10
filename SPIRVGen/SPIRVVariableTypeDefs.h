//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVVARIABLETYPEDEFS_H
#define SPEAR_SPIRVVARIABLETYPEDEFS_H

#define S32 Spear::var_t<int32_t, Assemble, spv::StorageClassFunction>
#define S64 Spear::var_t<int64_t, Assemble, spv::StorageClassFunction>
#define Int2 Spear::var_t<int2_t, Assemble, spv::StorageClassFunction>
#define Int3 Spear::var_t<int3_t, Assemble, spv::StorageClassFunction>
#define Int4 Spear::var_t<int4_t, Assemble, spv::StorageClassFunction>

#define U32 Spear::var_t<uint32_t, Assemble, spv::StorageClassFunction>
#define U64 Spear::var_t<uint64_t, Assemble, spv::StorageClassFunction>
#define UInt2 Spear::var_t<uint2_t, Assemble, spv::StorageClassFunction>
#define UInt3 Spear::var_t<uint3_t, Assemble, spv::StorageClassFunction>
#define UInt4 Spear::var_t<uint4_t, Assemble, spv::StorageClassFunction>

#define F32 Spear::var_t<float, Assemble, spv::StorageClassFunction>
#define F64 Spear::var_t<double, Assemble, spv::StorageClassFunction>
#define Float2 Spear::var_t<float2_t, Assemble, spv::StorageClassFunction>
#define Float3 Spear::var_t<float3_t, Assemble, spv::StorageClassFunction>
#define Float4 Spear::var_t<float4_t, Assemble, spv::StorageClassFunction>

#define Quaternion = SPIRVQuaternion<Assemble, spv::StorageClassFunction>;
#define Complex = SPIRVComplex<Assemble, spv::StorageClassFunction>;
#define Boolean Spear::var_t<bool, Assemble, spv::StorageClassFunction>

#define Float2x2 Spear::var_t<float2x2_t, Assemble, spv::StorageClassFunction>
#define Float3x3 Spear::var_t<float3x3_t, Assemble, spv::StorageClassFunction>
#define Float3x4 Spear::var_t<float3x4_t, Assemble, spv::StorageClassFunction>
#define Float4x3 Spear::var_t<float4x3_t, Assemble, spv::StorageClassFunction>
#define Float4x4 Spear::var_t<float4x4_t, Assemble, spv::StorageClassFunction>
#define Matrix Spear::var_t<float4x4_t, Assemble, spv::StorageClassFunction>

//#define SamplerState Spear::var_t<sampler_t, Assemble, spv::StorageClassUniformConstant>
//
//#define Texture1D Spear::var_t<tex1d_t<float4_t>, spv::StorageClassUniformConstant>
//#define Texture2D Spear::var_t<tex2d_t<float4_t>, spv::StorageClassUniformConstant>
//#define Texture3D Spear::var_t<tex3d_t<float4_t>, spv::StorageClassUniformConstant>
//#define TextureCube Spear::var_t<tex_cube_t<float4_t>, spv::StorageClassUniformConstant>

#endif // !SPEAR_SPIRVVARIABLETYPEDEFS_H
