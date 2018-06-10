//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_DEFERREDLIGHTINGEXAMPLE_H
#define SPEAR_DEFERREDLIGHTINGEXAMPLE_H

#include "SPIRVProgram.h"

namespace Spear
{
	enum EDLPermutation : uint32_t
	{
		kDLPermutation_EnvMap = 1 << 0,
		kDLPermutation_Shadow = 1 << 1,
		kDLPermutation_NumOf = 2
	};

	using TDLPerm = hlx::Flag<EDLPermutation>;

	template <uint32_t DirLightRange = 10u, uint32_t PointLightRange = 10u, uint32_t SpotLightRange = 10u>
	class DeferredLighting : public FragmentProgram<true>
	{
	public:
		DeferredLighting(const TDLPerm& _Perm = {}) :
			m_kPerm(_Perm)
		{
			AddCapability(spv::CapabilityImageQuery);
		}

		~DeferredLighting() {};

		const TDLPerm m_kPerm;

		// Inputs
		var_in_t<float4_t> vPosition;
		var_in_t<float2_t> vTexCoord;
		var_in_t<float3_t> vViewRay;

		Texture2DEx<float> gDepthTex;
		Texture2DEx<float> gShadowMap;
		//Texture2DEx<float> gProjectedSpotShadowMap;

		Texture2DEx<float2_t> gNormalWSMap; // normal ws
		Texture2DEx<float2_t> gMetallicMap; // metallic material map / horizon normal light leakage value
		Texture2DEx<float> gRoughnessMap; // roughness material map
		Texture2DEx<float4_t> gAlbedoMap; // base color <-> specular material colors for metals
		TextureCubeEx<float4_t> gEnvMap; // prefiltered environment map, representing irradiance

		SamplerState SamplerPointClamp;
		SamplerState SamplerPointWrap;
		SamplerState SamplerLinearWrap;
		SamplerState SamplerShadowMap;
		SamplerState SamplerLinearClamp;

		// Outputs
		RenderTarget Diffuse;
		RenderTarget Specular;

		// CBuffer ----------------------------------------------
		struct ShadowData
		{
			SPVStruct

			float4x4 mShadowTransform;
			f32 fSpotShadowDepthOffset;
			f32 fPointShadowDepthOffset;
			float2 DeferredLightingPAD;
		};
		CBuffer<ShadowData> cbDeferredLighting;

		struct CameraData
		{
			SPVStruct

			float4x4 mView; //64
			float4x4 mViewInv; //64

			float4x4 mViewProj; //64
			float4x4 mViewProjInv; //64

			float4x4 mProj; //64
			float4x4 mProjInv; //64

			float4 vCameraPos;
			//float4 qCameraOrientation;

			f32 fNearDist;
			f32 fFarDist;
			f32 fFarNearDist;
			f32 fTHFOV; // tan(fov/2)

			f32 fAspectRatio;
			float3 vLookDir;
		};
		CBuffer<CameraData> cbPerCamera;

		struct DirectionalLight
		{
			SPVStruct

			float3 vDirection;
			f32 vPad0;
			float3 vColor;
			f32 vPad1;
		};
		Array<DirectionalLight, DirLightRange> cbDirectionalLight;

		struct PointLight
		{
			SPVStruct

			float3 vColor;
			f32	fRange; // dmax

			float3 vPosition;
			f32 fDecayStart;

			s32 iShadowIndex; // corresponding cbPointLightShadow entry
			float3 POINTLIGHTPAD;
		};
		Array<PointLight, PointLightRange> cbPointLight;

		struct SpotLight
		{
			SPVStruct

			float3 vDirection;
			f32 fSpotAngle;

			float3 vColor;
			f32	fRange; // dmax

			float3 vPosition;
			f32 fDecayStart;

			s32 iShadowIndex; /// corresponding cbSpotLightShadow entry
			float3 SPOTLIGHTPAD;
		};
		Array<SpotLight, SpotLightRange> cbSpotLight;

		// Structs ---------------------------------------------------
		struct LightingResult
		{
			float3 vDiffuse{TIntermediate()};
			float3 vSpecular{TIntermediate()};
		};

		// Functions ----------------------------------------------------------------------------------
		float2 NormalEncode(const float3& _vNormal)
		{
			return float2(Atan2(_vNormal.y, _vNormal.x) / glm::pi<float>(), _vNormal.z);
		}

		float3 NormalDecode(const float2& _vEncodedNormal)
		{
			const float2& vAngles = _vEncodedNormal;
			auto t = vAngles.x * glm::pi<float>();
			auto phi = Sqrt(1.0f - vAngles.y * vAngles.y);
			return float3(Cos(t) * phi, Sin(t) * phi, vAngles.y);
		}
		
		f32 CalculateShadowFactor(float4 _vShadowPosH)
		{
			_vShadowPosH.xyz /= _vShadowPosH.w;
			f32 fDepth = _vShadowPosH.z; // NDC-Space -> [0,1]

			f32 fDX = 1.0f / gShadowMap.Dimensions().x;
			f32 fDXNeg = -fDX;

			f32 fPercentLit = 0.0f;
			const float2 Offsets[9] =
			{
				float2(fDXNeg, fDXNeg), float2(0.0f, fDXNeg),	float2(fDX, fDXNeg),
				float2(fDXNeg, 0.0f),	float2(0.0f, 0.0f),		float2(fDX, 0.0f),
				float2(fDXNeg, fDX),	float2(0.0f, fDX),		float2(fDX, fDX)
			};

			for (int i = 0; i < 9; ++i) // this is equivalent to unrolling the loop
			{
				//SampleCmpLevelZero
				fPercentLit += gShadowMap.SampleDref(SamplerShadowMap, _vShadowPosH.xy + Offsets[i], fDepth);
			}

			return fPercentLit / 9.0f;
		}

		// Fresnel with additional 'fudge factor' taking care of gloss
		// Use only with filtered env maps!
		float3 FresnelSchlickWithRoughness(const float3& _vSpecularColor, const float3& _vToEye, const float3& _vNormal, const f32& _fGloss)
		{
			/// Lazarov
			return _vSpecularColor + (1.0f - _vSpecularColor) * ((Pow(1.0f - Saturate(Dot(_vToEye, _vNormal)), 5.f)) / (4.0f - 3.0f * _fGloss));
		}

		float2 DirectSpecularGGX_FV(const f32& _fDotLH, const f32& _fRoughness)
		{

			// F
			f32 fDotLH5 = Pow(1.0f - _fDotLH, 5.f);

			// V
			f32 fK = (_fRoughness * _fRoughness) / 2.0f;
			f32 fK2 = fK * fK;
			f32 fInvK2 = 1.0f - fK2;
			f32 fVis = 1.f / (_fDotLH * _fDotLH * fInvK2 + fK2);

			return float2(fVis, fDotLH5 * fVis);
		}

		f32 DirectSpecularGGX_D(const f32& _fDotNH, const f32& _fRoughness)
		{
			f32 fAlpha = _fRoughness * _fRoughness;
			f32 fAlphaSqr = fAlpha * fAlpha;

			/// if fDotNH == 1.0f && fAlphaSqr = 0.f ->  _fDotNH * _fDotNH *(fAlphaSqr - 1.0) = -1.0f -> -1 + 1 = 0
			f32 fDenom = _fDotNH * _fDotNH * (fAlphaSqr - 1.0) + 1.0f;

			/// -> NaN division
			f32 fD = Select(fDenom == 0.f, make_const<bAssembleProg>(0.f), fAlphaSqr / (glm::pi<float>() * fDenom * fDenom));
			return fD;
		}

		float3 DirectSpecularGGX(const float3& _vNormal, const float3& _vToEye, const float3& _vToLight, const f32& _fRoughness, const float3& _vF0)
		{
			float3 fH = Normalize(_vToEye + _vToLight);

			f32 fDotLH = Saturate(Dot(_vToLight, fH));
			f32 fDotNH = Saturate(Dot(_vNormal, fH));

			f32 fD = DirectSpecularGGX_D(fDotNH, _fRoughness);

			float2 vFVHelp = DirectSpecularGGX_FV(fDotLH, _fRoughness);

			// basically a lerp
			float3 vFV = _vF0 * vFVHelp.x + (1.0f - _vF0) * vFVHelp.y;

			float3 vSpecular = fD * vFV;
			return vSpecular;
		}

		float3 CalculateSpecularColor(const float3& _vLightColor, const f32& _fDotNL, const float3& _vToLight, const float3& _vToEye, const float3& _vNormal, const f32& _fRoughness, const float3& _vF0)
		{
			/// PBR approach
			float3 vBRDF = DirectSpecularGGX(_vNormal, _vToEye, _vToLight, _fRoughness, _vF0);
			return vBRDF * _vLightColor * _fDotNL;
		}

		float3 CalculateDiffuseColor(const float3& _vLightColor, const f32& _fDotNL)
		{
			return _vLightColor * _fDotNL;
		}

		// https://imdoingitwrong.wordpress.com/2011/02/10/improved-light-attenuation/
		f32 CalculateAttenuation(const f32& _fSurfacePointToLightDist, const f32& _fRange, const f32&_fDecayStart)
		{
			f32 fDecayStart = Max(_fDecayStart, 0.0000001f); // ensure light sphere has valid radius

			f32 fDmax = Max(_fRange - fDecayStart, 0.f);
			f32 fD = Max(_fSurfacePointToLightDist - fDecayStart, 0.f);

			f32 fD2 = fD / fDmax;
			fD2 *= fD2;

			f32 fDFactor = ((fD / (1.f - fD2)) / fDecayStart) + 1.f;
			fDFactor *= fDFactor;

			return Select(fDFactor == 0.0f, make_const<bAssembleProg>(0.0f), (1.0f / fDFactor) * Step(_fSurfacePointToLightDist, fDmax));
		}

		// vL = Light vector from vertex pos to light
		f32 CalculateSpotCone(const ArrayElement<SpotLight>& _Light, const float3& vL)
		{
			f32 fMinCos = Cos(_Light->fSpotAngle);
			f32 fMaxCos = (fMinCos + 1.0f) / 2.0f;
			f32 fCosAngle = Dot(_Light->vDirection.xyz, -vL);
			return SmoothStep(fMinCos, fMaxCos, fCosAngle);
		}

		// _vToEye points from vertex being shaded to camera -> CameraPos - VertexPos
		// _vPosWS is the world space position of the vertex 
		// _vNormal is the vertex normal
		template <class Light>
		LightingResult CalculateLightSource(const ArrayElement<Light>& _Light, const float3& _vToEye, const float3& _vPosWS, const float3& _vNormal, const f32& _fRoughness, const float3& _vF0)
		{
			// Light vector from vertex pos to light
			float3 vL{TIntermediate()};
			f32 fPointToLightDist{ TIntermediate() };
			f32 fAttenuation = 1.f;

			if constexpr(std::is_same_v<Light, DirectionalLight>)
			{
				vL = -_Light->vDirection;
			}
			else
			{
				vL = _Light->vPosition.xyz - _vPosWS;
				fPointToLightDist = Length(vL);
				vL = vL / fPointToLightDist;
				
				fAttenuation = CalculateAttenuation(fPointToLightDist, _Light->fRange, _Light->fDecayStart);
				if constexpr(std::is_same_v<Light, SpotLight>)
				{
					fAttenuation *= CalculateSpotCone(_Light, vL);
				}
			}

			f32 fDotNL = Saturate(Dot(_vNormal, vL));

			LightingResult Result;

			Result.vDiffuse = CalculateDiffuseColor(_Light->vColor, fDotNL) * fAttenuation;
			Result.vSpecular = CalculateSpecularColor(_Light->vColor, fDotNL, vL, _vToEye, _vNormal, _fRoughness, _vF0) * fAttenuation;

			return Result;
		}

		LightingResult ComputeLighting(const float3& _vViewDir, const float3& _vPosWS, const float3& _vNormal, const f32& _fMetallic, const f32& _fRoughness, const float3& _vF0)
		{
			LightingResult Result = CalculateLightSource(cbDirectionalLight[0u], _vViewDir, _vPosWS, _vNormal, _fRoughness, _vF0);

			if (m_kPerm.CheckFlag(kDLPermutation_Shadow))
			{
				float4 vShadowPosH = float4(_vPosWS, 1.0f) * cbDeferredLighting->mShadowTransform;
				f32 fShadowFactor = CalculateShadowFactor(vShadowPosH);

				// First light supports shadows
				Result.vDiffuse *= fShadowFactor;
				Result.vSpecular *= fShadowFactor;
			}

			for (int d = 1; d < DirLightRange; ++d) // unrolled
			{
				LightingResult CurResult = CalculateLightSource(cbDirectionalLight[d], _vViewDir, _vPosWS, _vNormal, _fRoughness, _vF0);

				Result.vDiffuse += CurResult.vDiffuse;
				Result.vSpecular += CurResult.vSpecular;
			}

			for (int p = 0; p < PointLightRange; ++p) // unrolled
			{
				//f32 fShadowFactorDP = 1.0f;

				//if(PointLight.iShadowIndex > -1)
				//{
				//	cbPointLightShadowTYPE ShadowProps = cbPointLightShadowArray[PointLight.iShadowIndex];

				//	float4 vPosDP = TransformToParaboloid(_vPosWS, ShadowProps);
				//	float fSceneDepthDP = vPosDP.w - fPointShadowDepthOffset;// 0.005f;
				//	float3 vTexCoordDP = ConvertParaboloidToTexCoord(vPosDP);

				//	fShadowFactorDP = CalculateParaboloidShadowFactor(gParaboloidPointShadowMap, vTexCoordDP, fSceneDepthDP, ShadowProps);
				//}

				LightingResult CurResult = CalculateLightSource(cbPointLight[p], _vViewDir, _vPosWS, _vNormal, _fRoughness, _vF0);
				Result.vDiffuse += /*fShadowFactorDP **/ CurResult.vDiffuse;
				Result.vSpecular += /*fShadowFactorDP **/ CurResult.vSpecular;
			}

			for (int s = 0; s < SpotLightRange; ++s)
			{
				//float fShadowFactorPS = 1.0f;

				//if (SpotLight.iShadowIndex > -1)
				//{
				//	cbSpotLightShadowTYPE ShadowProps = cbSpotLightShadowArray[SpotLight.iShadowIndex];

				//	float4 vPosPS = TransformToProjected(_vPosWS, ShadowProps);
				//	fShadowFactorPS = CalculateProjectedShadowFactor(gProjectedSpotShadowMap, vPosPS, ShadowProps, fSpotShadowDepthOffset);
				//}

				LightingResult CurResult = CalculateLightSource(cbSpotLight[s], _vViewDir, _vPosWS, _vNormal, _fRoughness, _vF0);
				Result.vDiffuse += /*fShadowFactorPS **/ CurResult.vDiffuse;
				Result.vSpecular += /*fShadowFactorPS **/ CurResult.vSpecular;
			}

			Result.vDiffuse = (1.0f - _fMetallic) * Result.vDiffuse;

			return Result;
		}
		
		inline void operator()()
		{
			f32 fLinDepth = gDepthTex.Sample(SamplerPointClamp, vTexCoord);
			float3 vNormal = Normalize(NormalDecode(gNormalWSMap.Sample(SamplerPointWrap, vTexCoord)));

			float3 vViewSpacePos = vViewRay * fLinDepth * cbPerCamera->fFarDist;
			float3 vPosWS = (cbPerCamera->mViewInv * float4(vViewSpacePos, 1.0f)).xyz;
			float3 vToEye = Normalize(cbPerCamera->vCameraPos.xyz - vPosWS);

			f32 fRoughness = Max(gRoughnessMap.Sample(SamplerLinearWrap, vTexCoord), 0.0001f);
			float2 vMetallicHorizon = gMetallicMap.Sample(SamplerLinearWrap, vTexCoord);

			// Lighting
			float3 vF0 = gAlbedoMap.Sample(SamplerLinearWrap, vTexCoord).rgb; // rgb->spec color map -> F0 values for metallic

			vF0 = Lerp(make_const<bAssembleProg>(0.04f, 0.04f, 0.04f), vF0, vMetallicHorizon.x); // dielectric have F0 reflectance of ~0.04

			// Calculate Direct Diffuse and Direct Specular Lighting by point light sources
			LightingResult LightResult = ComputeLighting(vToEye, vPosWS, vNormal, vMetallicHorizon.x, fRoughness, vF0);

			// Calculate Indirect Specular Light by "Texture" lights like the skybox
			float3 vIndirectSpecularLight = { 0.f, 0.f, 0.f };

			if (m_kPerm.CheckFlag(kDLPermutation_EnvMap))
			{
				float3 vReflection = Reflect(-vToEye, vNormal);
				f32 fMipmapIndex = fRoughness * (gEnvMap.Dimensions().z - 1.0f);
				float3 vEnvSpecular = gEnvMap.SampleLOD(SamplerLinearClamp, vReflection, fMipmapIndex).rgb;

				vIndirectSpecularLight = FresnelSchlickWithRoughness(vF0, vToEye, vNormal, 1.0f - fRoughness);
				vIndirectSpecularLight *= vEnvSpecular;
			}

			/// Subsurface normal light leak fix -> http://marmosetco.tumblr.com/post/81245981087
			vMetallicHorizon.y *= vMetallicHorizon.y;
			LightResult.vSpecular *= vMetallicHorizon.y;

			Diffuse = float4(LightResult.vDiffuse, 1.0f);
			Specular = float4(LightResult.vSpecular + vIndirectSpecularLight, 1.0f);
		}
	};
} // Spear

#endif // !SPEAR_DEFERREDLIGHTINGEXAMPLE_H
