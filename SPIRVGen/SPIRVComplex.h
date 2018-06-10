//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVCOMPLEX_H
#define SPEAR_SPIRVCOMPLEX_H

#include "SPIRVOperatorImpl.h"

namespace Spear
{
	// z = a + bi
	// a = real, b = imag
	template <bool Assemble = true, spv::StorageClass Class = spv::StorageClassFunction>
	struct SPIRVComplex : public var_t<float2_t, Assemble, Class>
	{
		using var_t::var_t;

		//template <class ...Ts>
		//SPIRVComplex(const Ts& ... args) : VarType(args...) {}

		template <spv::StorageClass C1>
		const SPIRVComplex& operator=(const SPIRVComplex<Assemble, C1>& _Other) const;

		var_t<float, Assemble, spv::StorageClassFunction> Conjugate() const;
		var_t<float, Assemble, spv::StorageClassFunction> Norm() const;
		SPIRVComplex<Assemble, spv::StorageClassFunction> Inverse() const;

		// operators
		template <spv::StorageClass C1>
		const SPIRVComplex& operator*=(const SPIRVComplex<Assemble, C1>& _Other) const;

		template <spv::StorageClass C1>
		const SPIRVComplex& operator/=(const SPIRVComplex<Assemble, C1>& _Other) const;
	};

	//---------------------------------------------------------------------------------------------------
	// assignment
	template<bool Assemble, spv::StorageClass Class>
	template <spv::StorageClass C1>
	inline const SPIRVComplex<Assemble, Class>& SPIRVComplex<Assemble, Class>::operator=(const SPIRVComplex<Assemble, C1>& _Other) const
	{
		var_t<float2_t, Assemble, Class>::operator=(_Other);
		return *this;
	}

	//---------------------------------------------------------------------------------------------------
	template<bool Assemble, spv::StorageClass Class>
	inline var_t<float, Assemble, spv::StorageClassFunction> SPIRVComplex<Assemble, Class>::Conjugate() const
	{
		return Dot(*this, *this);
		//return x*x + y*y;
	}
	//---------------------------------------------------------------------------------------------------

	template<bool Assemble, spv::StorageClass Class>
	inline var_t<float, Assemble, spv::StorageClassFunction> SPIRVComplex<Assemble, Class>::Norm() const
	{
		return Sqrt(Conjugate());
	}
	//---------------------------------------------------------------------------------------------------
	// inverse
	template<bool Assemble, spv::StorageClass Class>
	inline SPIRVComplex<Assemble, spv::StorageClassFunction> SPIRVComplex<Assemble, Class>::Inverse() const
	{
		auto COut = SPIRVComplex<Assemble, spv::StorageClassFunction>();
		const var_t<float, Assemble, spv::StorageClassFunction> fRcpConj = 1.0f / Conjugate();
		COut.x = x * fRcpConj;
		COut.y = -1.0f * (y * fRcpConj);
		return COut;
	}

	//---------------------------------------------------------------------------------------------------
	// Complex Multiplication
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline void CMul(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2, const SPIRVComplex<Assemble, C3>& _cOut)
	{
		// z1z2 = (a1 + b1i)(a2 + b2i) =
		//		= (a1a2 - b1b2)(a1b2 + b1a2)i
		const auto A1 = _c1.x; const auto B1 = _c1.y;
		const auto A2 = _c2.x; const auto B2 = _c2.y;
		_cOut.x = A1 * A2 - B1 * B2;
		_cOut.y = A1 * B2 + B1 * A2;
	}

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVComplex<Assemble, Class>& SPIRVComplex<Assemble, Class>::operator*=(const SPIRVComplex<Assemble, C1>& _Other) const
	{
		CMul(*this, _Other, *this);
		return *this;
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator*(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2)
	{
		auto COut = SPIRVComplex<Assemble, spv::StorageClassFunction>();
		CMul(_c1, _c2, COut);
		return COut;
	}

	//---------------------------------------------------------------------------------------------------
	// Complex Division
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline void CDiv(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2, SPIRVComplex<Assemble, C3>& _cOut)
	{
		// z1+z2 = (a1 + b1i)/(a2 + b2i) =
		//		 = (a1a2+b1b2)/(a2^2+b2^2) + (b1a2-a1b2)/(a2^2+b2^2)i
		const auto A1 = _c1.x; const auto B1 = _c1.y;
		const auto A2 = _c2.x; const auto B2 = _c2.y;
		const auto fRcpDenom = 1.0f / (A2 * A2 + B2 * B2);
		_cOut.x = (A1*A2 + B1*B2) * fRcpDenom;
		_cOut.y = (B1*A2 - A1*B2) * fRcpDenom;
	}

	template<bool Assemble, spv::StorageClass Class>
	template<spv::StorageClass C1>
	inline const SPIRVComplex<Assemble, Class>& SPIRVComplex<Assemble, Class>::operator/=(const SPIRVComplex<Assemble, C1>& _Other) const
	{
		CDiv(*this, _Other, *this);
		return *this;
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator/(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2)
	{
		auto COut = SPIRVComplex<Assemble, spv::StorageClassFunction>();
		CDiv(_c1, _c2, COut);
		return COut;
	}

	//---------------------------------------------------------------------------------------------------
	// global operators from float2
	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator*(const SPIRVComplex<Assemble, C1>& _c1, const var_t<float, Assemble, C2>& _fScalar)
	{
		return static_cast<const var_t<float2_t, Assemble, C1>&>(_c1) * static_cast<const var_t<float, Assemble, C2>&>(_fScalar);
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator/(const SPIRVComplex<Assemble, C1>& _c1, const var_t<float, Assemble, C2>& _fScalar)
	{
		return static_cast<const var_t<float2_t, Assemble, C1>&>(_c1) / static_cast<const var_t<float, Assemble, C2>&>(_fScalar);
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator+(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2)
	{
		return static_cast<const var_t<float2_t, Assemble, C1>&>(_c1) + static_cast<const var_t<float2_t, Assemble, C2>&>(_c2);
	}

	template<bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline const SPIRVComplex<Assemble, spv::StorageClassFunction> operator-(const SPIRVComplex<Assemble, C1>& _c1, const SPIRVComplex<Assemble, C2>& _c2)
	{
		return static_cast<const var_t<float2_t, Assemble, C1>&>(_c1) - static_cast<const var_t<float2_t, Assemble, C2>&>(_c2);
	}
}

#endif // !SPEAR_SPIRVCOMPLEX_H