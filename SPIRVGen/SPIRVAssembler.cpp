//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#include "SPIRVAssembler.h"
#include "SPIRVConstant.h"
#include "SPIRVProgram.h"
#include "SPIRVVariable.h"
#include "SPIRVBinaryDefines.h"
#include "spirv-tools\optimizer.hpp"

using namespace Spear;

//---------------------------------------------------------------------------------------------------

SPIRVModule SPIRVAssembler::ExternalOptimize(const SPIRVModule& _Module, const OptimizationSettings& _Settings)
{
	if (_Settings.kPasses.None())
		return _Module;

	spvtools::Optimizer Optimizer(SPV_ENV_VULKAN_1_0);

	if (_Settings.kPasses.CheckFlag(kOptimizationPassFlag_AllPerformance))
	{
		Optimizer.RegisterPerformancePasses();
	}

	if (_Settings.kPasses.CheckFlag(kOptimizationPassFlag_AllSize))
	{
		Optimizer.RegisterSizePasses();
	}

	std::vector<uint32_t> Optimized;
	if (Optimizer.Run(_Module.GetCode().data(), _Module.GetCode().size(), &Optimized))
	{		
		return SPIRVModule(Optimized, _Module);
	}
	else
	{
		return _Module;
	}
}
//---------------------------------------------------------------------------------------------------


SPIRVAssembler::SPIRVAssembler() noexcept
{
	m_Operations.reserve(64*1024u);
}
//---------------------------------------------------------------------------------------------------

SPIRVAssembler::~SPIRVAssembler()
{
}
//---------------------------------------------------------------------------------------------------

SPIRVModule SPIRVAssembler::Assemble()
{
	Resolve();

	m_Operations.clear();
	m_uInstrId = 0u;
	m_uScopeID = 0u;
	m_uScopeLevel = 0u;
	m_TypeIds.clear();
	m_ConstantIds.clear();
	m_Bindings.clear();

	SPIRVModule Module(m_uResultId + 1u);
	Module.SetEntryPoint(m_sEntryPoint);
	Module.SetExecutionMode(m_kMode);
	Module.SetExecutionModel(m_kModel);
	Module.SetExtensions(m_Extensions);
	Module.SetCapabilities(m_Capabilities);

	// copy accumulated variable info
	for (auto& kv : m_UsedVariables)
	{
		VariableInfo& var = kv.second;
		if (var.kStorageClass != spv::StorageClassFunction)
		{
			var.uHash = var.ComputeHash();
			var.uStageFlags = 1 << m_kModel;
			Module.AddVariable(var);
		}
	}
	
	Module.Write(m_Instructions);

	m_Mutex.unlock();

	return ExternalOptimize(Module, m_OptSettings);
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::GetExtensionId(const std::string& _sExt)
{
	auto it = m_ExtensionIds.find(_sExt);
	if(it != m_ExtensionIds.end())
	{
		return it->second;
	}

	return HUNDEFINED32;
}
//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::Init(const std::unique_ptr<SPIRVProgram<true>>& _pProgram)
{
	m_kMode = _pProgram->GetExecutionMode();
	m_kModel = _pProgram->GetExecutionModel();
	m_Extensions = _pProgram->GetExtensions();
	m_sEntryPoint = _pProgram->GetEntryPoint();
	m_Capabilities = _pProgram->GetCapabilities();

	m_uResultId = 1u;
	m_pOpEntryPoint = nullptr;

	m_Instructions.clear();
	m_UsedVariables.clear();
	m_PreambleOpIds.clear();

	//https://www.khronos.org/registry/spir-v/specs/1.2/SPIRV.pdf#subsection.2.4

	for (const spv::Capability& Cap : m_Capabilities)
	{
		AddPreambleId(AddOperation(SPIRVOperation(spv::OpCapability, SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(Cap)))));
	}

	// OpExtension (unused)

	// OpExtInstImport
	for (const std::string& sExt : m_Extensions)
	{
		uint32_t uId = AddOperation(SPIRVOperation(spv::OpExtInstImport, MakeLiteralString(sExt)));
		AddPreambleId(uId);
		m_ExtensionIds[sExt] = uId;
	}

	//OpMemoryModel
	AddPreambleId(AddOperation(SPIRVOperation(spv::OpMemoryModel, { SPIRVOperand::Literal(spv::AddressingModelLogical), SPIRVOperand::Literal(spv::MemoryModelGLSL450) })));

	// OpEntryPoint
	// Op1: Execution model
	AddPreambleId(AddOperation(SPIRVOperation(spv::OpEntryPoint, SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(m_kModel))), &m_pOpEntryPoint));

	if (m_kMode < spv::ExecutionModeMax)
	{
		AddPreambleId(AddOperation(SPIRVOperation(spv::OpExecutionMode), &m_pOpExeutionMode));
	}

	// add types for entry point function
	const uint32_t uFunctionTypeId = AddType(SPIRVType(spv::OpTypeFunction, SPIRVType::Void()));

	const uint32_t uFuncId = AddOperation(SPIRVOperation(
		spv::OpFunction,
		AddType(SPIRVType::Void()), // result type
		{
			SPIRVOperand(kOperandType_Literal, static_cast<uint32_t>(spv::FunctionControlMaskNone)), // function control
			SPIRVOperand(kOperandType_Intermediate, uFunctionTypeId), // function type
		}));

	m_uFunctionPreambleIndex = static_cast<uint32_t>(m_PreambleOpIds.size());
	AddPreambleId(uFuncId);

	if (m_kMode < spv::ExecutionModeMax)
	{
		m_pOpExeutionMode->AddIntermediate(uFuncId);
		m_pOpExeutionMode->AddLiteral(static_cast<uint32_t>(m_kMode));
	}

	// Op2: entry point id must be the result id of an OpFunction instruction
	m_pOpEntryPoint->AddIntermediate(uFuncId);
	// Op3: Name is a name string for the entry point.A module cannot have two OpEntryPoint
	// instructions with the same Execution Model and the same Name	string.
	m_pOpEntryPoint->AddLiterals(MakeLiteralString(m_sEntryPoint));

	//OpFunctionParameter not needed since OpEntryPoint resolves them
	AddPreambleId(AddOperation(SPIRVOperation(spv::OpLabel)));	
}
//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::FlagUnused()
{
	uint32_t uUnused = 0u;

	const auto Consumed = [](const uint32_t& uId, const SPIRVOperation& _ConsumeOp) -> bool
	{
		if (_ConsumeOp.GetResultType() == uId)
		{
			return true;
		}

		for (const SPIRVOperand& Operand : _ConsumeOp.GetOperands())
		{
			if (Operand.kType == kOperandType_Intermediate && Operand.uId == uId)
			{
				return true;
			}
		}

		return false;
	};

	const size_t uOpCount = m_Operations.size();

	const auto Flag = [&](SPIRVOperation& _InOp)
	{
		if (_InOp.m_bUsed == false)
			return;

		if (CreatesResultId(_InOp.GetOpCode()) == false || _InOp.GetOpCode() == spv::OpLabel)
		{
			_InOp.m_bUsed = true;
			return;
		}

		_InOp.m_bUsed = false;

		// find any instruction that consumes this one
		for (uint32_t i = 0u; i < uOpCount && _InOp.m_bUsed == false; i++)
		{
			if (i != _InOp.m_uInstrId)
			{
				_InOp.m_bUsed = Consumed(_InOp.m_uInstrId, m_Operations[i]);
			}
		}

		if (_InOp.m_bUsed == false)
		{
			++uUnused;
			//HLOGD("Removed instruction %u %s", _InOp.m_uInstrId, WCSTR(GetOpCodeString(_InOp.GetOpCode())));
		}
	};

	uint32_t uPrevCount;
	do
	{
		uPrevCount = uUnused;
		uUnused = 0u;

		std::for_each(m_Operations.begin(), m_Operations.end(), Flag);
	} while (uUnused > uPrevCount);

	HLOG("Removed %u unused operations from %u total", uPrevCount, m_uInstrId);
}

//---------------------------------------------------------------------------------------------------
spv::StorageClass SPIRVAssembler::GetStorageClass(const SPIRVOperation& _Op) const
{
	const std::vector<SPIRVOperand>& Operands(_Op.GetOperands());
	switch (_Op.GetOpCode())
	{
	case spv::OpVariable:
	{
		HASSERT(Operands.size() > 0u, "Invalid number of OpVariable operands");

		const SPIRVOperand& ClassOp = Operands.front();
		HASSERT(ClassOp.uId != HUNDEFINED32 && ClassOp.kType == kOperandType_Literal, "Invalid OpVariable operand storage class [literal]");

		return static_cast<spv::StorageClass>(ClassOp.uId);
	}
	case spv::OpAccessChain:
	{
		HASSERT(Operands.size() > 0u, "Invalid number of OpAccessChain operands");
		const SPIRVOperand& BaseIdOp = Operands.front();
		HASSERT(BaseIdOp.uId != HUNDEFINED32 && BaseIdOp.kType == kOperandType_Intermediate, "Invalid OpAccessChain operand base id [variable]");
		HASSERT(BaseIdOp.uId < m_Operations.size(), "Invalid base id");

		return GetStorageClass(m_Operations[BaseIdOp.uId]);
	}
	default:
		HFATAL("Unsupported operation for variable");
		return spv::StorageClassMax;
	}
}
//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::AddPreambleId(const uint32_t& _uId)
{
	m_PreambleOpIds.push_back(_uId);
}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::AddType(const SPIRVType& _Type)
{
	const size_t uHash = _Type.GetHash();

	auto it = m_TypeIds.find(uHash);
	if (it != m_TypeIds.end())
	{
		// type exists
		return it->second;
	}

	const spv::Op kType = _Type.GetType();

	std::vector<uint32_t> SubTypes;
	SPIRVOperation OpType(kType);

	for (const SPIRVType& Type : _Type.GetSubTypes())
	{
		SubTypes.push_back(AddType(Type));
	}

	// create operands
	switch (kType)
	{
	case spv::OpTypeVoid:
	case spv::OpTypeBool:
	case spv::OpTypeSampler:
		break; // nothing to do
	case spv::OpTypeInt:
		OpType.AddLiteral(_Type.GetDimension()); // bitwidth
		OpType.AddLiteral(uint32_t(_Type.GetSign())); // sign bit
		break;
	case spv::OpTypeFloat:
		OpType.AddLiteral(_Type.GetDimension()); // bitwidth
		break;
	case spv::OpTypeVector:
		HASSERT(SubTypes.size() == 1u, "Invalid number of vector component types");
		OpType.AddIntermediate(SubTypes.front()); // component type
		OpType.AddLiteral(_Type.GetDimension()); // component count
		break;
	case spv::OpTypeMatrix:
		HASSERT(SubTypes.size() == 1u, "Invalid number of matrix component types");
		OpType.AddIntermediate(SubTypes.front()); // column type
		OpType.AddLiteral(_Type.GetDimension()); // column count (row type)
		break;
	case spv::OpTypeStruct:
		// If an operand is not yet defined, it must be defined by an OpTypePointer,
		// where the type pointed to is an OpTypeStruct (fwahlster: not sure if we need that, ignore it for now)
		OpType.AddTypes(SubTypes);
		break;
	case spv::OpTypeArray:
		HASSERT(SubTypes.size() == 1u, "Invalid number of array component types");
		HASSERT(_Type.GetDimension() > 0u, "Invalid array length");

		OpType.AddIntermediate(SubTypes.front()); // column type
		//Length must come from a constant instruction of an integer - type scalar whose value is at least 1.
		OpType.AddIntermediate(AddConstant(SPIRVConstant::Make(_Type.GetDimension()))); // length
		break;
	case spv::OpTypeFunction:
		HASSERT(SubTypes.size() > 0u, "Invalid number of return type and parameters");
		OpType.AddTypes(SubTypes);
		break;
	case spv::OpTypePointer:
		// dimension is used as storage class
		HASSERT(SubTypes.size() == 1u, "Pointer can only have one subtype");
		OpType.AddLiteral(_Type.GetDimension()); // storage class
		OpType.AddIntermediate(SubTypes.front()); // type
		break;
	case spv::OpTypeImage:
		HASSERT(SubTypes.size() == 1u, "Invalid number of sampled component types");
		OpType.AddIntermediate(SubTypes.front()); // sampled type
		OpType.AddLiteral(_Type.GetDimension()); // spv::Dim
		OpType.AddLiteral(_Type.GetTexDepthType());
		OpType.AddLiteral(uint32_t(_Type.GetArray()));
		OpType.AddLiteral(uint32_t(_Type.GetMultiSampled()));
		OpType.AddLiteral(_Type.GetTexSamplerAccess());
		OpType.AddLiteral(static_cast<uint32_t>(spv::ImageFormatUnknown)); // any format
		// If Dim is SubpassData, Sampled must be 2, Image Format must be Unknown, and the Execution Model must be Fragment.
		break;
	case spv::OpTypeSampledImage:
		HASSERT(SubTypes.size() == 1u, "Invalid number of image types");
		HASSERT(_Type.GetSubTypes().front().GetType() == spv::OpTypeImage, "Invalid image type");
		OpType.AddIntermediate(SubTypes.front()); // image type
		break;
	default:
		HFATAL("Type %d not implemented", kType);
		break;
	}

	const uint32_t uInstrId = AddOperation(std::move(OpType));
	m_TypeIds.insert({ uHash, uInstrId });

	return uInstrId;
}

//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::AddConstant(const SPIRVConstant& _Constant)
{
	const size_t uHash = _Constant.GetHash();

	auto it = m_ConstantIds.find(uHash);
	if (it != m_ConstantIds.end())
	{
		// constant exists
		return it->second;
	}

	// resolve type first to enforce result id ordering
	const SPIRVType& CompositeType(_Constant.GetCompositeType());
	const spv::Op kType = _Constant.GetType();
	SPIRVOperation OpConstant(kType, AddType(CompositeType));

	switch (kType)
	{
		// nothing to do here:
	case spv::OpConstantNull:
		break;
		// validate base type to be boolean
	case spv::OpConstantTrue:
	case spv::OpConstantFalse:
	case spv::OpSpecConstantTrue:
	case spv::OpSpecConstantFalse:
		HASSERT(CompositeType.GetType() == spv::OpTypeBool, "Invalid constant composite type");
		break;
		// copy literals as operands
	case spv::OpConstant:
	case spv::OpSpecConstant:
		OpConstant.AddLiterals(_Constant.GetLiterals());
		break;
	case spv::OpConstantComposite:
	case spv::OpSpecConstantComposite:
		for (const SPIRVConstant& Component : _Constant.GetComponents())
		{
			OpConstant.AddIntermediate(AddConstant(Component));
		}
		break;
		//case spv::OpSpecConstantOp:
		//case spv::OpConstantSampler:
	default:
		HFATAL("Constant type not implemented");
		break;
	}

	uint32_t uInstrId = AddOperation(std::move(OpConstant));
	m_ConstantIds.insert({ uHash, uInstrId });

	return uInstrId;
}
//---------------------------------------------------------------------------------------------------
void SPIRVAssembler::Resolve()
{
	HASSERT(m_Operations.size() > 3, "Insufficient operations");

	// check if op is actually used
	const auto TranslateOp = [this](SPIRVOperation& _Op)
	{
		if (_Op.GetUsed() && _Op.GetTranslated() == false)
		{
			AddInstruction(Translate(_Op));
		}
	};

	// close function body opend in init
	AddOperation(SPIRVOperation(spv::OpReturn));
	AddOperation(SPIRVOperation(spv::OpFunctionEnd));

	// cleanup unused ops
	if (m_bRemoveUnused)
	{
		FlagUnused(); // sets m_bUsed if consume by any other inst
	}

	// find input / output vars
	ForEachOp([this](SPIRVOperation& Op)
	{
		if (Op.GetUsed())
		{
			const spv::StorageClass kClass = GetStorageClass(Op);
			if (kClass == spv::StorageClassInput || kClass == spv::StorageClassOutput)
			{
				m_pOpEntryPoint->AddIntermediate(Op.m_uInstrId);
			}
		}
	}, is_var_op);	

	// assing types & constants
	ForEachOp([this](SPIRVOperation& Op)
	{
		AssignId(Op);
	}, is_type_or_const_op);

	// assing decorates
	ForEachOp([this](SPIRVOperation& Op)
	{
		AssignId(Op);
	}, is_decorate_op);

	// assign unresolved operation ids
	ForEachOpEx([this](SPIRVOperation& Op)
	{
		AssignId(Op);
	}, [](const SPIRVOperation& Op) {return Op.m_uResultId == HUNDEFINED32; });

	// translate header up until OpFuntion (which is followed by OpLable)
	size_t p = 0u;
	for (;p < m_uFunctionPreambleIndex; ++p)
	{
		TranslateOp(m_Operations[m_PreambleOpIds[p]]); 
	}

	// translate names
	ForEachOp([TranslateOp](SPIRVOperation& Op)
	{
		TranslateOp(Op);
	}, is_name_op);

	// translate decorates
	ForEachOp([TranslateOp](SPIRVOperation& Op)
	{
		TranslateOp(Op);
	}, is_decorate_op);

	// translate types && constants
	ForEachOp([TranslateOp](SPIRVOperation& Op)
	{
		TranslateOp(Op);
	}, is_type_or_const_op);

	// translate class member variables
	ForEachOpEx([TranslateOp](SPIRVOperation& Op)
	{
		TranslateOp(Op);
	}, [this](const SPIRVOperation& Op) {return Op.GetOpCode() == spv::OpVariable && GetStorageClass(Op) != spv::StorageClassFunction; });

	// translate rest of the preamble
	for (; p < m_PreambleOpIds.size(); ++p)
	{
		TranslateOp(m_Operations[m_PreambleOpIds[p]]);
	}

	// translate function variables, this resolves the problem that variables can not be declared in branch blocks
	ForEachOpEx([TranslateOp](SPIRVOperation& Op)
	{
		TranslateOp(Op);
	}, [this](const SPIRVOperation& Op) {return Op.GetOpCode() == spv::OpVariable && GetStorageClass(Op) == spv::StorageClassFunction; });

	// tranlate rest of the program
	for (SPIRVOperation& Op : m_Operations)
	{
		TranslateOp(Op);
	}
}
//---------------------------------------------------------------------------------------------------

//uint32_t SPIRVAssembler::AddOperation(const SPIRVOperation& _Instr, SPIRVOperation** _pOutInstr)
//{
//	m_Operations.push_back(_Instr);
//	m_Operations.back().m_uInstrId = m_uInstrId;
//
//	if (_pOutInstr != nullptr)
//	{
//		*_pOutInstr = &m_Operations.back();
//	}
//
//	//HLOGD("%s", WCSTR(_Instr.GetString()));
//
//	return m_uInstrId++;
//}
//---------------------------------------------------------------------------------------------------

uint32_t SPIRVAssembler::AddOperation(SPIRVOperation&& _Instr, SPIRVOperation ** _pOutInstr)
{
    m_Operations.emplace_back(std::move(_Instr)).m_uInstrId = m_uInstrId;

    if (_pOutInstr != nullptr)
    {
        *_pOutInstr = &m_Operations.back();
    }

    return m_uInstrId++;
}

//---------------------------------------------------------------------------------------------------

void SPIRVAssembler::AddVariableInfo(const var_decoration<true>& _Var)
{
	auto it = m_UsedVariables.find(_Var.uVarId);

	if (it == m_UsedVariables.end())
	{
		it = m_UsedVariables.insert({ _Var.uVarId, {} }).first;
	}

	VariableInfo& Var(it->second);

	Var.uVarId = _Var.uVarId;
	Var.Type = _Var.Type;
	Var.kStorageClass = _Var.kStorageClass;
	Var.uMemberOffset = _Var.uMemberOffset;
	Var.uBinding = _Var.uBinding;
	Var.uDescriptorSet = _Var.uDescriptorSet;
	Var.uLocation = _Var.uLocation;
	Var.sName = _Var.sName;
	Var.uSpecConstId = _Var.uSpecConstId;
	Var.bTexSampled = _Var.bTexSampled;
	Var.bTexStored = _Var.bTexStored;
	Var.uInputAttachmentIndex = _Var.uInputAttachmentIndex;
	Var.bInstanceData = _Var.bInstanceData;
	Var.bBuiltIn = _Var.bBuiltIn;
	//Var.Decorations.insert(Var.Decorations.end(), _Var.Decorations.begin(), _Var.Decorations.end());
}

//---------------------------------------------------------------------------------------------------
SPIRVInstruction SPIRVAssembler::Translate(SPIRVOperation& _Op)
{
	HASSERT(_Op.m_bTranslated == false, "Operation has already been translated");

	std::vector<uint32_t> Operands;
	uint32_t uTypeId = SPIRVInstruction::kInvalidId;

	const auto ResolveId = [&](uint32_t id) -> uint32_t
	{
		HASSERT(id < m_Operations.size(), "Invalid operand Id");
		const uint32_t uResolvedId = m_Operations[id].m_uResultId;
		HASSERT(uResolvedId != SPIRVInstruction::kInvalidId, "Unresolved id");
		return uResolvedId;
	};

	if (_Op.GetResultType() != HUNDEFINED32)
	{
		uTypeId = ResolveId(_Op.GetResultType());
	}

	for (const SPIRVOperand& Operand : _Op.GetOperands())
	{
		switch (Operand.kType)
		{
		case kOperandType_Intermediate:
			Operands.push_back(ResolveId(Operand.uId));
			break;
		case kOperandType_Literal:
			Operands.push_back(Operand.uId);
			break;
		default:
			HFATAL("Unsupported operand type");
			break;
		}
	}
	
	_Op.m_bTranslated = true;
	return SPIRVInstruction(_Op.GetOpCode(), uTypeId, _Op.m_uResultId, Operands);
}
//---------------------------------------------------------------------------------------------------
void SPIRVAssembler::AddInstruction(const SPIRVInstruction& _Instr)
{
	m_Instructions.push_back(_Instr);
}
//---------------------------------------------------------------------------------------------------
void SPIRVAssembler::AssignId(SPIRVOperation& _Op)
{
	HASSERT(_Op.m_uResultId == SPIRVInstruction::kInvalidId, "Instruction already has a result id!");

	uint32_t uResultId = SPIRVInstruction::kInvalidId;

	if (_Op.m_bUsed) // dont resolve unused ops
	{
		if (CreatesResultId(_Op.GetOpCode()))
		{
			uResultId = m_uResultId++;
		}
	}

	_Op.m_uResultId = uResultId;
}

//---------------------------------------------------------------------------------------------------
