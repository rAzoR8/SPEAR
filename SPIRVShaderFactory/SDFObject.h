//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SDFOBJECT_H
#define SPEAR_SDFOBJECT_H

#include "SPIRVOperatorImpl.h"
#include <memory>

namespace Spear
{
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class EvalFunc>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> ForwardDiffNormal(const var_t<float3_t, Assemble, C1>& p, const var_t<float, Assemble, C2>& e, const EvalFunc& _Eval)
	{
		using vec3 = var_t<float3_t, Assemble, spv::StorageClassFunction>;

		return Normalize(
			vec3(
				_Eval(vec3(p.x + e, p.y, p.z)) - _Eval(vec3(p.x - e, p.y, p.z)),
				_Eval(vec3(p.x, p.y + e, p.z)) - _Eval(vec3(p.x, p.y - e, p.z)),
				_Eval(vec3(p.x, p.y, p.z + e)) - _Eval(vec3(p.x, p.y, p.z - e))
			)
		);
	}

	template<bool Assemble, spv::StorageClass C1>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> DeriveFragmentNormal(const var_t<float3_t, Assemble, C1>& _PixelViewPos)
	{
		return Cross(Normalize(Ddx(_PixelViewPos)), Normalize(Ddy(_PixelViewPos)));
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> SphereDist(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Radius)
	{
		return Length(_Point) - _Radius;
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> CubeDist(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float3_t, Assemble, C2>& _vExtents)
	{
		auto d = Abs(_Point) - _vExtents;
		return Min(0.f, Max(d.x, d.y, d.z)) + Length(Max(d, make_const<Assemble>(float3_t(0.f, 0.f, 0.f))));
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2> // plane at origin
	inline var_t<float, Assemble, spv::StorageClassFunction> PlaneDist(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float3_t, Assemble, C2>& _vNormal)
	{
		return Dot(_Point, _vNormal);
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2> // xyz = normal box extents, w = extent towards info
	inline var_t<float, Assemble, spv::StorageClassFunction> CrossDist(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _fExtent)
	{
		return Min(Max(Abs(_Point.x), Abs(_Point.y)), Max(Abs(_Point.y), Abs(_Point.z)), Max(Abs(_Point.z), Abs(_Point.x))) - _fExtent;
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	struct SDFObject
	{
		static constexpr bool AssembleParam = Assemble;

		using vec3 = var_t<float3_t, Assemble, spv::StorageClassFunction>;

		SDFObject() {};
		virtual ~SDFObject() {};

		// user has to override this function:
		virtual var_t<float, Assemble, spv::StorageClassFunction> Distance(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const = 0;

		template <spv::StorageClass C1>
		inline var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& _Point) const { return Distance(make_intermediate(_Point)); };

		template <spv::StorageClass C1, spv::StorageClass C2>
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Normal(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Epsilon) const
		{
			return ForwardDiffNormal(_Point, _Epsilon, [&](const auto& v) {return this->Eval(v); });
		};	
	};

	template <bool Assemble>
	using TSDFObj = std::shared_ptr<SDFObject<Assemble>>;

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	struct SphereSDF : public SDFObject<Assemble>
	{
		var_t<float, Assemble, Class> fRadius;
		SphereSDF(const float& _fRadius = 1.f) : fRadius(_fRadius) {}

		template <spv::StorageClass C1>
		SphereSDF(const var_t<float, Assemble, C1>& _fRadius) : fRadius(_fRadius) {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Distance(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final
		{
			return SphereDist(_Point, fRadius); 
		}

		template <class ...Ts>
		static inline std::shared_ptr<SphereSDF> Make(const Ts& ... args) {return std::make_shared<SphereSDF>(args...); }
	};

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	struct CubeSDF : public SDFObject<Assemble>
	{
		var_t<float3_t, Assemble, Class> vExtent;
		CubeSDF(const float3_t _vExtents = {1.f, 1.f, 1.f}) : vExtent(_vExtents) {}

		template <spv::StorageClass C1>
		CubeSDF(const var_t<float3_t, Assemble, C1>& _vExtents) : vExtent(_vExtents) {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Distance(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final
		{
			return CubeDist(_Point, vExtent);
		}

		template <class ...Ts>
		static inline std::shared_ptr<CubeSDF> Make(const Ts& ... args) { return std::make_shared<CubeSDF>(args...); }
	};

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	struct PlaneSDF : public SDFObject<Assemble>
	{
		var_t<float3_t, Assemble, Class> vNormal;
		PlaneSDF(const float3_t _vNormal = { 0.f, 1.f, 0.f }) : vNormal(_vNormal) {}

		template <spv::StorageClass C1>
		PlaneSDF(const var_t<float3_t, Assemble, C1>& _vNormal) : vNormal(_vNormal) {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Distance(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final
		{
			return PlaneDist(_Point, vNormal);
		}

		template <class ...Ts>
		static inline std::shared_ptr<PlaneSDF> Make(const Ts& ... args) { return std::make_shared<PlaneSDF>(args...); }
	};

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	struct CrossSDF : public SDFObject<Assemble>
	{
		var_t<float, Assemble, Class> fExtent;
		CrossSDF(const float& _fExtent = 1.f) : fExtent(_fExtent) {}

		template <spv::StorageClass C1>
		CrossSDF(const var_t<float, Assemble, C1>& _fExtent) : fExtent(_fExtent) {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Distance(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final
		{
			return CrossDist(_Point, fExtent);
		}

		template <class ...Ts>
		static inline std::shared_ptr<CrossSDF> Make(const Ts& ... args) { return std::make_shared<CrossSDF>(args...); }
	};

	//---------------------------------------------------------------------------------------------------

} // Spear

#endif // !SPEAR_SDFOBJECT_H
