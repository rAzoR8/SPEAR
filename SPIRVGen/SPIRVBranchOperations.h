//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVBRANCHNODE_H
#define SPEAR_SPIRVBRANCHNODE_H

#include "SPIRVAssembler.h"

namespace Spear
{
#pragma region If
	template <bool Assemble>
	struct BranchNodeBase{};

	template <>
	struct BranchNodeBase<false>	
	{
		bool bCondition = false;
	};

	template <>
	struct BranchNodeBase<true>
	{
		SPIRVOperation* pThenBranch = nullptr;
		SPIRVOperation* pSelectionMerge = nullptr;
		SPIRVOperation* pBranchConditional = nullptr;
	};

	template <bool Assemble>
	struct BranchNode : public BranchNodeBase<Assemble>
	{
		template <class LambdaFunc>
		void ElseNode(const LambdaFunc& _Func);
	};

	template<bool Assemble, class LambdaFunc, spv::StorageClass Class>
	inline BranchNode<Assemble> IfNode(const var_t<bool, Assemble, Class>& _Cond, const LambdaFunc& _Func, const spv::SelectionControlMask _kMask = spv::SelectionControlMaskNone)
	{
		BranchNode<Assemble> Node;

		if constexpr(Assemble)
		{
			_Cond.Load();

			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpSelectionMerge,
				{
					SPIRVOperand(kOperandType_Intermediate, HUNDEFINED32), // merge id
					SPIRVOperand(kOperandType_Literal, (const uint32_t)_kMask) // selection class
				}), &Node.pSelectionMerge);

			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranchConditional, SPIRVOperand(kOperandType_Intermediate, _Cond.uResultId)), &Node.pBranchConditional);
		}
		else
		{
			Node.bCondition = _Cond.Value;
		}

		if (_Cond.Value || Assemble)
		{
			if constexpr(Assemble)
			{
				Node.pBranchConditional->AddIntermediate(GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel))); // add true label
			}

			//GlobalAssembler.ForceNextLoads();
			GlobalAssembler.EnterScope();
			_Func();
			GlobalAssembler.LeaveScope();
			//GlobalAssembler.ForceNextLoads(false);

			if constexpr(Assemble)
			{
				GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &Node.pThenBranch); // end of then block

				const uint32_t uFalseLableId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
				Node.pThenBranch->AddIntermediate(uFalseLableId);

				std::vector<SPIRVOperand>& Operands = Node.pSelectionMerge->GetOperands();
				HASSERT(Operands.size() == 2u, "Invalid number of operands for selection merge");
				Operands.front().uId = uFalseLableId; // use false label as merge label

				Node.pBranchConditional->AddIntermediate(uFalseLableId);
			}
		}

		return Node;
	}

	//---------------------------------------------------------------------------------------------------
	
	template<bool Assemble>
	template<class LambdaFunc>
	inline void BranchNode<Assemble>::ElseNode(const LambdaFunc& _Func)
	{
		if constexpr (Assemble)
		{
			GlobalAssembler.EnterScope();
			_Func();
			GlobalAssembler.LeaveScope();

			HASSERT(pThenBranch != nullptr && pSelectionMerge != nullptr, "Invalid branch node");
			
			// end of then block
			SPIRVOperation* pElseBranch = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pElseBranch);

			// selection merge
			std::vector<SPIRVOperand>& SelectionOperands = pSelectionMerge->GetOperands();
			HASSERT(SelectionOperands.size() == 2u, "Invalid number of operands for selection merge");
			const uint32_t uMergeId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			SelectionOperands.front().uId = uMergeId;

			// then branch update
			std::vector<SPIRVOperand>& ThenOperands = pThenBranch->GetOperands();
			HASSERT(ThenOperands.size() == 1u, "Invalid number of operands for then branch");
			ThenOperands.front().uId = uMergeId;

			// end of else block
			pElseBranch->AddOperand(SPIRVOperand(kOperandType_Intermediate, uMergeId));
		} 
		else
		{
			if (bCondition == false) // we are in the not condition branch
			{
				_Func();
			}
		}
	}
	//---------------------------------------------------------------------------------------------------

#pragma endregion

	//---------------------------------------------------------------------------------------------------

	template <class CondFunc, class LoopBody, class VarT = std::invoke_result_t<CondFunc>>  // CondFunc needs to return a var_t<bool>
	inline void WhileFunc(const CondFunc& _CondFunc, const LoopBody& _LoopBody, const spv::LoopControlMask _kLoopControl = spv::LoopControlMaskNone)
	{
		static_assert(is_var<VarT>, "Condition function must return a var_t type SPIR-V Variable");

		if constexpr(VarT::AssembleMode == false) //Assemble == false
		{
			while (_CondFunc().Value)
			{
				_LoopBody();
			}
		}
		else
		{
			// merge branch label
			SPIRVOperation* pOpBranch = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch); // close previous block
			const uint32_t uLoopMergeId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uLoopMergeId);

			// loop merge
			SPIRVOperation* pOpLoopMerge = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLoopMerge), &pOpLoopMerge);

			// condition branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uConditionLabelId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uConditionLabelId);

			// tranlate condition var
			GlobalAssembler.EnterScope();
			const auto& CondVar = _CondFunc();
			GlobalAssembler.LeaveScope();

			// branch conditional %cond %loopbody %exit
			SPIRVOperation* pOpBranchCond = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranchConditional), &pOpBranchCond);
			const uint32_t uLoopBodyId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranchCond->AddIntermediate(CondVar.Load());
			pOpBranchCond->AddIntermediate(uLoopBodyId);

			GlobalAssembler.EnterScope();
			_LoopBody();
			GlobalAssembler.LeaveScope();

			// close block
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uBlockExit = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uBlockExit);

			// exit branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uExitId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uLoopMergeId);

			pOpLoopMerge->AddIntermediate(uExitId); // merge block
			pOpLoopMerge->AddIntermediate(uBlockExit); // continue
			pOpLoopMerge->AddLiteral((uint32_t)_kLoopControl);

			pOpBranchCond->AddIntermediate(uExitId); // structured merge

			//GlobalAssembler.ForceNextLoads(false);
		}
	}
	//---------------------------------------------------------------------------------------------------

	template<class CondFunc, class IncFunc, class LoopBody, class VarT = std::invoke_result_t<CondFunc>>  // CondFunc needs to return a var_t<bool>
	inline void ForFunc(const CondFunc& _CondFunc, const IncFunc& _IncFunc, const LoopBody& _LoopBody, const spv::LoopControlMask _kLoopControl = spv::LoopControlMaskNone)
	{
		static_assert(is_var<VarT>, "Condition function must return a var_t type SPIR-V Variable");

		if constexpr(VarT::AssembleMode == false)
		{
			for (; _CondFunc().Value; _IncFunc())
			{
				_LoopBody();
			}
		}
		else
		{
			// branch %merge
			// label %merge
			// loopmerge
			// branch %cond
			// label %cond
			// Condition Code
			// branch_conditional
			// label %loopbody
			// LoopBody code
			// branch %increment
			// label %increment
			// Increment Code
			// branch %exit
			// label %exit

			// merge branch label
			SPIRVOperation* pOpBranch = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch); // close previous block
			const uint32_t uLoopMergeId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uLoopMergeId);

			// loop merge
			SPIRVOperation* pOpLoopMerge = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLoopMerge), &pOpLoopMerge);

			// condition branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uConditionLabelId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uConditionLabelId);

			//GlobalAssembler.ForceNextLoads();

			// tranlate condition var
			GlobalAssembler.EnterScope();
			const auto& CondVar = _CondFunc();
			GlobalAssembler.LeaveScope();

			// branch conditional %cond %loopbody %exit
			SPIRVOperation* pOpBranchCond = nullptr;
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranchConditional), &pOpBranchCond);
			const uint32_t uLoopBodyId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranchCond->AddIntermediate(CondVar.Load());
			pOpBranchCond->AddIntermediate(uLoopBodyId);

			GlobalAssembler.EnterScope();
			_LoopBody();
			GlobalAssembler.LeaveScope();

			// inrement branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uIncrementId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uIncrementId);

			GlobalAssembler.EnterScope();
			_IncFunc();
			GlobalAssembler.LeaveScope();

			// exit branch label
			GlobalAssembler.AddOperation(SPIRVOperation(spv::OpBranch), &pOpBranch);
			const uint32_t uExitId = GlobalAssembler.AddOperation(SPIRVOperation(spv::OpLabel));
			pOpBranch->AddIntermediate(uLoopMergeId);

			pOpLoopMerge->AddIntermediate(uExitId);
			pOpLoopMerge->AddIntermediate(uIncrementId);
			pOpLoopMerge->AddLiteral((uint32_t)_kLoopControl);

			pOpBranchCond->AddIntermediate(uExitId); // structured merge

			//GlobalAssembler.ForceNextLoads(false);
		}
	}
	//---------------------------------------------------------------------------------------------------
	// helper macros

#ifndef ExprCaptureRule
#define ExprCaptureRule =
#endif

#ifndef While
#define While(_cond) WhileFunc([ExprCaptureRule](){return _cond;}, [ExprCaptureRule]()
#endif // !While

#ifndef For
#define For(_var, _cond, _inc) _var; ForFunc([ExprCaptureRule](){return _cond;}, [ExprCaptureRule](){_inc;}, [ExprCaptureRule]()
#endif // !While

#pragma region if_else
	// renamed If and Else functions so that the macros are not part of the name
#ifndef If
#define If(_cond) IfNode((_cond), [ExprCaptureRule]()
#endif // !If

#ifndef Endif
#define Endif );
#endif // !Endif

#ifndef Else
#define Else ).ElseNode([ExprCaptureRule]()
#endif // !Else

#ifndef IF
#define IF(_cond) IfNode((_cond), [ExprCaptureRule]() {
#endif // !If

#ifndef ENDIF
#define ENDIF });
#endif // !Endif

#ifndef ELSE
#define ELSE }).ElseNode([ExprCaptureRule]() {
#endif // !Else
	//---------------------------------------------------------------------------------------------------

} // !Spear

#endif // !SPEAR_SPIRVBRANCHNODE_H
