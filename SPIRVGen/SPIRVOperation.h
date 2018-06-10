//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVOPERATION_H
#define SPEAR_SPIRVOPERATION_H

#include <vulkan\spirv.hpp>
#include "StandardDefines.h"

namespace Spear
{
	enum EOperandType : uint32_t
	{
		kOperandType_Intermediate, // result of a instruction
		kOperandType_Literal, 
		kOperandType_Unknown, // unmapped
	};

	struct SPIRVOperand
	{
		SPIRVOperand(const EOperandType _kType = kOperandType_Unknown, const uint32_t _uId = HUNDEFINED32) noexcept :
			kType(_kType), uId(_uId) {};

        SPIRVOperand(const SPIRVOperand& _Other) noexcept : kType(_Other.kType), uId(_Other.uId) {}
        SPIRVOperand(SPIRVOperand&& _Other) noexcept : kType(std::move(_Other.kType)), uId(std::move(_Other.uId)) {}

        SPIRVOperand& operator=(const SPIRVOperand& _Other) noexcept
        {
            kType = _Other.kType;
            uId = _Other.uId;
            return *this;
        }

        SPIRVOperand& operator=(SPIRVOperand&& _Other) noexcept
        {
            kType = std::move(_Other.kType);
            uId = std::move(_Other.uId);
            return *this;
        }

		static SPIRVOperand Intermediate(const uint32_t _uId) noexcept {return SPIRVOperand(kOperandType_Intermediate, _uId);	}
		static SPIRVOperand Literal(const uint32_t _uLiteral1) noexcept { return SPIRVOperand(kOperandType_Literal, _uLiteral1); }

		EOperandType kType;		
		uint32_t uId;
	};

	inline bool operator==(const SPIRVOperand& l, const SPIRVOperand& r) noexcept
	{
		return l.kType == r.kType && l.uId == r.uId;
	}

	inline bool operator!=(const SPIRVOperand& l, const SPIRVOperand& r) noexcept
	{
		return l.kType != r.kType || l.uId != r.uId;
	}


	// The SPIRV operation is the immediate logical counter part to the SPIRV instruction
	// and is used in a SPIRV program when resolving and assembling the instruction stream
	class SPIRVOperation
	{
		friend class SPIRVAssembler;
	public:
		SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, const SPIRVOperand& _Operand);
		SPIRVOperation(const spv::Op _kOp, const SPIRVOperand& _Operand);

        template <class ...Operands>
        SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, Operands&&... _Operands);

		SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, const std::vector<SPIRVOperand>& _Operands = {});
        SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, std::vector<SPIRVOperand>&& _Operands);

		SPIRVOperation(const spv::Op _kOp = spv::OpNop, const std::vector<SPIRVOperand>& _Operands = {}) noexcept;

		SPIRVOperation(const spv::Op _kOp, const std::vector<uint32_t>& _Literals);

        SPIRVOperation(const SPIRVOperation& _Other);
        SPIRVOperation(SPIRVOperation&& _Other);

		~SPIRVOperation();

        SPIRVOperation& operator=(const SPIRVOperation& _Other);
        SPIRVOperation& operator=(SPIRVOperation&& _Other);

		std::string GetString() const;

		void AddOperand(const SPIRVOperand& _Operand);
		void AddIntermediate(const uint32_t _uId);
		void AddLiteral(const uint32_t _uLiteral1);

		void AddLiterals(const std::vector<uint32_t>& _Literals);
		void AddTypes(const std::vector<uint32_t>& _Types);

		const spv::Op& GetOpCode() const noexcept;
		bool GetUsed() const noexcept;
		bool GetTranslated() const noexcept;

		const uint32_t& GetResultType() const noexcept;
		const std::vector<SPIRVOperand>& GetOperands() const noexcept;
		std::vector<SPIRVOperand>& GetOperands() noexcept;

	private:
		spv::Op m_kOpCode = spv::OpNop;
		uint32_t m_uInstrId = HUNDEFINED32;
		uint32_t m_uResultId = HUNDEFINED32;
		std::vector<SPIRVOperand> m_Operands;
		uint32_t m_uResultTypeId = HUNDEFINED32;
		bool m_bUsed = true;
		bool m_bTranslated = false;
	};

    template<class ...Operands>
    inline SPIRVOperation::SPIRVOperation(const spv::Op _kOp, const uint32_t _uResultTypeId, Operands&& ..._Operands) :
        m_kOpCode(_kOp), m_uResultTypeId(_uResultTypeId), m_Operands({ std::forward<Operands>(_Operands)... })
    {
    }

	inline const spv::Op& SPIRVOperation::GetOpCode() const noexcept
	{
		return m_kOpCode;
	}

	inline bool SPIRVOperation::GetUsed() const noexcept
	{
		return m_bUsed;
	}

	inline bool SPIRVOperation::GetTranslated() const noexcept
	{
		return m_bTranslated;
	}

	inline const std::vector<SPIRVOperand>& SPIRVOperation::GetOperands() const noexcept
	{
		return m_Operands;
	}

	inline std::vector<SPIRVOperand>& SPIRVOperation::GetOperands() noexcept
	{
		return m_Operands;
	}

	inline const uint32_t& SPIRVOperation::GetResultType() const noexcept
	{
		return m_uResultTypeId;
	}
} // !Spear

#endif // !SPEAR_SPIRVOPERATION_H
