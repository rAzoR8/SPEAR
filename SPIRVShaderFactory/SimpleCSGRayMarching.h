//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SIMPLECSGRAYMARCHING_H
#define SPEAR_SIMPLECSGRAYMARCHING_H

#include "CSGObject.h"
#include "SPIRVBranchOperations.h"
#include "CameraFunctions.h"
#include "MaterialInterface.h"

namespace Spear
{
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class TEvalFunc>
	inline var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
		const TEvalFunc& _Eval,
		const var_t<float3_t, Assemble, C1>& _vEye, // view pos
		const var_t<float3_t, Assemble, C2>& _vMarchDir, // ray dir
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001f,
		const uint32_t _uStepCount = 100u)
	{
		auto depth = make_var<Assemble>(_fStartDepth);
		For(auto i = make_var<Assemble>(0u), i < _uStepCount && depth < _fEndDepth, ++i)
		{
			auto dist = _Eval(_vEye + depth * _vMarchDir);
			If(dist < _fEpsilon)
			{
				i = _uStepCount; // break from loop
			}
			Else
			{
				depth += dist;
			});
		});

		return depth;// Min(depth, _fEndDepth);
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
		const TCSGObj<Assemble>& _Object,
		const var_t<float3_t, Assemble, C1>& _vEye, // view pos
		const var_t<float3_t, Assemble, C2>& _vMarchDir, // ray dir
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001f,
		const uint32_t _uStepCount = 100u)
	{
		return ShortestDistToSurface([&](const var_t<float3_t, Assemble, C1>& e) {return _Object->Eval(e); }, _vEye, _vMarchDir, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> ShortestDistToSurface(
		const CSGScene<Assemble>& _Scene,
		const var_t<float3_t, Assemble, C1>& _vEye, // view pos
		const var_t<float3_t, Assemble, C2>& _vMarchDir, // ray dir
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001f,
		const uint32_t _uStepCount = 100u)
	{
		return ShortestDistToSurface([&](const var_t<float3_t, Assemble, C1>& e) {return _Scene.Eval(e); }, _vEye, _vMarchDir, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);
	}
	
	//---------------------------------------------------------------------------------------------------

	// single material
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class TEvalFunc>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> RayMarchDistanceFunction(
		const TEvalFunc& _DistFunc,
		const var_t<float3_t, Assemble, C1>& _vCameraPos,
		const var_t<float3_t, Assemble, C2>& _vRay,
		const IMaterialInterface<Assemble>* _pMaterial = nullptr,
		const std::vector<PointLight<Assemble>*> _PointLights = {}, // todo: use std::variant and std visit
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001f,
		const uint32_t _uStepCount = 100u)
	{
		auto fDist = ShortestDistToSurface(_DistFunc, _vCameraPos, _vRay, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);

		auto vPos = _vCameraPos + _vRay * fDist;
		auto vNormal = ForwardDiffNormal(vPos, mcvar(_fEpsilon), _DistFunc);
		//auto vNormal = DeriveFragmentNormal(vPos);

		auto vColor = make_const<Assemble>(float3_t(0.f, 0.f, 0.f));

		if (_pMaterial != nullptr)
		{
			for (const PointLight<Assemble>* pLight : _PointLights)
			{
				vColor += _pMaterial->Eval(vPos, vNormal, _vCameraPos, *pLight);
			}
		}
		else
		{
			//vColor.r = fDist / _fEndDepth; // for debugging
			vColor = vNormal; // print normal instead
		}

		// ray escaped
		auto bEscaped = fDist > _fEndDepth - _fEpsilon;
		return Select(bEscaped, mvar(float3_t(0.f, 0.f, 0.f)), vColor);

		return vColor;
	}

	//---------------------------------------------------------------------------------------------------

	// Material per CSG object
	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2/*, spv::StorageClass C3*/>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> RayMarchCSGSceneEx(
		const CSGScene<Assemble>& _Scene,
		const var_t<float3_t, Assemble, C1>& _vRay,
		const var_t<float3_t, Assemble, C2>& _vCameraPos,
		const std::vector<TLightVariant<Assemble>> _Lights,
		const float _fStartDepth = 0.f,
		const float _fEndDepth = 100.f,
		const float _fEpsilon = 0.0001f,
		const uint32_t _uStepCount = 100u)
	{
		var_t<float3_t, Assemble, spv::StorageClassFunction> vColor = { 0.f, 0.f, 0.f };

		//auto fDist = ShortestDistToSurface([&](const var_t<float3_t, Assemble, C1>& e) {return _Scene.Eval(e); }, _vCameraPos, _vRay, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);

		//auto vPos = _vCameraPos + _vRay * fDist;
		//auto vNormal = _Scene.Normal(vPos, mcvar(_fEpsilon));

		for (const auto& pObj : _Scene.GetObjects())
		{
			const auto& pMaterial = pObj->GetMaterial();

			if (pMaterial)
			{
				auto fDist = ShortestDistToSurface(pObj, _vCameraPos, _vRay, _fStartDepth, _fEndDepth, _fEpsilon, _uStepCount);

				auto vPos = _vCameraPos + _vRay * fDist;
				auto vNormal = pObj->Normal(vPos, mcvar(_fEpsilon));

				for (const auto Light : _Lights)
				{
					vColor += std::visit([&](auto&& arg) {return pMaterial->Eval(vPos, vNormal, _vCameraPos, arg); }, Light);
					//vColor += Select(fDist < _fEndDepth, vObjColor, mcvar(float3_t(0.f, 0.f, 0.f)));
				}
			}
		}

		return vColor;
	}
	//---------------------------------------------------------------------------------------------------

	// simple pointlight monomaterial marching
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, spv::StorageClass C4>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> RayMarchCSGScene(
		const CSGScene<Assemble>& _Scene,
		const var_t<float3_t, Assemble, C1>& _vCameraPos,
		const var_t<float, Assemble, C2>& _fFoVDeg, // camera field of view Y in degrees
		const var_t<float2_t, Assemble, C3>& _vFragCoords, // fragment coordinates relative to viewport
		const var_t<float2_t, Assemble, C4>& _vViewportSize,// resolution of the viewport
		const IMaterialInterface<Assemble>* _pMaterial = nullptr,
		const std::vector<PointLight<Assemble>*> _PointLights = {})
	{
		return RayMarchDistanceFunction(
			[&](const var_t<float3_t, Assemble, C1>& e) {return _Scene.Eval(e); }, // depth function
			_vCameraPos, // origin
			RayDirection(_fFoVDeg, _vViewportSize, _vFragCoords), // view
			_pMaterial, // shading
			_PointLights);
	}
} // Spear

#endif // !SPEAR_SIMPLECSGRAYMARCHING_H
