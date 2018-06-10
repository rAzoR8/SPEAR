//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVINSTRUCTION_H
#define SPEAR_SPIRVINSTRUCTION_H

#include <vulkan\spirv.hpp>
#include <vector>

namespace Spear
{
	class SPIRVInstruction
	{
	public:
		static constexpr uint32_t kInvalidId = 0xffffffff;

		SPIRVInstruction(
			const spv::Op _kOp = spv::OpNop,
			const uint32_t _uTypeId = kInvalidId,
			const uint32_t _uResultId = kInvalidId,
			const std::vector<uint32_t>& _Operands = {}) noexcept;

		//SPIRVInstruction(const std::vector<uint32_t>& _Words);

		// raw instruction words to be decoded, returns number of consumed words, 0 if failed
		static uint32_t Decode(const std::vector<uint32_t>& _Words, const uint32_t _uIndex, SPIRVInstruction& _OutInstr);

		~SPIRVInstruction();

		uint32_t GetOpCode() const noexcept;
		const uint32_t GetTypeId() const noexcept;
		const uint32_t& GetResultId() const noexcept;
		const std::vector<uint32_t>& GetOperands() const noexcept;
		spv::Op GetOp() const noexcept;
		std::string GetString() const;

	private:
		spv::Op m_kOperation;

		uint32_t m_uTypeId = kInvalidId;
		uint32_t m_uResultId = kInvalidId;
		std::vector<uint32_t> m_Operands;

		// format:
		// OpCode u16 
		// WordCount u16
		// Id u32 (optional)
		// Result Id (optional)
		// Operands x u32 (WordCount-(1-3)) (optional)
	};

	inline const uint32_t SPIRVInstruction::GetTypeId() const noexcept {return m_uTypeId;}
	inline const uint32_t& SPIRVInstruction::GetResultId() const noexcept { return m_uResultId; }
	inline const std::vector<uint32_t>& SPIRVInstruction::GetOperands() const noexcept {return m_Operands;}
	inline spv::Op SPIRVInstruction::GetOp() const noexcept{return m_kOperation;}
}; // Spear

#endif // !SPEAR_SPIRVINSTRUCTION_H
