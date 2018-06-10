//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#include "SPIRVModule.h"
#include "SPIRVInstruction.h"
#include "HashUtils.h"
#include <fstream>

using namespace Spear;
//---------------------------------------------------------------------------------------------------
SPIRVModule::SPIRVModule(const SPIRVModule& _Other) :
	m_uBounds(_Other.m_uBounds),
	m_uGenerator(_Other.m_uGenerator),
	m_uSchema(_Other.m_uSchema),
	m_uSPVVersion(_Other.m_uSPVVersion),
	m_InstructionStream(_Other.m_InstructionStream),
	m_Extensions(_Other.m_Extensions),
	m_kMode(_Other.m_kMode),
	m_kModel(_Other.m_kModel),
	m_sEntryPoint(_Other.m_sEntryPoint),
	m_uHash(_Other.m_uHash),
	m_uSPVOperations(_Other.m_uSPVOperations),
	m_Variables(_Other.m_Variables)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVModule::SPIRVModule(const std::vector<uint32_t>& _Optimized, const SPIRVModule& _Other) :
	m_uBounds(_Other.m_uBounds),
	m_uGenerator(_Other.m_uGenerator),
	m_uSchema(_Other.m_uSchema),
	m_uSPVVersion(_Other.m_uSPVVersion),
	m_InstructionStream(_Optimized),
	m_Extensions(_Other.m_Extensions),
	m_kMode(_Other.m_kMode),
	m_kModel(_Other.m_kModel),
	m_sEntryPoint(_Other.m_sEntryPoint),
	m_uSPVOperations(_Other.m_uSPVOperations),
	m_Variables(_Other.m_Variables)
{
	m_uHash = 0u;

	for (const uint32_t& uWord : _Optimized)
	{
		m_uHash = hlx::AddHash(m_uHash, uWord);
	}
}
//---------------------------------------------------------------------------------------------------
SPIRVModule::SPIRVModule(const uint32_t _uBounds) noexcept :
	m_uBounds(_uBounds)
{
}
//---------------------------------------------------------------------------------------------------

SPIRVModule::~SPIRVModule()
{
}

//---------------------------------------------------------------------------------------------------
void SPIRVModule::Write(const std::vector<SPIRVInstruction>& _Instructions)
{
	m_InstructionStream.resize(0);
	m_uHash = 0u;

	// write header
	Put(spv::MagicNumber);
	Put(m_uSPVVersion);
	Put(uGenerator); // tracy
	Put(m_uBounds); // Bounds
	Put(uSchema);

	m_uSPVOperations = static_cast<uint32_t>(_Instructions.size());

	// write instructions
	for (const SPIRVInstruction& Instr : _Instructions)
	{
		Put(Instr);
	}
}

//---------------------------------------------------------------------------------------------------

bool SPIRVModule::Save(const std::string& _sFilePath) const
{
	std::ofstream File(_sFilePath, std::ios::out | std::ios::binary);

	if (File.is_open() == false)
		return false;

	File.write(reinterpret_cast<const char*>(m_InstructionStream.data()), m_InstructionStream.size() * sizeof(uint32_t));
	File.close();

	return true;
}
//---------------------------------------------------------------------------------------------------

void SPIRVModule::Put(const uint32_t& _uWord)
{
	m_uHash = hlx::AddHash(m_uHash, _uWord);
	m_InstructionStream.push_back(_uWord);
}
//---------------------------------------------------------------------------------------------------

void SPIRVModule::Put(const SPIRVInstruction& _Instr)
{
	// TODO: check if operation can be skipped (like OpNop etc)

	Put(_Instr.GetOpCode());

	const uint32_t& uTypeId(_Instr.GetTypeId());
	const uint32_t& uResultId(_Instr.GetResultId());

	if(uTypeId != SPIRVInstruction::kInvalidId)
		Put(uTypeId);

	if (uResultId != SPIRVInstruction::kInvalidId)
		Put(uResultId);

	for (const uint32_t& uOperand : _Instr.GetOperands())
	{
		Put(uOperand);
	}
}
//---------------------------------------------------------------------------------------------------
bool SPIRVModule::GetVariableByName(const std::string& _sName, VariableInfo & _OutVar)
{
	for (const VariableInfo& Var : m_Variables)
	{
		if (Var.sName == _sName)
		{
			_OutVar = Var;
			return true;
		}
	}

	return false;
}
//---------------------------------------------------------------------------------------------------

size_t VariableInfo::ComputeHash() const
{
	return 
		hlx::CombineHashes(Type.GetHash(),
		hlx::Hash(
			kStorageClass,
			uMemberOffset,
			uDescriptorSet,
			uBinding,
			uLocation,
			uSpecConstId,
			uInputAttachmentIndex,
			bTexSampled,
			bTexStored,
			bInstanceData));
}
//---------------------------------------------------------------------------------------------------
