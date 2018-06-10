//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_LIGHTINGFUNCTIONS_H
#define SPEAR_LIGHTINGFUNCTIONS_H

#include "SPIRVOperatorImpl.h"

namespace Spear
{
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<float, Assemble, spv::StorageClassFunction> CalculateAttenuation(
		const var_t<float, Assemble, C1>& _fSurfacePointToLightDist,
		const var_t<float, Assemble, C2>& _fRange,
		const var_t<float, Assemble, C3>& _fDecayStart)
	{
		auto fDecayStart = Max(_fDecayStart, 0.0000001f); // ensure light sphere has valid radius

		auto fDmax = Max(_fRange - fDecayStart, 0.f);
		auto fD = Max(_fSurfacePointToLightDist - fDecayStart, 0.f);

		auto fDFactor = Square(((fD / (1.f - Square(fD / fDmax))) / fDecayStart) + 1.f);

		return Select(fDFactor == 0.0f, make_const<Assemble>(0.0f), (1.0f / fDFactor) * Step(_fSurfacePointToLightDist, fDmax));
	}
	//---------------------------------------------------------------------------------------------------

	// vL = Light vector from vertex pos to light
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<float, Assemble, spv::StorageClassFunction> CalculateSpotCone(
		const var_t<float, Assemble, C1>& _fSpotAngleRad,
		const var_t<float3_t, Assemble, C2> _vSpotDirection,
		const var_t<float3_t, Assemble, C3> _vLightToSurfaceDir)
	{
		auto fMinCos = Cos(_fSpotAngleRad);
		auto fMaxCos = (fMinCos + 1.0f) / 2.0f;
		return SmoothStep(fMinCos, fMaxCos, Dot(_vSpotDirection, _vLightToSurfaceDir));
	}
	//---------------------------------------------------------------------------------------------------
} // Spear

#endif // !SPEAR_LIGHTINGFUNCTIONS_H
