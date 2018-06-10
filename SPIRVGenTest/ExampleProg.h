//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_EXAMPLEPROG_H
#define SPEAR_EXAMPLEPROG_H

#include "SPIRVProgram.h"
#include "SPIRVAssembler.h"
#include "SPIRVExtensionAMD.h"

#include "..\SPIRVShaderFactory\MicrofacetReflection.h"

namespace Spear
{
	template <bool Assemble>
	class ExampleProg : public SPIRVProgram<Assemble>
	{
	public:
		ExampleProg() : SPIRVProgram<Assemble>()
		{ 
			AddExtension(ExtAMD::ExtGCNShader);
			AddCapability(spv::CapabilityInt64);
			AddCapability(spv::CapabilityImageQuery);
			GlobalAssembler.RemoveUnusedOperations(false); // for debugging
		};

		~ExampleProg() {};

		struct B
		{
			SPVStruct
			float2 UVCoord = "UVCoords";
			float2 Offset;

			u32 SampleCount;
		};

		struct PushBlock
		{
			SPVStruct
			float4 stuff;
		};

		CBuffer<B> BufferBlock;
		RenderTarget OutputColor;
		SamplerState Sampler;
		Texture2DEx<float3_t> InputImg;
		//SubPassColor SubPass;
		PushConstant<PushBlock> Push;
		Array<float3_t, 4> TestArray;

		inline void operator()()
		{
			f32 sum = 0.f;
			f32 sum2 = 1.f;

			float3 l, v, h, n;

			auto ddd = Saturate(l);

			l += ddd;

			auto bl = l != v && l == n;
			auto an = Any(bl);

			uint3 u1, u2;

			auto rep = replicate<3>(sum);

			l += rep;

			l = Saturate(l);

			auto u = Select(an, u1, u2);

			auto bit = u1 >= u2;
			auto bit2 = sum >= 1.f;

			auto k = Select(an, sum, sum2);

			auto f = FresnelSchlick(l, h, sum);
			auto d = BlinnPhongDistribution(n, h, sum);
			auto geoi = GeoImplicit(n, l, v);
			auto geotc = GeoCookTorrance(n, l, v, h);
			u32 size = TestArray.Length();
			//size = SizeOf(TestArray);

			auto dif = Ddx(l);
			dif = dif + Ddy(v);

			auto dims = InputImg.Dimensions(size);
			//v3.xy = dims;

			auto sampldrf = InputImg.SampleDref(Sampler, float2(0.5f, 0.5f), sum);
			auto fetch = InputImg.Fetch(int2(1, 1));
			auto gather = InputImg.Gather(Sampler, float2(0.5f, 0.5f), u32(0u));

			auto time = ExtAMD::GCNShader::Time<Assemble>();

			complex z1(3.0f, 4.0f);
			complex z2(3.0f, -2.0f);

			z1 *= z2;
			
			If(sum < 2.f)
			{
				sum += 2.f;
			}
			Else
			{
				sum -= 1.f;
			});

			//u32 uVertexID(1);
			auto id1 = (kVertexIndex & 1) << 2;
			auto id2 = (kInstanceIndex & 2) << 1;

			For(u32 e = 0u, e < size, ++e)
			{
				auto elem = TestArray[e];
				sum += Length(elem);
			});

			float3x4 m34;

			float3 v3 = { 1.f, 2.f, 3.f };
			float3 a, b, c;

			matrix m;

			m = Inverse(m);
			float4x3 m43 = Transpose(m34);
			auto det = Determinant(m);

			c = Atan2(a, b);
			b = Pow(c, a);
			a = Exp2(c);
			c = Log(a);
			b = InvSqrt(a + b);
			a = Reflect(b, Normalize(c));
			b = Refract(a, c, 0.5f);

			v3 = Fma(a, float3{ 1.f, 2.f, 3.f }, c);
			//v3 = Cross(a, b) * Dot(a, c);
			quaternion q1 = quaternion(v3, sum);
			quaternion q2;

			auto q = q1 * q2;
			q *= q2;
			q = q + q2;

			v3 = q.Rotate(v3);
			v3 = q.RotateUnit(v3);

			auto sp = SpecConst<float>(2.f);

			auto res = m34 * v3 * sp; // instead of using mul
			auto baj = Length(res.xyz);

			float2 offset = BufferBlock->Offset;
			For(u32 i = 0u, i < BufferBlock->SampleCount, ++i)
			{
				OutputColor.rgb = InputImg.Sample(Sampler, BufferBlock->UVCoord + offset);
				OutputColor.a = Length(OutputColor.rgb);
			});
		};
	private:
	};

}; // !Spear

#endif // !SPEAR_EXAMPLEPROG_H
