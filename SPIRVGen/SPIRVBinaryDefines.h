//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVBINARYDEFINES_H
#define SPEAR_SPIRVBINARYDEFINES_H

#include <string>
#include <unordered_map>
#include <vulkan\spirv.hpp>	
#include "Flag.h"

namespace Spear
{
	enum ESPVOpArgs
	{
		kSPVOpArgs_None = 0,
		kSPVOpArgs_TypeId = 1 << 0,
		kSPVOpArgs_ResultId = 1 << 1,
		kSPVOpArgs_TypeAndResultId = kSPVOpArgs_TypeId | kSPVOpArgs_ResultId,
		kSPVOpArgs_Unknown = 0xff
	};

	using TSPVArgFlag = hlx::Flag<ESPVOpArgs>;

	// dont use, unfinished
	inline static std::string GetOpCodeString(const spv::Op _kOp)
	{
		static const std::unordered_map<spv::Op, std::string> OpNames =
		{
			{ spv::OpNop, "OpNop" },
		{ spv::OpUndef, "OpUndef" },
		{ spv::OpSourceContinued, "OpSourceContinued" },
		{ spv::OpSource, "OpSource" },
		{ spv::OpSourceExtension, "OpSourceExtension" },
		{ spv::OpName, "OpName" },
		{ spv::OpMemberName, "OpMemberName" },
		{ spv::OpString, "OpString" },
		{ spv::OpLine, "OpLine" },
		{ spv::OpExtension, "OpExtension" },
		{ spv::OpExtInstImport, "OpExtInstImport" },
		{ spv::OpMemoryModel, "OpMemoryModel" },
		{ spv::OpEntryPoint, "OpEntryPoint" },
		{ spv::OpExecutionMode, "OpExecutionMode" },
		{ spv::OpCapability, "OpCapability" },
		{ spv::OpTypeVoid, "OpTypeVoid" },
		{ spv::OpTypeBool, "OpTypeBool" },
		{ spv::OpTypeInt, "OpTypeInt" },
		{ spv::OpTypeFloat, "OpTypeFloat" },
		{ spv::OpTypeVector, "OpTypeVector" },
		{ spv::OpTypeMatrix, "OpTypeMatrix" },
		{ spv::OpTypeImage, "OpTypeImage" },
		{ spv::OpTypeSampler, "OpTypeSampler" },
		{ spv::OpTypeSampledImage, "OpTypeSampledImage" },
		{ spv::OpTypeArray, "OpTypeArray" },
		{ spv::OpTypeRuntimeArray, "OpTypeRuntimeArray" },
		{ spv::OpTypeStruct, "OpTypeStruct" },
		{ spv::OpTypePointer, "OpTypePointer" },
		{ spv::OpTypeFunction, "OpTypeFunction" },
		{ spv::OpTypeEvent, "OpTypeEvent" },
		{ spv::OpTypeDeviceEvent, "OpTypeDeviceEvent" },
		{ spv::OpTypeReserveId, "OpTypeReserveId" },
		{ spv::OpTypeQueue, "OpTypeQueue" },
		{ spv::OpTypePipe, "OpTypePipe" },
		{ spv::OpTypeForwardPointer, "OpTypeForwardPointer" },
		{ spv::OpConstantTrue, "OpConstantTrue" },
		{ spv::OpConstantFalse, "OpConstantFalse" },
		{ spv::OpConstant, "OpConstant" },
		{ spv::OpConstantComposite, "OpConstantComposite" },
		{ spv::OpConstantSampler, "OpConstantSampler" },
		{ spv::OpConstantNull, "OpConstantNull" },
		{ spv::OpSpecConstantTrue, "OpSpecConstantTrue" },
		{ spv::OpSpecConstantFalse, "OpSpecConstantFalse" },
		{ spv::OpSpecConstant, "OpSpecConstant" },
		{ spv::OpSpecConstantComposite, "OpSpecConstantComposite" },
		{ spv::OpSpecConstantOp, "OpSpecConstantOp" },
		{ spv::OpFunction, "OpFunction" },
		{ spv::OpFunctionParameter, "OpFunctionParameter" },
		{ spv::OpFunctionEnd, "OpFunctionEnd" },
		{ spv::OpFunctionCall, "OpFunctionCall" },
		{ spv::OpVariable, "OpVariable" },
		{ spv::OpImageTexelPointer, "OpImageTexelPointer" },
		{ spv::OpLoad, "OpLoad" },
		{ spv::OpStore, "OpStore" },
		{ spv::OpCopyMemory, "OpCopyMemory" },
		{ spv::OpCopyMemorySized, "OpCopyMemorySized" },
		{ spv::OpAccessChain, "OpAccessChain" },
		{ spv::OpInBoundsAccessChain, "OpInBoundsAccessChain" },
		{ spv::OpPtrAccessChain, "OpPtrAccessChain" },
		{ spv::OpArrayLength, "OpArrayLength" },
		{ spv::OpGenericPtrMemSemantics, "OpGenericPtrMemSemantics" },
		{ spv::OpInBoundsPtrAccessChain, "OpInBoundsPtrAccessChain" },
		{ spv::OpDecorate, "OpDecorate" },
		{ spv::OpMemberDecorate, "OpMemberDecorate" },
		{ spv::OpDecorationGroup, "OpDecorationGroup" },
		{ spv::OpGroupDecorate, "OpGroupDecorate" },
		{ spv::OpGroupMemberDecorate, "OpGroupMemberDecorate" },
		{ spv::OpVectorExtractDynamic, "OpVectorExtractDynamic" },
		{ spv::OpVectorInsertDynamic, "OpVectorInsertDynamic" },
		{ spv::OpVectorShuffle, "OpVectorShuffle" },
		{ spv::OpCompositeConstruct, "OpCompositeConstruct" },
		{ spv::OpCompositeExtract, "OpCompositeExtract" },
		{ spv::OpCopyObject, "OpCopyObject" },
		{ spv::OpTranspose, "OpTranspose" },
		{ spv::OpSampledImage, "OpSampledImage" },
		{ spv::OpImageSampleImplicitLod, "OpImageSampleImplicitLod" },
		{ spv::OpImageSampleExplicitLod, "OpImageSampleExplicitLod" },
		{ spv::OpImageSampleDrefImplicitLod, "OpImageSampleDrefImplicitLod" },
		{ spv::OpImageSampleDrefExplicitLod, "OpImageSampleDrefExplicitLod" },
		{ spv::OpImageSampleProjImplicitLod, "OpImageSampleProjImplicitLod" },
		{ spv::OpImageSampleProjExplicitLod, "OpImageSampleProjExplicitLod" },
		{ spv::OpImageSampleProjDrefImplicitLod, "OpImageSampleProjDrefImplicitLod" },
		{ spv::OpImageSampleProjDrefExplicitLod, "OpImageSampleProjDrefExplicitLod" },
		{ spv::OpImageFetch, "OpImageFetch" },
		{ spv::OpImageGather, "OpImageGather" },
		{ spv::OpImageDrefGather, "OpImageDrefGather" },
		{ spv::OpImageRead, "OpImageRead" },
		{ spv::OpImageWrite, "OpImageWrite" },
		{ spv::OpImage, "OpImage" },
		{ spv::OpImageQueryFormat, "OpImageQueryFormat" },
		{ spv::OpImageQueryOrder, "OpImageQueryOrder" },
		{ spv::OpImageQuerySizeLod, "OpImageQuerySizeLod" },
		{ spv::OpImageQuerySize, "OpImageQuerySize" },
		{ spv::OpImageQueryLod, "OpImageQueryLod" },
		{ spv::OpImageQueryLevels, "OpImageQueryLevels" },
		{ spv::OpImageQuerySamples, "OpImageQuerySamples" }

		};

		auto it = OpNames.find(_kOp);
		return it != OpNames.end() ? it->second : "Unknown [" + std::to_string(_kOp) + "]";
	}

	// dont use, unfinished
	inline static ESPVOpArgs GetOpCodeArgs(const spv::Op _kOp)
	{
		static const std::unordered_map<spv::Op, ESPVOpArgs> OpArgs =
		{
			{ spv::OpNop, kSPVOpArgs_None },
		{ spv::OpUndef, kSPVOpArgs_TypeAndResultId },
		{ spv::OpSourceContinued, kSPVOpArgs_None },
		{ spv::OpSource, kSPVOpArgs_None },
		{ spv::OpSourceExtension, kSPVOpArgs_None },
		{ spv::OpName, kSPVOpArgs_None },
		{ spv::OpMemberName, kSPVOpArgs_TypeId },
		{ spv::OpString, kSPVOpArgs_ResultId },
		{ spv::OpLine, kSPVOpArgs_None },
		{ spv::OpExtension, kSPVOpArgs_None },
		{ spv::OpExtInstImport, kSPVOpArgs_ResultId },
		{ spv::OpExtInst, kSPVOpArgs_TypeAndResultId },
		{ spv::OpMemoryModel, kSPVOpArgs_None },
		{ spv::OpEntryPoint, kSPVOpArgs_None },
		{ spv::OpExecutionMode, kSPVOpArgs_None },
		{ spv::OpCapability, kSPVOpArgs_None },
		{ spv::OpTypeVoid, kSPVOpArgs_ResultId },
		{ spv::OpTypeVoid, kSPVOpArgs_ResultId },
		{ spv::OpTypeBool, kSPVOpArgs_ResultId },
		{ spv::OpTypeInt, kSPVOpArgs_ResultId },
		{ spv::OpTypeFloat, kSPVOpArgs_ResultId },
		{ spv::OpTypeVector, kSPVOpArgs_ResultId },
		{ spv::OpTypeMatrix, kSPVOpArgs_ResultId },
		{ spv::OpTypeImage, kSPVOpArgs_TypeAndResultId },
		{ spv::OpTypeSampler, kSPVOpArgs_ResultId },
		{ spv::OpTypeSampledImage, kSPVOpArgs_TypeAndResultId },
		{ spv::OpTypeArray, kSPVOpArgs_TypeAndResultId },
		{ spv::OpTypeRuntimeArray, kSPVOpArgs_TypeAndResultId },
		{ spv::OpTypeStruct, kSPVOpArgs_ResultId },
		{ spv::OpTypeOpaque, kSPVOpArgs_ResultId },
		{ spv::OpTypeOpaque, kSPVOpArgs_ResultId },
		{ spv::OpTypePointer, kSPVOpArgs_ResultId },
		{ spv::OpTypeFunction, kSPVOpArgs_TypeAndResultId },
		{ spv::OpTypeEvent, kSPVOpArgs_ResultId },
		{ spv::OpTypeDeviceEvent, kSPVOpArgs_ResultId },
		{ spv::OpTypeReserveId, kSPVOpArgs_ResultId },
		{ spv::OpTypeQueue, kSPVOpArgs_ResultId },
		{ spv::OpTypePipe, kSPVOpArgs_ResultId },
		{ spv::OpTypeForwardPointer, kSPVOpArgs_TypeId },
		{ spv::OpConstantTrue, kSPVOpArgs_ResultId },

		};

		auto it = OpArgs.find(_kOp);
		return it != OpArgs.end() ? it->second : kSPVOpArgs_Unknown;
	}

	inline static std::string LiteralToString(const uint32_t _uLiteral)
	{
		std::string sLiteralStr;
		const char* c = reinterpret_cast<const char*>(&_uLiteral);
		for (uint32_t i = 0; i < 4 && *c != 0; i++, c++)
		{
			sLiteralStr += *c;
		}

		return sLiteralStr;
	}

	inline static bool CreatesResultId(const spv::Op _kOp)
	{
		switch (_kOp)
		{
		// instructions that don't create a result id (incomplete list)
		case spv::OpNop:
		case spv::OpSourceContinued:
		case spv::OpSource:
		case spv::OpSourceExtension:
		case spv::OpName:
		case spv::OpMemberName:
		case spv::OpLine:
		case spv::OpNoLine:
		case spv::OpModuleProcessed:
		case spv::OpDecorate:
		case spv::OpMemberDecorate:
		case spv::OpGroupDecorate:
		case spv::OpGroupMemberDecorate:
		//case spv::OpDecrorateId: // spv v1.2
		case spv::OpExtension:
		case spv::OpMemoryModel:
		case spv::OpEntryPoint:
		case spv::OpExecutionMode:
		case spv::OpCapability:
		//case spv::OpExecutionModeId: // spv v1.2
		case spv::OpTypeForwardPointer:
		case spv::OpStore:
		case spv::OpCopyMemory:
		case spv::OpCopyMemorySized:
		case spv::OpFunctionEnd:
		case spv::OpLoopMerge:
		case spv::OpSelectionMerge:
		case spv::OpBranch:
		case spv::OpBranchConditional:
		case spv::OpSwitch:
		case spv::OpKill:
		case spv::OpReturn:
		case spv::OpReturnValue:
		case spv::OpUnreachable:
		case spv::OpLifetimeStart:
		case spv::OpLifetimeStop:
		case spv::OpEmitVertex:
		case spv::OpEndPrimitive:
		case spv::OpEmitStreamVertex:
		case spv::OpEndStreamPrimitive:
		case spv::OpControlBarrier:
		case spv::OpMemoryBarrier:
		case spv::OpMemoryNamedBarrier:
		case spv::OpGroupWaitEvents:
		case spv::OpRetainEvent:
		case spv::OpReleaseEvent:
		case spv::OpSetUserEventStatus:
		case spv::OpCaptureEventProfilingInfo:
		case spv::OpGroupCommitReadPipe:
		case spv::OpGroupCommitWritePipe:
			return false;
			break;
		default:
			return true;
		}
	}
	
} // Spear

#endif // !SPEAR_SPIRVBINARYDEFINES_H
