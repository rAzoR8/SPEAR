//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#include "SPIRVInstruction.h"
#include "SPIRVBinaryDefines.h" // for decode

using namespace Spear;

//---------------------------------------------------------------------------------------------------

SPIRVInstruction::SPIRVInstruction(
	const spv::Op _kOp,
	const uint32_t _uTypeId,
	const uint32_t _uResultId,
	const std::vector<uint32_t>& _Operands) noexcept :
	m_kOperation(_kOp),
	m_uTypeId(_uTypeId),
	m_uResultId(_uResultId),
	m_Operands(_Operands) 
{
}

//---------------------------------------------------------------------------------------------------

uint32_t Decode(const std::vector<uint32_t>& _Words, const uint32_t _uOffset, SPIRVInstruction& _OutInstr)
{
	uint32_t uWordCount = 1;
	uint32_t uOffset = _uOffset;

	auto GetWord = [&]() -> uint32_t
	{
		return (uOffset < _Words.size() && (--uWordCount > 0)) ? _Words[uOffset++] : SPIRVInstruction::kInvalidId;
	};

	const uint32_t& uOpCode = GetWord();

	if (uOpCode != SPIRVInstruction::kInvalidId)
	{
		const spv::Op kOp = static_cast<spv::Op>(uOpCode & spv::OpCodeMask);
		uWordCount = uOpCode & (spv::OpCodeMask << spv::WordCountShift);
		uint32_t uTypeId = SPIRVInstruction::kInvalidId;
		uint32_t uResultId = SPIRVInstruction::kInvalidId;
		std::vector<uint32_t> Operands;

		const TSPVArgFlag kArgs = GetOpCodeArgs(kOp);

		if (kArgs.CheckFlag(kSPVOpArgs_TypeId))
		{
			uTypeId = GetWord();
		}

		if (kArgs.CheckFlag(kSPVOpArgs_ResultId))
		{
			uResultId = GetWord();
		}

		for (uint32_t uOperand = GetWord(); uOperand != SPIRVInstruction::kInvalidId; uOperand = GetWord())
		{
			Operands.push_back(uOperand);
		}
		
		_OutInstr = SPIRVInstruction(kOp, uTypeId, uResultId, Operands);
	}

	return uOffset - _uOffset;
}
//---------------------------------------------------------------------------------------------------

SPIRVInstruction::~SPIRVInstruction()
{
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVInstruction::GetOpCode() const noexcept
{
	uint16_t uWordCount = 1u + static_cast<uint16_t>(m_Operands.size());

	if (m_uTypeId != kInvalidId)
		++uWordCount;

	if (m_uResultId != kInvalidId)
		++uWordCount;

	return (m_kOperation & spv::OpCodeMask) | (uWordCount << spv::WordCountShift);
}
//---------------------------------------------------------------------------------------------------

std::string SPIRVInstruction::GetString() const
{
	std::string sOp;
	if (m_uResultId != kInvalidId)
	{
		sOp = "%" + std::to_string(m_uResultId) + "=";
	}

	sOp = "\t" + GetOpCodeString(m_kOperation);

	if (m_uTypeId != kInvalidId)
	{
		sOp += " type_" + std::to_string(m_uTypeId);
	}

	std::string sLiteralStr;
	for (const uint32_t& uOperand : m_Operands)
	{
		if (uOperand < 255)
		{
			sOp += " op_"+  std::to_string(uOperand);
		}
		else
		{
			sLiteralStr += LiteralToString(uOperand);
		}
	}

	if (sLiteralStr.empty() == false)
		sOp += " " + sLiteralStr;

	return sOp;
}
//---------------------------------------------------------------------------------------------------
