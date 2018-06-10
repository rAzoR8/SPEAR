//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_MICROFACETREFLECTION_H
#define SPEAR_MICROFACETREFLECTION_H

#include "SPIRVProgram.h"

namespace Spear
{
	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3> // ri = refraction index
	inline var_t<float, Assemble, spv::StorageClassFunction> FresnelSchlick(const var_t<float3_t, Assemble, C1>& l, const var_t<float3_t, Assemble, C2>& h, var_t<float, Assemble, C3>& ri)
	{
		auto f0 = (1.f - ri) / (1.f + ri);
		f0 *= f0;
		return f0 + (1.f - f0) * Pow(1.f - Dot(l, h), 5.f);
	}

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3> // h = half, n = normal, a = exponent
	inline var_t<float, Assemble, spv::StorageClassFunction> BlinnPhongDistribution(const var_t<float3_t, Assemble, C1>& n, const var_t<float3_t, Assemble, C2>& h, var_t<float, Assemble, C3>& a)
	{
		return ((a + 2.f) / glm::two_pi<float>()) * Pow(Dot(n, h), a);
	}

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<float, Assemble, spv::StorageClassFunction> GeoImplicit(const var_t<float3_t, Assemble, C1>& n, const var_t<float3_t, Assemble, C2>& l, const var_t<float3_t, Assemble, C3>& v)
	{
		return Dot(n, l) * Dot(n, v);
	}

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, spv::StorageClass C4>
	inline var_t<float, Assemble, spv::StorageClassFunction> GeoCookTorrance(const var_t<float3_t, Assemble, C1>& n, const var_t<float3_t, Assemble, C2>& l, const var_t<float3_t, Assemble, C3>& v, const var_t<float3_t, Assemble, C4>& h)
	{
		auto nh2vh = (2.f * Dot(n, h)) / Dot(v, h);

		return Min(1.f, nh2vh * Dot(n, v), nh2vh * Dot(n, l));
	}

	template <class MRInstance>
	class MicrofacetReflection
	{
	public:
		MicrofacetReflection() {};
		virtual ~MicrofacetReflection() {};

		//https://simonstechblog.blogspot.de/2011/12/microfacet-brdf.html
		template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3> // n = normal, l = lightdir, v = viewdir
		inline var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& n, const var_t<float3_t, Assemble, C2>& l, const var_t<float3_t, Assemble, C3>& v) const
		{
			const MRInstance* pThis = static_cast<const MRInstance*>(this);

			auto h = Normalize(l + v);
			// we pass all vectors as some variants might use different inputs
			return (pThis->F(n, l, v, h) * pThis->G(n, l, v, h) * pThis->D(n, l, v, h)) / (4.f * Dot(n, l) * Dot(n, v));			 
		}
	private:

	};
} // Spear

#endif // !SPEAR_MICROFACETREFLECTION_H
