//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#include "SPIRVType.h"
#include "Logger.h"
#include "HashUtils.h"

using namespace Spear;

//---------------------------------------------------------------------------------------------------

SPIRVType::SPIRVType(const spv::Op _kOp, uint32_t _uDimension, const bool _bSign) :
	m_kBaseType(_kOp), m_uDimension(_uDimension), m_bSign(_bSign)
{
	HASSERT(_kOp >= spv::OpTypeVoid && _kOp <= spv::OpTypeForwardPointer, "Invalid Type");
}
//---------------------------------------------------------------------------------------------------

SPIRVType::SPIRVType(const spv::Op _kOp, const SPIRVType& _SubType, const uint32_t _uDimension, const bool _bSign) :
	m_kBaseType(_kOp), m_uDimension(_uDimension), m_bSign(_bSign), m_SubTypes({_SubType})
{
	HASSERT(_kOp >= spv::OpTypeVoid && _kOp <= spv::OpTypeForwardPointer, "Invalid Type");
}
//---------------------------------------------------------------------------------------------------

SPIRVType::SPIRVType(const spv::Op _kOp, const std::vector<SPIRVType>& _SubTypes, const uint32_t _uDimension, const bool _bSign) :
	m_kBaseType(_kOp), m_uDimension(_uDimension), m_bSign(_bSign), m_SubTypes(_SubTypes)
{
	HASSERT(_kOp >= spv::OpTypeVoid && _kOp <= spv::OpTypeForwardPointer, "Invalid Type");
}
//---------------------------------------------------------------------------------------------------

SPIRVType::SPIRVType(const SPIRVType& _SampledType, const spv::Dim _uDimension, const bool _bArray, const ETexDepthType _kDepthType, const bool _bMultiSampled, const ETexSamplerAccess _kSamplerAccess) :
	m_SubTypes(1u, _SampledType), m_kBaseType(spv::OpTypeImage), m_uDimension(_uDimension), m_bArray(_bArray), m_kTexDepthType(_kDepthType), m_bMultiSampled(_bMultiSampled), m_kSamplerAccess(_kSamplerAccess)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVType::~SPIRVType()
{
}
//---------------------------------------------------------------------------------------------------

SPIRVType& SPIRVType::Append(const SPIRVType& _SubType)
{
	if (m_SubTypes.empty())
	{
		m_SubTypes.push_back(_SubType);
	}
	else
	{
		m_SubTypes.back().Append(_SubType);
	}

	return *this;
}
//---------------------------------------------------------------------------------------------------

SPIRVType& SPIRVType::Member(const SPIRVType& _SubType)
{
	m_SubTypes.push_back(_SubType);
	return *this;
}
//---------------------------------------------------------------------------------------------------

size_t SPIRVType::GetHash() const
{
	size_t uHash = hlx::Hash(m_kBaseType, m_uDimension, m_bSign, m_bArray, m_bMultiSampled, m_kTexDepthType, m_kSamplerAccess);

	for (const SPIRVType& subtype : m_SubTypes)
	{
		uHash = hlx::CombineHashes(uHash, subtype.GetHash());
	}
	
	return uHash;
}
//---------------------------------------------------------------------------------------------------
uint32_t SPIRVType::GetSize() const
{
	uint32_t uSize = 0u;

	switch (m_kBaseType)
	{
	case spv::OpTypeBool: // not sure about the bool, in uniformes its implicitly converted to int
	case spv::OpTypeInt:
	case spv::OpTypeFloat:
		uSize += 4u;
		break;
	case spv::OpTypeVector:
	case spv::OpTypeMatrix:
	case spv::OpTypeArray:
		HASSERT(m_SubTypes.size() == 1u, "Invalid number of sub types");
		uSize += m_SubTypes.front().GetSize() * m_uDimension;
		break;
	case spv::OpTypeStruct:
		for (const SPIRVType& SubType : m_SubTypes)
		{
			uSize += SubType.GetSize();
		}
		break;
	default:
		break;
	}

	return uSize;
}
//---------------------------------------------------------------------------------------------------
