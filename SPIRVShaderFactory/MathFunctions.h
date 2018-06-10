//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_MATHFUNCTIONS_H
#define SPEAR_MATHFUNCTIONS_H

#include "SPIRVOperatorImpl.h"

namespace Spear
{
	template <bool Assemble, spv::StorageClass C1>
	inline var_t<float3x3_t, Assemble, spv::StorageClassFunction> RotateY3X3(const var_t<float, Assemble, C1>& _fAngleRad)
	{
		using vec3 = var_t<float3_t, Assemble, spv::StorageClassFunction>;
		using mat3 = var_t<float3x3_t, Assemble, spv::StorageClassFunction>;

		auto c = Cos(_fAngleRad);
		auto s = Sin(_fAngleRad);

		return mat3(
			vec3(c, 0.f, s),
			vec3(0.f, 1.f, 0.f), // float3_t make_const
			vec3(-s, 0.f, c));
	}

	template <bool Assemble, spv::StorageClass C1>
	inline var_t<float4x4_t, Assemble, spv::StorageClassFunction> RotateY4X4(const var_t<float, Assemble, C1>& _fAngleRad)
	{
		using vec4 = var_t<float4_t, Assemble, spv::StorageClassFunction>;
		using mat4 = var_t<float4x4_t, Assemble, spv::StorageClassFunction>;

		auto c = Cos(_fAngleRad);
		auto s = Sin(_fAngleRad);

		return mat4(
			vec4(c, 0.f, s, 0.f),
			vec4(0.f, 1.f, 0.f, 0.f),
			vec4(-s, 0.f, c, 0.f),
			vec4(0.f, 0.f, 0.f, 1.f));
	}
} // Spear

#endif // !SPEAR_MATHFUNCTIONS_H
