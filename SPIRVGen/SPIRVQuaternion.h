//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVQUATERNION_H
#define SPEAR_SPIRVQUATERNION_H

#include "SPIRVOperatorImpl.h"
//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/

namespace Spear
{
	// from Assembly pov it might make more sense to define quaternion_t as {float s, float3_t v} to spare all the extract & insert operations when accessing components
	// but the main benefit is that quaternion_t is a float4_t equivalent and can be indexed & transformed in the same way
	// the previous version used the glm:quat type but since it does not derive from vec4 to inherit all the implemented operations & traits, float4_t is used here

	template <bool Assemble = true, spv::StorageClass Class = spv::StorageClassFunction>
	struct SPIRVQuaternion : public var_t<float4_t, Assemble, Class>
	{
		using var_t::var_t;

		SPIRVQuaternion() {}

		// construct from rotation axis & radian angle
		template <spv::StorageClass C1, spv::StorageClass C2>
		SPIRVQuaternion(const var_t<float3_t, Assemble, C1>& _vAxis, const var_t<float, Assemble, C2>& _fAngleRad);

		SPIRVQuaternion(const float3_t& _vAxis, const float& _fAngleRad);

		SPIRVQuaternion(const float4_t& _vQuat);

		template <spv::StorageClass C1>
		const SPIRVQuaternion& operator*=(const SPIRVQuaternion<Assemble, C1>& _Other) const;

		SPIRVQuaternion<Assemble, spv::StorageClassFunction> Conjugate() const;
		var_t<float, Assemble, spv::StorageClassFunction> Norm() const;
		SPIRVQuaternion<Assemble, spv::StorageClassFunction> Inverse() const;

		var_t<float3_t, Assemble, spv::StorageClassFunction> Rotate(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const;

		// assumes quaternion has unit length => q^-1 = conjugate(q)
		var_t<float3_t, Assemble, spv::StorageClassFunction> RotateUnit(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const;

		var_t<float3_t, Assemble, spv::StorageClassFunction> InverseRotate(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const;
		var_t<float3_t, Assemble, spv::StorageClassFunction> InverseRotateUnit(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const;

		// helper
		static inline float4_t angleAxis(const float3_t& _vAxis, const float& _fAngleRad)
		{
			return { _vAxis * std::sinf(_fAngleRad * 0.5f), std::cosf(_fAngleRad * 0.5f) };
		}
	};

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1, spv::StorageClass C2>
	inline SPIRVQuaternion<Assemble, Class>::SPIRVQuaternion(const var_t<float3_t, Assemble, C1>& _vAxis, const var_t<float, Assemble, C2>& _fAngleRad)
	{
		const auto a = _fAngleRad * 0.5f;
		xyz = _vAxis * Sin(a);
		w = Cos(a);
	}

	template<bool Assemble, spv::StorageClass Class>
	inline SPIRVQuaternion<Assemble, Class>::SPIRVQuaternion(const float3_t& _vAxis, const float& _fAngleRad) : VarType(angleAxis(_vAxis, _fAngleRad)){	}

	template<bool Assemble, spv::StorageClass Class>
	inline SPIRVQuaternion<Assemble, Class>::SPIRVQuaternion(const float4_t& _vQuat) : VarType(_vQuat){}

	//---------------------------------------------------------------------------------------------------
	// Helper function

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline void QMul(const SPIRVQuaternion<Assemble, C1>& q1, const SPIRVQuaternion<Assemble, C2>& q2, const SPIRVQuaternion<Assemble, C3>& qout)
	{
		//https://gist.github.com/mattatz/40a91588d5fb38240403f198a938a593
		//var.xyz = q2.xyz * q1.w + q1.xyz * q2.w + cross(q1.xyz, q2.xyz);
		//var.w = q1.w * q2.w - dot(q1.xyz, q2.xyz);

		const auto q1axis = q1.xyz; const auto q1angle = q1.w;
		const auto q2axis = q2.xyz; const auto q2angle = q2.w;
		qout.xyz = q2axis * q1angle + q1axis * q2angle + Cross(q1axis, q2axis);
		qout.w = q1angle * q2angle - Dot(q1axis, q2axis);
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline SPIRVQuaternion<Assemble, spv::StorageClassFunction> operator*(const SPIRVQuaternion<Assemble, C1>& l, const SPIRVQuaternion<Assemble, C2>& r)
	{
		auto var = SPIRVQuaternion<Assemble, spv::StorageClassFunction>();	
		QMul(l, r, var);
		return var;
	}

	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVQuaternion<Assemble, Class>& SPIRVQuaternion<Assemble, Class>::operator*=(const SPIRVQuaternion<Assemble, C1>& _Other) const
	{
		QMul(*this, _Other, *this);
		return *this;
	}

	//---------------------------------------------------------------------------------------------------


	template<bool Assemble, spv::StorageClass Class>
	inline SPIRVQuaternion<Assemble, spv::StorageClassFunction> SPIRVQuaternion<Assemble, Class>::Conjugate() const
	{
		return SPIRVQuaternion<Assemble, spv::StorageClassFunction>(-xyz, w); // todo: replace with construct_var
	}

	template<bool Assemble, spv::StorageClass Class>
	inline var_t<float, Assemble, spv::StorageClassFunction> SPIRVQuaternion<Assemble, Class>::Norm() const
	{
		return Sqrt(Dot(*this, *this));
	}

	template<bool Assemble, spv::StorageClass Class>
	inline SPIRVQuaternion<Assemble, spv::StorageClassFunction> SPIRVQuaternion<Assemble, Class>::Inverse() const
	{
		return Conjugate() / Dot(*this, *this);
	}

	template<bool Assemble, spv::StorageClass Class>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> SPIRVQuaternion<Assemble, Class>::Rotate(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const
	{
		return (*this * SPIRVQuaternion<Assemble, spv::StorageClassFunction>(_Point, 0.f) * Inverse()).xyz;
	}

	template<bool Assemble, spv::StorageClass Class>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> SPIRVQuaternion<Assemble, Class>::RotateUnit(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const
	{
		return (*this * SPIRVQuaternion<Assemble, spv::StorageClassFunction>(_Point, 0.f) * Conjugate()).xyz;
	}

	template<bool Assemble, spv::StorageClass Class>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> SPIRVQuaternion<Assemble, Class>::InverseRotate(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const
	{
		return (Inverse() * SPIRVQuaternion<Assemble, spv::StorageClassFunction>(_Point, 0.f) * (*this)).xyz;
	}

	template<bool Assemble, spv::StorageClass Class>
	inline var_t<float3_t, Assemble, spv::StorageClassFunction> SPIRVQuaternion<Assemble, Class>::InverseRotateUnit(const var_t<float3_t, Assemble, spv::StorageClassFunction>& _Point) const
	{
		return (Conjugate() * SPIRVQuaternion<Assemble, spv::StorageClassFunction>(_Point, 0.f) * (*this)).xyz;
	}

} //Spear

#endif // !SPEAR_SPIRVQUATERNION_H
