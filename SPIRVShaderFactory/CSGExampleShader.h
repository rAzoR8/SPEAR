//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_CSGEXAMPLESHADER_H
#define SPEAR_CSGEXAMPLESHADER_H

#include "SimpleCSGRayMarching.h"
#include "SPIRVProgram.h"
#include "PhongMaterial.h"

namespace Spear
{
	template <bool Assemble = true>
	class CSGExampleShader : public FragmentProgram<Assemble>
	{
	public:
		CSGExampleShader() : FragmentProgram<Assemble>("CSGExampleShader")
		{
			OptimizationSettings Settings;
			Settings.kPasses = kOptimizationPassFlag_AllPerformance;
			GlobalAssembler.ConfigureOptimization(Settings);
		}
		~CSGExampleShader() {};

		RenderTarget OutputColor;
		inline void operator()()
		{
			float3 vCamPos = { 0.f, 0.f, 5.f };
			float2 vViewport = { 1600.f, 900.f };
			f32 fFoV = 45.f;

			auto Red = PhongMaterial<Assemble>::Make(float3_t{ 0.f, 0.0f, 0.f });
			auto Blue = PhongMaterial<Assemble>::Make(float3_t{ 0.f, 0.0f, 0.f }, float3_t{ 0.0f, 0.15f, 0.85f });
			auto White = PhongMaterial<Assemble>::Make(float3_t{ 0.f, 0.0f, 0.f }, float3_t{ 1.0f, 1.0f, 1.f });

			std::vector<TLightVariant<Assemble>> Lights = { PointLight<Assemble>({ 2.f, 0.5f, 2.f })/* PointLight<Assemble>({ -2.f, -2.5f, 10.f })*//*, DirectionalLight<Assemble>({ 0.25f, 0.8f, 0.f })*/ };

			quaternion vRot({ 1.f, 0.5f, 0.f }, 0.3f);

			auto sphere = SphereSDF<Assemble>::Make(0.2f);
			auto cube = CubeSDF<Assemble>::Make();
			auto plane = PlaneSDF<Assemble>::Make(glm::normalize(float3_t(1.f, 0.25f, 0.25f)));
			//auto cross = csg(CrossSDF<Assemble>::Make() * 0.1f) /** vRot*/;

			// translation
			auto csgobj1 = sphere + float3_t(1.f, 0.f, 0.f);
			// scale & rotation
			auto csgobj2 = (0.25f * cube) /** vRot*/;

			// linear blending
			//auto blend = Blend(csgobj1, csgobj2, 0.5f);

			////auto menger1 = cube / (cross % float3_t(0.5f, 0.5f, 0.5f));
			////auto menger2 = menger1 / (cross % float3_t(1.f, 1.f, 1.f));
			////auto menger3 = menger2 / (cross % float3_t(2.f, 2.f, 2.f));
			////auto menger = menger3;

			//auto rep = sphere % float3_t(0.5f, 0.5f, 0.5f);
			//csgobj1->SetMaterial(Red);
			//csgobj2->SetMaterial(Blue);
			//blend->SetMaterial(Blue);
			//cross->SetMaterial(Blue);

			auto background = plane + float3_t(0.f, -1.f, 0.f);
			background->SetMaterial(Red);

			CSGScene<Assemble> scene({csgobj1, csgobj2, background });

			if (false)
			{
				auto vRay = RayDirection(fFoV, vViewport, kFragCoord.xy);
				OutputColor.rgb = RayMarchCSGSceneEx(scene, vRay, vCamPos, Lights);
			}
			else
			{
				PointLight<Assemble> PointLight1({ 2.f, 0.5f, 2.f });
				OutputColor.rgb = RayMarchCSGScene(scene, vCamPos, fFoV, kFragCoord.xy, vViewport, Red.get(), {&PointLight1 });
			}

			OutputColor.a = 0.f;
		};
	};

} // Spear

#endif // !SPEAR_CSGEXAMPLESHADER_H
