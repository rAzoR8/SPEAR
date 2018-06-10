//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#include "SPIRVConstant.h"
#include "HashUtils.h"
#include "Logger.h"

using namespace Spear;
//---------------------------------------------------------------------------------------------------

SPIRVConstant::SPIRVConstant(
	const spv::Op _kConstantType,
	const SPIRVType& _CompositeType,
	const std::vector<uint32_t>& _Constants) :
	m_kConstantType(_kConstantType),
	m_CompositeType(_CompositeType),
	m_Constants(_Constants)
{
	HASSERT(_kConstantType >= spv::OpConstantTrue && _kConstantType <= spv::OpSpecConstantOp, "Invalid constant type");
	switch (_kConstantType)
	{
	case spv::OpConstantTrue:
	case spv::OpConstantFalse:
	case spv::OpSpecConstantTrue:
	case spv::OpSpecConstantFalse:
		m_CompositeType = SPIRVType::Bool();
	default:
		break;
	}
}
//---------------------------------------------------------------------------------------------------

SPIRVConstant::SPIRVConstant(
	const spv::Op _kConstantType,
	const SPIRVType& _CompositeType,
	const std::vector<SPIRVConstant>& _Components) : 
	m_kConstantType(_kConstantType),
	m_CompositeType(_CompositeType),
	m_Components(_Components)
{
	HASSERT(_kConstantType == spv::OpConstantComposite || _kConstantType == spv::OpSpecConstantComposite, "Invalid constant type");
}
//---------------------------------------------------------------------------------------------------

SPIRVConstant::~SPIRVConstant()
{
}

//---------------------------------------------------------------------------------------------------
SPIRVConstant::SPIRVConstant(const SPIRVConstant& _Other) :
	m_kConstantType(_Other.m_kConstantType),
	m_CompositeType(_Other.m_CompositeType),
	m_Constants(_Other.m_Constants),
	m_Components(_Other.m_Components)
{
}
//---------------------------------------------------------------------------------------------------
size_t SPIRVConstant::GetHash(const bool _bParent) const
{
	size_t uHash = hlx::CombineHashes(hlx::Hash(m_kConstantType), _bParent ? m_CompositeType.GetHash() : kUndefinedSizeT);

	for (const uint32_t& cval : m_Constants)
	{
		uHash = hlx::CombineHashes(uHash, cval);
	}

	for (const SPIRVConstant& Component : m_Components)
	{
		uHash = hlx::CombineHashes(uHash, Component.GetHash(false));
	}

	return uHash;
}
//---------------------------------------------------------------------------------------------------
