//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_CSGOBJECT_H
#define SPEAR_CSGOBJECT_H

#include "SDFObject.h"
#include "MaterialInterface.h"
#include "SPIRVQuaternion.h"

namespace Spear
{
	// https://www.alanzucconi.com/2016/07/01/signed-distance-functions/#part6
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> IntersectSDF(const var_t<float, Assemble, C1>& _lDist, const var_t<float, Assemble, C2>& _rDist)
	{
		return Max(_lDist, _rDist);
	}

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> UnionSDF(const var_t<float, Assemble, C1>& _lDist, const var_t<float, Assemble, C2>& _rDist)
	{
		return Min(_lDist, _rDist);
	}

	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float, Assemble, spv::StorageClassFunction> DifferenceSDF(const var_t<float, Assemble, C1>& _lDist, const var_t<float, Assemble, C2>& _rDist)
	{
		return Max(_lDist, -_rDist);
	}

	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	class CSGObject
	{
	public:
		static constexpr bool AssembleParam = Assemble;

		CSGObject(const std::shared_ptr<SDFObject<Assemble>>& _pLeft, const std::shared_ptr<SDFObject<Assemble>>& _pRight = nullptr);
		CSGObject(const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr);
		CSGObject(const std::shared_ptr<SDFObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight);
		CSGObject(const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<SDFObject<Assemble>>& _pRight);

		virtual ~CSGObject() {};

		// override to implement offset, rotation, scale
		virtual var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const { return _Point; };
		virtual var_t<float, Assemble, spv::StorageClassFunction> PostEval(const var_t<float, Assemble, spv::StorageClassFunction>& _Dist) const { return _Dist; };
		virtual var_t<float, Assemble, spv::StorageClassFunction> Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const;

		template <spv::StorageClass C1>
		var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& _Point) const;

		template <spv::StorageClass C1, spv::StorageClass C2>
		var_t<float3_t, Assemble, spv::StorageClassFunction> Normal(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Epsilon) const;

		void SetMaterial(const std::shared_ptr<IMaterialInterface<Assemble>>& _pMaterial) { m_pMaterial = _pMaterial; }
		const std::shared_ptr<IMaterialInterface<Assemble>>& GetMaterial() const { return m_pMaterial; }

	private:
		std::shared_ptr<IMaterialInterface<Assemble>> m_pMaterial{ nullptr };
		std::shared_ptr<SDFObject<Assemble>> m_pLeftSDF{ nullptr };
		std::shared_ptr<SDFObject<Assemble>> m_pRightSDF{ nullptr };

		std::shared_ptr<CSGObject<Assemble>> m_pLeftCSG{ nullptr };
		std::shared_ptr<CSGObject<Assemble>> m_pRightCSG{ nullptr };
	};
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	using TCSGObj = std::shared_ptr<CSGObject<Assemble>>;

	// helper traits
	template<class T>
	constexpr bool derive_from_csg = std::is_base_of_v<CSGObject<true>, T> || std::is_base_of_v<CSGObject<false>, T>;

	template<class T>
	constexpr bool derive_from_sdf = std::is_base_of_v<SDFObject<true>, T> || std::is_base_of_v<SDFObject<false>, T>;

	template<class T>
	constexpr bool derive_from_obj = derive_from_sdf<T> || derive_from_csg<T>;

	template<class T, bool Assemble>
	constexpr bool derive_from_csg_expl = std::is_base_of_v<CSGObject<Assemble>, T>;

	template<class T, bool Assemble>
	constexpr bool derive_from_sdf_expl = std::is_base_of_v<SDFObject<Assemble>, T>;

	template<class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TCSGObj<T::AssembleParam> csg(const std::shared_ptr<T>& _pSource)
	{
		return std::make_shared<CSGObject<T::AssembleParam>>(_pSource);
	}

	template<class U, class V, typename = std::enable_if_t<derive_from_csg<U> && derive_from_csg<V>>>
	inline TCSGObj<U::AssembleParam> csg(const std::shared_ptr<U>& _pLeft, const std::shared_ptr<V>& _pRight)
	{
		static_assert(U::AssembleParam == V::AssembleParam, "Assemble parameter mismatch");
		return std::make_shared<CSGObject<U::AssembleParam>>(_pLeft, _pRight);
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	inline CSGObject<Assemble>::CSGObject(const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight) :
		m_pLeftCSG(_pLeft), m_pRightCSG(_pRight)
	{
	}

	template<bool Assemble>
	inline CSGObject<Assemble>::CSGObject(const std::shared_ptr<SDFObject<Assemble>>& _pLeft, const std::shared_ptr<SDFObject<Assemble>>& _pRight) :
		m_pLeftSDF(_pLeft), m_pRightSDF(_pRight)
	{
	}

	template<bool Assemble>
	inline CSGObject<Assemble>::CSGObject(const std::shared_ptr<SDFObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight) :
		m_pLeftSDF(_pLeft), m_pRightCSG(_pRight)
	{
	}

	template<bool Assemble>
	inline CSGObject<Assemble>::CSGObject(const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<SDFObject<Assemble>>& _pRight) :
		m_pLeftCSG(_pLeft), m_pRightSDF(_pRight)
	{
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template <spv::StorageClass C1>
	inline var_t<float, Assemble, spv::StorageClassFunction> CSGObject<Assemble>::Eval(const var_t<float3_t, Assemble, C1>& _Point) const
	{
		auto vPoint = PreEval(make_intermediate(_Point));

		if (m_pLeftSDF != nullptr && m_pRightSDF != nullptr)
		{
			return PostEval(Construct(m_pLeftSDF->Eval(vPoint), m_pRightSDF->Eval(vPoint)));
		}
		else if (m_pLeftCSG != nullptr && m_pRightCSG != nullptr)
		{
			return PostEval(Construct(m_pLeftCSG->Eval(vPoint), m_pRightCSG->Eval(vPoint)));
		}
		else if (m_pLeftCSG != nullptr && m_pRightSDF != nullptr)
		{
			return PostEval(Construct(m_pLeftCSG->Eval(vPoint), m_pRightSDF->Eval(vPoint)));
		}
		else if (m_pLeftSDF != nullptr && m_pRightCSG != nullptr)
		{
			return PostEval(Construct(m_pLeftSDF->Eval(vPoint), m_pRightCSG->Eval(vPoint)));
		}
		else if (m_pLeftSDF != nullptr)
		{
			return PostEval(m_pLeftSDF->Eval(vPoint));
		}
		else if (m_pRightSDF != nullptr)
		{
			return PostEval(m_pRightSDF->Eval(vPoint));
		}
		else if (m_pLeftCSG != nullptr)
		{
			return PostEval(m_pLeftCSG->Eval(vPoint));
		}
		else if (m_pRightCSG != nullptr)
		{
			return PostEval(m_pRightCSG->Eval(vPoint));
		}
		else
		{
			return make_const<Assemble>(0.f); // invalid config
		}
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble>
	template<spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> CSGObject<Assemble>::Normal(const var_t<float3_t, Assemble, C1>& p, const var_t<float, Assemble, C2>& e) const
	{
		return ForwardDiffNormal(p, e, [&](const auto& v) {return this->Eval(v); });
	}

	//---------------------------------------------------------------------------------------------------
	// user has to override this function:

	template<bool Assemble>
	inline var_t<float, Assemble, spv::StorageClassFunction> CSGObject<Assemble>::Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const
	{
		return UnionSDF(_lDist, _rDist); // default to union impl
	}
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	using UnionCSGObject = CSGObject<Assemble>;

	// Intersection
	template <bool Assemble>
	class IntersectCSGObject : public CSGObject<Assemble>
	{
	public:
		using CSGObject::CSGObject;
		virtual ~IntersectCSGObject() {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const final
		{
			return IntersectSDF(_lDist, _rDist);
		}
	};
	//---------------------------------------------------------------------------------------------------

	// Difference
	template <bool Assemble>
	class DifferenceCSGObject : public CSGObject<Assemble>
	{
	public:
		using CSGObject::CSGObject;
		virtual ~DifferenceCSGObject() {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const final
		{
			return DifferenceSDF(_lDist, _rDist);
		}
	};
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	using TUnionCSG = std::shared_ptr<CSGObject<Assemble>>;

	template <bool Assemble>
	using TIntersectionCSG = std::shared_ptr<IntersectCSGObject<Assemble>>;

	template <bool Assemble>
	using TDifferenceCSG = std::shared_ptr<DifferenceCSGObject<Assemble>>;

	//---------------------------------------------------------------------------------------------------

	template <class U, class V, typename = std::enable_if_t<derive_from_obj<U> && derive_from_obj<V>>>
	inline TUnionCSG<U::AssembleParam> operator&(const std::shared_ptr<U>& l, const std::shared_ptr<V>& r)
	{
		static_assert(U::AssembleParam == V::AssembleParam, "Assemble parameter mismatch");
		return std::make_shared<CSGObject<U::AssembleParam>>(l, r);
	}

	template <class U, class V, typename = std::enable_if_t<derive_from_obj<U> && derive_from_obj<V>>>
	inline TDifferenceCSG<U::AssembleParam> operator/(const std::shared_ptr<U>& l, const std::shared_ptr<V>& r)
	{
		static_assert(U::AssembleParam == V::AssembleParam, "Assemble parameter mismatch");
		return std::make_shared<DifferenceCSGObject<U::AssembleParam>>(l, r);
	}

	template <class U, class V, typename = std::enable_if_t<derive_from_obj<U> && derive_from_obj<V>>>
	inline TIntersectionCSG<U::AssembleParam> operator|(const std::shared_ptr<U>& l, const std::shared_ptr<V>& r)
	{
		static_assert(U::AssembleParam == V::AssembleParam, "Assemble parameter mismatch");
		return std::make_shared<IntersectCSGObject<U::AssembleParam>>(l, r);
	}

	//---------------------------------------------------------------------------------------------------

	// Translate by offset
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class TranslateCSGObject : public CSGObject<Assemble>
	{
	public:
		TranslateCSGObject(const float3_t& _vOffset, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), vOffset(_vOffset) {};
		TranslateCSGObject(const float3_t& _vOffset, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vOffset(_vOffset) {};
		
		template<spv::StorageClass C1>
		TranslateCSGObject(const var_t<float3_t, Assemble, C1>& _vOffset, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), vOffset(_vOffset) {};
		template<spv::StorageClass C1>
		TranslateCSGObject(const var_t<float3_t, Assemble, C1>& _vOffset, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vOffset(_vOffset) {};
		
		virtual ~TranslateCSGObject(){}

		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final { return _Point - vOffset; };

	private:
		var_t<float3_t, Assemble, Class> vOffset;
	};

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	using TTranslateCSG = std::shared_ptr<TranslateCSGObject<Assemble, Class>>;

	//---------------------------------------------------------------------------------------------------

	// translate CSG by offset
	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TTranslateCSG<Assemble> operator+(const std::shared_ptr<T>& l, const var_t<float3_t, Assemble, C1>& r)
	{
		return std::make_shared<TranslateCSGObject<Assemble>>(r, l);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TTranslateCSG<T::AssembleParam> operator+(const std::shared_ptr<T>& l, const float3_t& r)
	{
		return std::make_shared<TranslateCSGObject<T::AssembleParam>>(r, l);
	}

	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TTranslateCSG<Assemble> operator+(const var_t<float3_t, Assemble, C1>& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<TranslateCSGObject<Assemble>>(l, r);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TTranslateCSG<T::AssembleParam> operator+(const float3_t& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<TranslateCSGObject<T::T::AssembleParam>>(l, r);
	}

	//---------------------------------------------------------------------------------------------------

	// Scale
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class UniformScaleCSGObject : public CSGObject<Assemble>
	{
	public:
		UniformScaleCSGObject(const float& _fScale, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), fScale(_fScale) {};
		UniformScaleCSGObject(const float& _fScale, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), fScale(_fScale) {};

		template <spv::StorageClass C1>
		UniformScaleCSGObject(const var_t<float, Assemble, C1>& _fScale, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), fScale(_fScale) {};
		template <spv::StorageClass C1>
		UniformScaleCSGObject(const var_t<float, Assemble, C1>& _fScale, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), fScale(_fScale) {};

		virtual ~UniformScaleCSGObject() {}

		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final { return _Point / fScale; };
		inline var_t<float, Assemble, spv::StorageClassFunction> PostEval(const var_t<float, Assemble, spv::StorageClassFunction>& _fDist) const final { return _fDist * fScale; };

	private:
		var_t<float, Assemble, Class> fScale;
	};

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	using TUniformScaleCSG = std::shared_ptr<UniformScaleCSGObject<Assemble, Class>>;

	//---------------------------------------------------------------------------------------------------

	// scale CSG by factor
	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TUniformScaleCSG<Assemble> operator*(const std::shared_ptr<T>& l, const var_t<float, Assemble, C1>& r)
	{
		return std::make_shared<UniformScaleCSGObject<Assemble>>(r, l);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TUniformScaleCSG<T::AssembleParam> operator*(const std::shared_ptr<T>& l, const float& r)
	{
		return std::make_shared<UniformScaleCSGObject<T::AssembleParam>>(r, l);
	}

	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TUniformScaleCSG<Assemble> operator*(const var_t<float, Assemble, C1>& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<UniformScaleCSGObject<Assemble>>(l, r);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TUniformScaleCSG<T::AssembleParam> operator*(const float& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<UniformScaleCSGObject<T::AssembleParam>>(l, r);
	}

	//---------------------------------------------------------------------------------------------------

	// Rotation
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class RotationCSGObject : public CSGObject<Assemble>
	{
	public:
		RotationCSGObject(const float4_t& _vRotation, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), vRotation(_vRotation) {};
		RotationCSGObject(const float4_t& _vRotation, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vRotation(_vRotation) {};

		template <spv::StorageClass C1>
		RotationCSGObject(const SPIRVQuaternion<Assemble, C1>& _vRotation, const std::shared_ptr<SDFObject<Assemble>>& _pSource = nullptr) : CSGObject<Assemble>(_pSource), vRotation(_vRotation) {};
		template <spv::StorageClass C1>
		RotationCSGObject(const SPIRVQuaternion<Assemble, C1>& _vRotation, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight = nullptr) : CSGObject<Assemble>(_pLeft, _pRight), vRotation(_vRotation) {};

		virtual ~RotationCSGObject() {}

		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final { return vRotation.InverseRotateUnit(_Point); };

	private:
		SPIRVQuaternion<Assemble, Class> vRotation;
	};

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	using TRotationCSG = std::shared_ptr<RotationCSGObject<Assemble, Class>>;

	//---------------------------------------------------------------------------------------------------

	// rotate CSG by unit quaternion
	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TRotationCSG<Assemble> operator*(const std::shared_ptr<T>& l, const SPIRVQuaternion<Assemble, C1>& r)
	{
		return std::make_shared<RotationCSGObject<Assemble>>(r, l);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TRotationCSG<T::AssembleParam> operator*(const std::shared_ptr<T>& l, const float4_t& r)
	{
		return std::make_shared<RotationCSGObject<T::AssembleParam>>(r, l);
	}

	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TRotationCSG<Assemble> operator*(const SPIRVQuaternion<Assemble, C1>& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<RotationCSGObject<Assemble>>(l, r);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TRotationCSG<T::AssembleParam> operator*(const float4_t& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<RotationCSGObject<T::AssembleParam>>(l, r);
	}
	

	//---------------------------------------------------------------------------------------------------

	// blend between to csg objects
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class LinearBlendCSGObject : public CSGObject<Assemble>
	{
	public:
		LinearBlendCSGObject(const float& _fFactor, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight) : CSGObject<Assemble>(_pLeft, _pRight), fFactor(_fFactor) {};

		template <spv::StorageClass C1>
		LinearBlendCSGObject(const var_t<float, Assemble, C1>& _fFactor, const std::shared_ptr<CSGObject<Assemble>>& _pLeft, const std::shared_ptr<CSGObject<Assemble>>& _pRight) : CSGObject<Assemble>(_pLeft, _pRight), fFactor(_fFactor) {};

		virtual ~LinearBlendCSGObject() {}

		inline var_t<float, Assemble, spv::StorageClassFunction> Construct(const var_t<float, Assemble, spv::StorageClassFunction>& _lDist, const var_t<float, Assemble, spv::StorageClassFunction>& _rDist) const final
		{
			return Lerp(_lDist, _rDist, fFactor);
		}
	private:
		var_t<float, Assemble, Class> fFactor;
	};

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	using TLinearBlendCSG = std::shared_ptr<LinearBlendCSGObject<Assemble, Class>>;

	template <bool Assemble, class U, class V, spv::StorageClass C1, spv::StorageClass Class = spv::StorageClassFunction, typename = std::enable_if_t<derive_from_csg_expl<U, Assemble> && derive_from_csg_expl<V, Assemble>>>
	inline TLinearBlendCSG<Assemble, Class> Blend(const std::shared_ptr<U>& _pLeft, const std::shared_ptr<V>& _pRight, const var_t<float, Assemble, C1>& _fFactor)
	{
		return std::make_shared<LinearBlendCSGObject<Assemble, Class>>(_fFactor, _pLeft, _pRight);
	}

	template <class U, class V, spv::StorageClass Class = spv::StorageClassFunction, typename = std::enable_if_t<derive_from_csg<U> && derive_from_csg<V>>>
	inline TLinearBlendCSG<U::AssembleParam, Class> Blend(const std::shared_ptr<U>& _pLeft, const std::shared_ptr<V>& _pRight, const float& _fFactor)
	{
		static_assert(U::AssembleParam == V::AssembleParam, "Assemble parameter mismatch");
		return std::make_shared<LinearBlendCSGObject<U::AssembleParam, Class>>(_fFactor, _pLeft, _pRight);
	}
	//---------------------------------------------------------------------------------------------------

	// repeat csg objects
	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	class RepetitionCSGObject : public CSGObject<Assemble>
	{
	public:
		RepetitionCSGObject(const float3_t& _vRep, const std::shared_ptr<SDFObject<Assemble>>& _pLeft) : CSGObject<Assemble>(_pLeft), vRep(_vRep) {};
		RepetitionCSGObject(const float3_t& _vRep, const std::shared_ptr<CSGObject<Assemble>>& _pLeft) : CSGObject<Assemble>(_pLeft), vRep(_vRep) {};

		template <spv::StorageClass C1>
		RepetitionCSGObject(const var_t<float3_t, Assemble, C1>& _vRep, const std::shared_ptr<SDFObject<Assemble>>& _pLeft) : CSGObject<Assemble>(_pLeft), vRep(_vRep) {};

		template <spv::StorageClass C1>
		RepetitionCSGObject(const var_t<float3_t, Assemble, C1>& _vRep, const std::shared_ptr<CSGObject<Assemble>>& _pLeft) : CSGObject<Assemble>(_pLeft), vRep(_vRep) {};

		virtual ~RepetitionCSGObject() {}

		inline var_t<float3_t, Assemble, spv::StorageClassFunction> PreEval(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const final
		{
			return (_Point % vRep) - 0.5f * vRep;
		};
		
	private:
		var_t<float3_t, Assemble, Class> vRep;
	};

	template <bool Assemble, spv::StorageClass Class = spv::StorageClassFunction>
	using TRepetitionCSG = std::shared_ptr<RepetitionCSGObject<Assemble, Class>>;

	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TRepetitionCSG<Assemble> operator%(const std::shared_ptr<T>& l, const var_t<float3_t, Assemble, C1>& r)
	{
		return std::make_shared<RepetitionCSGObject<Assemble>>(r, l);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TRepetitionCSG<T::AssembleParam> operator%(const std::shared_ptr<T>& l, const float3_t& r)
	{
		return std::make_shared<RepetitionCSGObject<T::AssembleParam>>(r, l);
	}

	template <bool Assemble, spv::StorageClass C1, class T, typename = std::enable_if_t<std::is_base_of_v<CSGObject<Assemble>, T> || std::is_base_of_v<SDFObject<Assemble>, T>>>
	inline TRepetitionCSG<Assemble> operator%(const var_t<float3_t, Assemble, C1>& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<RepetitionCSGObject<Assemble>>(l, r);
	}

	template <class T, typename = std::enable_if_t<derive_from_obj<T>>>
	inline TRepetitionCSG<T::AssembleParam> operator%(const float3_t& l, const std::shared_ptr<T>& r)
	{
		return std::make_shared<RepetitionCSGObject<T::AssembleParam>>(l, r);
	}

	//---------------------------------------------------------------------------------------------------
	// CSG SCENE
	//---------------------------------------------------------------------------------------------------

	template <bool Assemble>
	class CSGScene
	{
	public:
		CSGScene(std::initializer_list<std::shared_ptr<CSGObject<Assemble>>> _Objects = {}) : m_Objects(_Objects) {}
		CSGScene(const std::vector<std::shared_ptr<CSGObject<Assemble>>>& _Objects) : m_Objects(_Objects) {}

		virtual ~CSGScene() {}

		template <spv::StorageClass C1>
		inline var_t<float, Assemble, spv::StorageClassFunction> Eval(const var_t<float3_t, Assemble, C1>& _Point) const
		{
			HASSERT(m_Objects.empty() == false, "CSGScene is empty, nothing to be evaluated");

			auto dist = m_Objects.front()->Eval(_Point);

			for (uint32_t i = 1u; i < m_Objects.size(); ++i)
			{
				dist = UnionSDF(m_Objects[i]->Eval(_Point), dist);
			}

			return dist;
		}

		template <spv::StorageClass C1, spv::StorageClass C2>
		inline var_t<float3_t, Assemble, spv::StorageClassFunction> Normal(const var_t<float3_t, Assemble, C1>& _Point, const var_t<float, Assemble, C2>& _Epsilon) const
		{
			return ForwardDiffNormal(_Point, _Epsilon, [&](const auto& v) {return this->Eval(v); });
		}

		const std::vector<std::shared_ptr<CSGObject<Assemble>>>& GetObjects() const { return m_Objects; }

	private:
		std::vector<std::shared_ptr<CSGObject<Assemble>>> m_Objects;
	};

	//---------------------------------------------------------------------------------------------------

} // Spear

#endif // !SPEAR_CSGOBJECT_H
