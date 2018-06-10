//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_MATERIALINTERFACE_H
#define SPEAR_MATERIALINTERFACE_H

#include "SPIRVVariable.h"
#include <variant>

namespace Spear
{
	template<bool Assemble>
	struct DirectionalLight
	{
		SPVStruct;

		DirectionalLight(
			const float3_t _vDirection = { 0.5f, -1.f, 0.f }, 
			const float3_t _vColor = { 1.f, 1.f, 1.f }) :
			vDirection(glm::normalize(_vDirection)),
			vColorIntensity(_vColor)
		{}

		var_t<float3_t, Assemble, spv::StorageClassFunction> vDirection;
		var_t<float, Assemble, spv::StorageClassFunction> DLPAD1;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vColorIntensity;
		var_t<float, Assemble, spv::StorageClassFunction> DLPAD2;
	};

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble>
	struct PointLight
	{
		SPVStruct;

		PointLight(
			const float3_t _vPosition = { 0.f, 0.f, 0.f },
			const float _fRange = 10.f,
			const float3_t _vColor = { 1.f, 1.f, 1.f },
			const float _fDecayStart = 2.f) :
			vPosition(_vPosition),
			fRange(_fRange),
			vColorIntensity(_vColor),
			fDecayStart(_fDecayStart)
		{}

		var_t<float3_t, Assemble, spv::StorageClassFunction> vPosition;
		var_t<float, Assemble, spv::StorageClassFunction> fRange;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vColorIntensity;
		var_t<float, Assemble, spv::StorageClassFunction> fDecayStart;
	};
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	struct SpotLight
	{
		SPVStruct;

		SpotLight(
			const float3_t _vPosition = { 0.f, 0.f, 0.f },
			const float _fRange = 10.f,
			const float3_t _vColor = { 1.f, 1.f, 1.f },
			const float _fDecayStart = 2.f,
			const float3_t _vDirection = { 0.5f, -1.f, 0.f },
			const float _fSpotAngleDeg = 30.f) :
			vPosition(_vPosition),
			fRange(_fRange),
			vColorIntensity(_vColor),
			fDecayStart(_fDecayStart),
			vDirection(glm::normalize(_vDirection)),
			fSpotAngle(glm::radians(_fSpotAngleDeg))
		{}

		var_t<float3_t, Assemble, spv::StorageClassFunction> vPosition;
		var_t<float, Assemble, spv::StorageClassFunction> fRange;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vColorIntensity;
		var_t<float, Assemble, spv::StorageClassFunction> fDecayStart;

		var_t<float3_t, Assemble, spv::StorageClassFunction> vDirection;
		var_t<float, Assemble, spv::StorageClassFunction> fSpotAngle; // could be encoded as magnitude of vDirection
	};
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	using TLightVariant = std::variant<DirectionalLight<Assemble>, PointLight<Assemble>, SpotLight<Assemble>>;

	// a material is just some entity that evaluates to some spectrum
	template <bool Assemble>
	struct IMaterialInterface
	{
		// TODO: function: GetDiffuse Reflection Vec & GetSpecularReflection Vec (random under ndf)

		// light default empty implementation
		virtual var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos, const DirectionalLight<Assemble>& _DirLight) const { return _DirLight.vColorIntensity; };
		virtual var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos, const PointLight<Assemble>& _PointLight) const { return _PointLight.vColorIntensity; };
		virtual var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos, const SpotLight<Assemble>& _SpotLight) const { return _SpotLight.vColorIntensity; };

		// std visit matcher
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> operator()(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos, const DirectionalLight<Assemble>& _DirLight) const { return Eval(_vPos, _vNormal, _vCameraPos, _DirLight); };
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> operator()(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos, const PointLight<Assemble>& _PointLight) const { return Eval(_vPos, _vNormal, _vCameraPos, _PointLight); };
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> operator()(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal, const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos, const SpotLight<Assemble>& _SpotLight) const { return Eval(_vPos, _vNormal, _vCameraPos, _SpotLight); };
	};
} // Spear

#endif // !SPEAR_MATERIALINTERFACE_H
