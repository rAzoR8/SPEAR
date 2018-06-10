//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#include "SPIRVDecoration.h"
#include "Logger.h"

using namespace Spear;

//---------------------------------------------------------------------------------------------------

SPIRVOperation SPIRVDecoration::MakeOperation(const uint32_t _uTargetId, const uint32_t _uMemberIndex) const
{
	const uint32_t uTargetId = _uTargetId == HUNDEFINED32 ? m_uTargetId : _uTargetId;
	const uint32_t uMemberIndex = _uMemberIndex == HUNDEFINED32 ? m_uMemberIndex : _uMemberIndex;

	HASSERT(uTargetId != HUNDEFINED32, "Invalid target id");
	HASSERT(m_kDecoration < spv::DecorationMax, "Invalid decoration");

	// target / base id
	std::vector<SPIRVOperand> Operands = { SPIRVOperand(kOperandType_Intermediate, uTargetId) };

	spv::Op kOp = spv::OpNop;
	if (uMemberIndex == HUNDEFINED32)
	{
		kOp = spv::OpDecorate;
	}
	else
	{	
		kOp = spv::OpMemberDecorate;
		Operands.push_back(SPIRVOperand::Literal(uMemberIndex));
	}

	Operands.push_back(SPIRVOperand::Literal((uint32_t)m_kDecoration));

	SPIRVOperation OpDecorate(kOp, Operands);
	OpDecorate.AddLiterals(m_Literals);

	return OpDecorate;
}

//---------------------------------------------------------------------------------------------------
