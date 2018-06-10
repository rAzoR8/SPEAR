//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_PHONGMATERIAL_H
#define SPEAR_PHONGMATERIAL_H

#include "SPIRVOperatorImpl.h"
#include "MaterialInterface.h"
#include "LightingFunctions.h"

namespace Spear
{
	//---------------------------------------------------------------------------------------------------

	// standard branchless phong illumination for point light source
	template <
		bool Assemble,
		spv::StorageClass C1,
		spv::StorageClass C2,
		spv::StorageClass C3,
		spv::StorageClass C4,
		spv::StorageClass C5,
		spv::StorageClass C6,
		spv::StorageClass C7,
		spv::StorageClass C8>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> PhongIlluminationPoint(
			const var_t<float3_t, Assemble, C1>& _vPos, // Surface point being lit
			const var_t<float3_t, Assemble, C2>& _vNormal, // Surface normal
			const var_t<float3_t, Assemble, C3>& _vCameraPos,
			const var_t<float3_t, Assemble, C4>& _vDiffuseColor,
			const var_t<float3_t, Assemble, C5>& _vSpecularColor,
			const var_t<float, Assemble, C6>& _Alpha, // Shininess factor
			const var_t<float3_t, Assemble, C7>& _vLightPos,
			const var_t<float3_t, Assemble, C8>& _vLightColor)// intensity	 
	{
		auto L = Normalize(_vLightPos - _vPos);
		auto V = Normalize(_vCameraPos - _vPos);
		auto R = Normalize(Reflect(-L, _vNormal));

		return _vLightColor * 
			(_vDiffuseColor * Saturate(Dot(_vNormal, L))
			+ _vSpecularColor * Pow(Saturate(Dot(R, V)), _Alpha));
	}

	//---------------------------------------------------------------------------------------------------

	// standard branchless phong illumination for directional light source
	template <
		bool Assemble,
		spv::StorageClass C1,
		spv::StorageClass C2,
		spv::StorageClass C3,
		spv::StorageClass C4,
		spv::StorageClass C5,
		spv::StorageClass C6,
		spv::StorageClass C7,
		spv::StorageClass C8>
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PhongIlluminationDir(
			const var_t<float3_t, Assemble, C1>& _vPos, // Surface point being lit
			const var_t<float3_t, Assemble, C2>& _vNormal, // Surface normal
			const var_t<float3_t, Assemble, C3>& _vCameraPos,
			const var_t<float3_t, Assemble, C4>& _vDiffuseColor,
			const var_t<float3_t, Assemble, C5>& _vSpecularColor,
			const var_t<float, Assemble, C6>& _Alpha, // Shininess factor
			const var_t<float3_t, Assemble, C7>& _vLightDir, // source to surface
			const var_t<float3_t, Assemble, C8>& _vLightColor)// intensity	 
	{
		auto V = Normalize(_vCameraPos - _vPos);
		auto R = Normalize(Reflect(_vLightDir, _vNormal));

		return _vLightColor *
			(_vDiffuseColor * Saturate(Dot(_vNormal, -_vLightDir))
				+ _vSpecularColor * Pow(Saturate(Dot(R, V)), _Alpha));
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	struct PhongMaterial : public IMaterialInterface<Assemble>
	{
		SPVStruct;
		
		// directional light
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, // surface point lit
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal,
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos,
			const DirectionalLight<Assemble>& _Light) const final
		{
			return vAmbientColor +
				PhongIlluminationDir(_vPos, _vNormal, _vCameraPos, vDiffuseColor, vSpecularColor, fShininess, _Light.vDirection, _Light.vColorIntensity);
		}

		// point light
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, // surface point lit
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal,
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos,
			const PointLight<Assemble>& _Light) const final
		{
			return vAmbientColor +
				PhongIlluminationPoint(_vPos, _vNormal, _vCameraPos, vDiffuseColor, vSpecularColor, fShininess, _Light.vPosition, _Light.vColorIntensity) *
				CalculateAttenuation(Length(_Light.vPosition - _vPos), _Light.fRange, _Light.fDecayStart);
		}

		// spot light
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Eval(
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vPos, // surface point lit
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vNormal,
			const var_t<float3_t, Assemble, spv::StorageClassFunction>& _vCameraPos,
			const SpotLight<Assemble>& _Light) const final
		{
			return vAmbientColor +
				PhongIlluminationPoint(_vPos, _vNormal, _vCameraPos, vDiffuseColor, vSpecularColor, fShininess, _Light.vPosition, _Light.vColorIntensity)
				* CalculateAttenuation(Length(_Light.vPosition - _vPos), _Light.fRange, _Light.fDecayStart)
				* CalculateSpotCone(_Light.fSpotAngle, _Light.vDirection, Normalize(_vPos - _Light.vPosition));
		}

		PhongMaterial(
			const float3_t _vAmbient = {0.25f, 0.25f, 0.25f},
			const float3_t _vDiffuse = { 0.75f, 0.25f, 0.25f },
			const float3_t _vSpecular = { 1.f, 1.f, 1.f },
			const float _fShininess = 10.f) :
			vAmbientColor(_vAmbient),
			vDiffuseColor(_vDiffuse),
			vSpecularColor(_vSpecular),
			fShininess(_fShininess)	{}

		var_t<float3_t, Assemble, spv::StorageClassFunction> vAmbientColor;
		var_t<float, Assemble, spv::StorageClassFunction> PSPAD1;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vDiffuseColor;
		var_t<float, Assemble, spv::StorageClassFunction> PSPAD2;
		var_t<float3_t, Assemble, spv::StorageClassFunction> vSpecularColor;
		var_t<float, Assemble, spv::StorageClassFunction> fShininess;

		template <class ...Ts>
		static inline std::shared_ptr<PhongMaterial> Make(const Ts& ... args) { return std::make_shared<PhongMaterial>(args...); }
	};

	//---------------------------------------------------------------------------------------------------


} // Spear

#endif // !SPEAR_PHONGMATERIAL_H
