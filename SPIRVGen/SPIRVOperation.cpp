//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#include "SPIRVOperation.h"
#include "SPIRVBinaryDefines.h"

using namespace Spear;

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, const SPIRVOperand& _Operand) :
	m_kOpCode(_kOp), m_Operands(1u, _Operand), m_uResultTypeId(_uResultTypeId)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const SPIRVOperand& _Operand) :
	m_kOpCode(_kOp), m_Operands(1u, _Operand)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, const std::vector<SPIRVOperand>& _Operands) :
	m_kOpCode(_kOp), m_Operands(_Operands), m_uResultTypeId(_uResultTypeId)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, std::vector<SPIRVOperand>&& _Operands) : 
    m_kOpCode(_kOp), m_uResultTypeId(_uResultTypeId), m_Operands(std::move(_Operands))
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const std::vector<SPIRVOperand>& _Operands) noexcept :
	m_kOpCode(_kOp), m_Operands(_Operands)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const std::vector<uint32_t>& _Literals) :
	m_kOpCode(_kOp)
{
	AddLiterals(_Literals);
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(const SPIRVOperation& _Other) : 
    m_bTranslated(_Other.m_bTranslated),
    m_bUsed(_Other.m_bUsed),
    m_kOpCode(_Other.m_kOpCode),
    m_Operands(_Other.m_Operands),
    m_uInstrId(_Other.m_uInstrId),
    m_uResultId(_Other.m_uResultId),
    m_uResultTypeId(_Other.m_uResultTypeId)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::SPIRVOperation(SPIRVOperation&& _Other) :
    m_bTranslated(std::move(_Other.m_bTranslated)),
    m_bUsed(std::move(_Other.m_bUsed)),
    m_kOpCode(std::move(_Other.m_kOpCode)),
    m_Operands(std::move(_Other.m_Operands)),
    m_uInstrId(std::move(_Other.m_uInstrId)),
    m_uResultId(std::move(_Other.m_uResultId)),
    m_uResultTypeId(std::move(_Other.m_uResultTypeId))
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation::~SPIRVOperation()
{
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation& SPIRVOperation::operator=(const SPIRVOperation & _Other)
{
    m_bTranslated =_Other.m_bTranslated;
    m_bUsed = _Other.m_bUsed;
    m_kOpCode = _Other.m_kOpCode;
    m_Operands = _Other.m_Operands;
    m_uInstrId = _Other.m_uInstrId;
    m_uResultId = _Other.m_uResultId;
    m_uResultTypeId = _Other.m_uResultTypeId;
    return *this;
}
//---------------------------------------------------------------------------------------------------

SPIRVOperation& SPIRVOperation::operator=(SPIRVOperation&& _Other)
{
    m_bTranslated = std::move(_Other.m_bTranslated);
    m_bUsed = std::move(_Other.m_bUsed);
    m_kOpCode = std::move(_Other.m_kOpCode);
    m_Operands = std::move(_Other.m_Operands);
    m_uInstrId = std::move(_Other.m_uInstrId);
    m_uResultId = std::move(_Other.m_uResultId);
    m_uResultTypeId = std::move(_Other.m_uResultTypeId);
    return *this;
}
//---------------------------------------------------------------------------------------------------

std::string SPIRVOperation::GetString() const
{
	std::string sOp;
	
	if (m_uInstrId != HUNDEFINED32)
	{
		sOp += "%" + std::to_string(m_uInstrId) + " =\t"; 
	}

	sOp += GetOpCodeString(m_kOpCode) + " ";

	if (m_uResultTypeId != HUNDEFINED32)
	{
		sOp += "%" + std::to_string(m_uResultTypeId) + "t ";
	}

	for (const SPIRVOperand& Operand : m_Operands)
	{
		if (Operand.kType == kOperandType_Intermediate)
		{
			sOp += "%" + std::to_string(Operand.uId) + "i ";
		}
		else if (Operand.kType == kOperandType_Literal)
		{
			if (Operand.uId < 255)
			{
				sOp += std::to_string(Operand.uId) + " ";
			}
			else
			{
				sOp += LiteralToString(Operand.uId) + " ";
			}
		}
	}

	return sOp;
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddOperand(const SPIRVOperand& _Operand)
{
	m_Operands.push_back(_Operand);
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddIntermediate(const uint32_t _uId)
{
	m_Operands.push_back(SPIRVOperand(kOperandType_Intermediate, _uId));
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddLiteral(const uint32_t _uLiteral1)
{
	m_Operands.push_back(SPIRVOperand(kOperandType_Literal, _uLiteral1));
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddLiterals(const std::vector<uint32_t>& _Literals)
{
	for (const uint32_t& uLiteral : _Literals)
	{
		m_Operands.push_back(SPIRVOperand(kOperandType_Literal, uLiteral));
	}
}
//---------------------------------------------------------------------------------------------------

void SPIRVOperation::AddTypes(const std::vector<uint32_t>& _Types)
{
	for (const uint32_t& uType : _Types)
	{
		m_Operands.push_back(SPIRVOperand(kOperandType_Intermediate, uType));
	}
}
//---------------------------------------------------------------------------------------------------
