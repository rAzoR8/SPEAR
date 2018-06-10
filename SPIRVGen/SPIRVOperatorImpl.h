//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVOPERATORIMPL_H
#define SPEAR_SPIRVOPERATORIMPL_H

#include "SPIRVVariable.h"
#include <vulkan\GLSL.std.450.h>
#include <glm\gtc\constants.hpp>

namespace Spear
{
	//---------------------------------------------------------------------------------------------------
	// create operation with no operands
	template <bool Assemble, class OpFunc, class T = std::invoke_result_t<OpFunc>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op0(const OpFunc& _OpFunc, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc();
		}
		else // Assemble
		{
			const spv::Op kOpCode = (spv::Op)OpTypeDecider<base_type_t<T>>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			var.uResultId = GlobalAssembler.EmplaceOperation(kOpCode, var.uTypeId);
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// create operation with one operand
	template <class U, class OpFunc, bool Assemble, spv::StorageClass C1, class T = std::invoke_result_t<OpFunc, const U&>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op1(const var_t<U, Assemble, C1>& l, const OpFunc& _OpFunc, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(l.Value);
		}
		else // Assemble
		{
			LoadVariables(l);

			const spv::Op kOpCode = (spv::Op)OpTypeDecider<base_type_t<U>>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");
			var.uResultId = GlobalAssembler.EmplaceOperation(kOpCode, var.uTypeId, SPIRVOperand::Intermediate(l.uResultId));
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// create operation with two operands
	template <class U, class V, class OpFunc, bool Assemble, spv::StorageClass C1, spv::StorageClass C2,  class T = std::invoke_result_t<OpFunc, const U&, const V&>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op2(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r, const OpFunc& _OpFunc, const EOpTypeBase _kOpTypeBase, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());
		
		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(l.Value, r.Value);		
		}
		else // Assemble
		{
			LoadVariables(l, r);

			const spv::Op kOpCode = (spv::Op)OpTypeDeciderEx<T, U, V>(_kOpTypeBase, _Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			var.uResultId = GlobalAssembler.EmplaceOperation(
                kOpCode,
                var.uTypeId, // result type
                SPIRVOperand::Intermediate(l.uResultId), // operand1
                SPIRVOperand::Intermediate(r.uResultId)  // operand2
            );
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// create operation with three operands
	template <class U, class V, class W, class OpFunc, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, class T = std::invoke_result_t<OpFunc, const U&, const V&, const W&>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_op3(
		const var_t<U, Assemble, C1>& v1,
		const var_t<V, Assemble, C2>& v2,
		const var_t<W, Assemble, C3>& v3,
		const OpFunc& _OpFunc,
		const EOpTypeBase _kOpTypeBase,
		const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(v1.Value, v2.Value, v3.Value);
		}
		else // Assemble
		{
			LoadVariables(v1, v2, v3);

			const spv::Op kOpCode = (spv::Op)OpTypeDeciderEx<T, U, V, W>(_kOpTypeBase, _Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			var.uResultId = GlobalAssembler.EmplaceOperation(
                kOpCode,
                var.uTypeId,
                SPIRVOperand::Intermediate(v1.uResultId),
                SPIRVOperand::Intermediate(v2.uResultId),
                SPIRVOperand::Intermediate(v3.uResultId)
            );
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// extension operation with no operands
	template <bool Assemble, class OpFunc, class T = std::invoke_result_t<OpFunc>, class ...Ops >
	inline var_t<T, Assemble, spv::StorageClassFunction> make_ext_op0(const OpFunc& _OpFunc, const std::string& _sExt, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc();
		}
		else
		{
			const uint32_t kOpCode = OpTypeDecider<base_type_t<T>>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			const uint32_t uExtId = GlobalAssembler.GetExtensionId(_sExt);
			HASSERT(uExtId != HUNDEFINED32, "Invalid extension");

			var.uResultId = GlobalAssembler.EmplaceOperation(
                spv::OpExtInst,
                var.uTypeId,
                SPIRVOperand(kOperandType_Intermediate, uExtId), // which extension
                SPIRVOperand(kOperandType_Literal, kOpCode) // instr opcode
            );
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// extension operation with one operand
	template <class U, class OpFunc, bool Assemble, spv::StorageClass C1, class T = std::invoke_result_t<OpFunc, const U&>, class ...Ops >
	inline var_t<T, Assemble, spv::StorageClassFunction> make_ext_op1(const var_t<U, Assemble, C1>& l, const OpFunc& _OpFunc, const std::string& _sExt, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(l.Value);
		}
		else
		{
			l.Load();

			const uint32_t kOpCode = OpTypeDecider<base_type_t<U>>(_Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			const uint32_t uExtId = GlobalAssembler.GetExtensionId(_sExt);
			HASSERT(uExtId != HUNDEFINED32, "Invalid extension");

			var.uResultId = GlobalAssembler.EmplaceOperation(
                spv::OpExtInst,
                var.uTypeId, // result type
                SPIRVOperand(kOperandType_Intermediate, uExtId), // which extension
                SPIRVOperand(kOperandType_Literal, kOpCode), // instr opcode
                SPIRVOperand(kOperandType_Intermediate, l.uResultId) // operand
            );
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// extension operation with two operands
	template <class U, class V, class OpFunc, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class T = std::invoke_result_t<OpFunc, const U&, const V&>, class ...Ops >
	inline var_t<T, Assemble, spv::StorageClassFunction> make_ext_op2(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r, const OpFunc& _OpFunc, const std::string& _sExt, const EOpTypeBase _kOpTypeBase, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(l.Value, r.Value);
		}
		else
		{
			LoadVariables(l, r);

			const spv::Op kOpCode = (spv::Op)OpTypeDeciderEx<T, U, V>(_kOpTypeBase, _Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			const uint32_t uExtId = GlobalAssembler.GetExtensionId(_sExt);
			HASSERT(uExtId != HUNDEFINED32, "Invalid extension");

            var.uResultId = GlobalAssembler.EmplaceOperation(
                spv::OpExtInst,
                var.uTypeId, // result type
                SPIRVOperand(kOperandType_Intermediate, uExtId), // which extension
                SPIRVOperand(kOperandType_Literal, kOpCode), // instr opcode
                SPIRVOperand(kOperandType_Intermediate, l.uResultId), // op1
                SPIRVOperand(kOperandType_Intermediate, r.uResultId) // op2
            );
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// extension operation with three operands
	template <class U, class V, class W, class OpFunc, bool Assemble,
		spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3,
		class T = std::invoke_result_t<OpFunc, const U&, const V&, const W&>, class ...Ops>
	inline var_t<T, Assemble, spv::StorageClassFunction> make_ext_op3(
		const var_t<U, Assemble, C1>& v1,
		const var_t<V, Assemble, C2>& v2,
		const var_t<W, Assemble, C3>& v3,
		const OpFunc& _OpFunc, const std::string& _sExt, const EOpTypeBase _kOpTypeBase, const Ops ..._Ops)
	{
		auto var = var_t<T, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr(Assemble == false)
		{
			var.Value = _OpFunc(v1.Value, v2.Value, v3.Value);
		}
		else
		{
			LoadVariables(v1, v2, v3);

			const spv::Op kOpCode = (spv::Op)OpTypeDeciderEx<T, U, V, W>(_kOpTypeBase, _Ops...);
			HASSERT(kOpCode != spv::OpNop, "Invalid variable base type!");

			const uint32_t uExtId = GlobalAssembler.GetExtensionId(_sExt);
			HASSERT(uExtId != HUNDEFINED32, "Invalid extension");

			var.uResultId = GlobalAssembler.EmplaceOperation(
                spv::OpExtInst,
                var.uTypeId,
                SPIRVOperand(kOperandType_Intermediate, uExtId), // which extension
                SPIRVOperand(kOperandType_Literal, kOpCode), // instr opcode
                SPIRVOperand(kOperandType_Intermediate, v1.uResultId), // op1
                SPIRVOperand(kOperandType_Intermediate, v2.uResultId), // op2
                SPIRVOperand(kOperandType_Intermediate, v3.uResultId) // op3
            );
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// Create a intermediate vector with dimension N from variable x
	template <uint32_t N, class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_scalar<T>>>
	inline var_t<vec_type_t<T, N>, Assemble, spv::StorageClassFunction> replicate(const var_t<T, Assemble, C1>& _Var)
	{
		auto var = var_t<vec_type_t<T, N>, Assemble, spv::StorageClassFunction>(TIntermediate());

		if constexpr (N == 1)
		{
			var = _Var;
			return var;
		}

		if constexpr(Assemble == false)
		{
			for (uint32_t i = 0; i < N; ++i)
			{
				var.Value[i] = _Var.Value;
			}
		}
		else
		{
			const uint32_t uId = _Var.Load();
			SPIRVOperation OpConstruct(spv::OpCompositeConstruct, var.uTypeId);
			for (uint32_t i = 0; i < N; ++i)
			{
				OpConstruct.AddIntermediate(uId);
			}
			var.uResultId = GlobalAssembler.AddOperation(std::move(OpConstruct));
		}

		return var;
	}

	//---------------------------------------------------------------------------------------------------
	// OPERATOR IMPLEMENTATIONS
	//---------------------------------------------------------------------------------------------------

	// ADD
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator+(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 + v2; }, kOpTypeBase_Result, spv::OpFAdd, spv::OpIAdd);
	}
	// add with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_convertible<V, T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator+(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) + r;
	}
	// add with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_convertible<V, T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator+(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l + var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}
	//---------------------------------------------------------------------------------------------------
	// SUB
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator-(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 - v2; }, kOpTypeBase_Result, spv::OpFSub, spv::OpISub);
	}
	// sub with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_convertible<V, T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator-(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return var_t<T, Assemble, spv::StorageClassFunction>((T)l) - r;
	}
	// sub with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_convertible<V, T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator-(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l - var_t<T, Assemble, spv::StorageClassFunction>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// MUL
	template <class U, class V, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class T = mul_result_t<U,V>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator*(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r)
	{
		if constexpr(is_vector<U> && is_scalar<V>)
			return make_op2(l, r, [](const U& v1, const V& v2) -> T {return v1 * v2; }, kOpTypeBase_Result, spv::OpVectorTimesScalar);
		else if constexpr(is_vector<V> && is_scalar<U>)
			return make_op2(r, l, [](const V& v1, const U& v2) -> T {return v1 * v2; }, kOpTypeBase_Result, spv::OpVectorTimesScalar);
		else if constexpr(is_matrix<V> || is_matrix<U>)
			return Mul(l, r); // implementation below
		else
			return make_op2(l, r, [](const U& v1, const V& v2) -> T {return v1 * v2; }, kOpTypeBase_Result, spv::OpFMul, spv::OpIMul);
	}

	// vector * matrix
	template <class M, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_matrix<M>>>
	inline var_t<row_type_t<M>, Assemble, spv::StorageClassFunction> Mul(
		const var_t<col_type_t<M>, Assemble, C1>& l,
		const var_t<M, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const col_type_t<M>& v, const M& m)-> row_type_t<M> {return v * m; }, kOpTypeBase_Result, spv::OpVectorTimesMatrix);
	}

	// matrix * vector
	template <class M, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_matrix<M>>>
	inline var_t<col_type_t<M>, Assemble, spv::StorageClassFunction> Mul(
		const var_t<M, Assemble, C1>& l,
		const var_t<row_type_t<M>, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const M& m, const row_type_t<M>& v)-> col_type_t<M> {return m * v; }, kOpTypeBase_Result, spv::OpMatrixTimesVector);
	}

	// matrix * matrix
	template <bool Assemble,
		spv::StorageClass C1, spv::StorageClass C2,
		class M, class N,
		class MRow = row_type_t<M>,
		class MCol = col_type_t<M>,
		class NRow = row_type_t<N>,
		class NCol = col_type_t<N>,
		class R = mat_type_t<NRow, MCol>,
		typename = std::enable_if_t<std::is_same_v<MRow, NCol>>>
		inline var_t<R, Assemble, spv::StorageClassFunction> Mul(
			const var_t<M, Assemble, C1>& l,
			const var_t<N, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const M& m, const N& n)-> R {return m * n; }, kOpTypeBase_Result, spv::OpMatrixTimesMatrix);
	}

	// mul with constant left
	template <class U, class V, bool Assemble, spv::StorageClass C1, class BaseType = base_type_t<V>, typename = std::enable_if_t<is_convertible<U, BaseType>>>
	inline var_t<V, Assemble, spv::StorageClassFunction> operator*(const U& l, const var_t<V, Assemble, C1>& r)
	{
		return make_const<Assemble>((BaseType)l) *  r;
	}

	// mul with constant right
	template <class U, class V, bool Assemble, spv::StorageClass C1, class BaseType = base_type_t<U>, typename = std::enable_if_t<is_convertible<V, BaseType>>>
	inline var_t<U, Assemble, spv::StorageClassFunction> operator*(const var_t<U, Assemble, C1>& l, const V& r)
	{
		return l * make_const<Assemble>((BaseType)r);
	}

	//---------------------------------------------------------------------------------------------------
	// DIV
	template <class U, class V, bool Assemble, spv::StorageClass C1, spv::StorageClass C2,
		class T = longer_type_t<U, V>,
		class BaseType = base_type_t<V>,
		typename = std::enable_if_t<std::is_same_v<V, base_type_t<U>> || std::is_same_v<U, V>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator/(const var_t<U, Assemble, C1>& l, const var_t<V, Assemble, C2>& r)
	{
		//The types of Operand 1 and Operand 2 both must be the same as Result Type
		if constexpr(std::is_same_v<U, V>)
		{
			return make_op2(l, r, [](const U& v1, const V& v2)-> T {return v1 / v2; }, kOpTypeBase_Result, spv::OpFDiv, spv::OpSDiv, spv::OpUDiv);
		}
		else // if right operand is a scalar, multiply with inverse
		{
			return l * var_t<BaseType, Assemble, spv::StorageClassFunction>((BaseType)1 / r);
		}
	}
	// div with constant left
	template <class U, class V, bool Assemble, spv::StorageClass C1, class BaseType = base_type_t<V>, typename = std::enable_if_t<is_convertible<U, BaseType>>>
	inline var_t<V, Assemble, spv::StorageClassFunction> operator/(const U& l, const var_t<V, Assemble, C1>& r)
	{
		return make_const<Assemble>((BaseType)l) / r;
	}
	// div with constant right
	template <class U, class V, bool Assemble, spv::StorageClass C1, class BaseType = base_type_t<U>, typename = std::enable_if_t<is_convertible<V, BaseType>>>
	inline var_t<U, Assemble, spv::StorageClassFunction> operator/(const var_t<U, Assemble, C1>& l, const V& r)
	{
		return l * make_const<Assemble>((BaseType)1 / (BaseType)r);
	}

	//---------------------------------------------------------------------------------------------------

	template<class ResultT, class ComponentOp>
	inline ResultT ComponentWiseOp(const ComponentOp& _CompFunc)
	{
		constexpr size_t N = Dimension<ResultT>;
		ResultT ret;
		for (uint32_t i = 0u; i < N; ++i)
		{
			ret[i] = _CompFunc(i);
		}

		return ret;
	}

	//---------------------------------------------------------------------------------------------------
	// EQUAL
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<Dimension<T> == 1>>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator==(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		return make_op2(L, R, [](const T& l, const T& r)->bool { return l == r; }, kOpTypeBase_Operand1, spv::OpFOrdEqual, spv::OpIEqual, spv::OpNop, spv::OpLogicalEqual);
	}

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<Dimension<T> != 1>>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator==(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		const auto equal = [](const T& l, const T& r)->condition_t<T>
		{
			return ComponentWiseOp<condition_t<T>>([&](const uint32_t i) {return l[i] == r[i]; });
		};

		return make_op2(L, R, equal, kOpTypeBase_Operand1, spv::OpFOrdEqual, spv::OpIEqual, spv::OpNop, spv::OpLogicalEqual);
	}

	// equal with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator==(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) == r;
	}
	// equal with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator==(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l == make_const<Assemble>((T)r);
	}
	//---------------------------------------------------------------------------------------------------
	// UNEQUAL
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<Dimension<T> == 1>>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator!=(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		return make_op2(L, R, [](const T& l, const T& r)->bool {return l != r; }, kOpTypeBase_Operand1, spv::OpFOrdNotEqual, spv::OpINotEqual, spv::OpNop, spv::OpLogicalNotEqual);
	}

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<Dimension<T> != 1>>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator!=(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		const auto equal = [](const T& l, const T& r)->condition_t<T>
		{
			return ComponentWiseOp<condition_t<T>>([&](const uint32_t i) {return l[i] != r[i]; });
		};

		return make_op2(L, R, equal, kOpTypeBase_Operand1, spv::OpFOrdNotEqual, spv::OpINotEqual, spv::OpNop, spv::OpLogicalNotEqual);
	}

	// unequal with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator!=(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) != r;
	}
	// unequal with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator!=(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l != make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// LOGICAL OR
	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator||(const var_t<bool, Assemble, C1>& L, const var_t<bool, Assemble, C2>& R)
	{
		return make_op2(l, r, [](const bool& v1, const bool& v2)-> bool {return v1 || v2; }, kOpTypeBase_Result, spv::OpLogicalOr);
	}

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_bool<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator||(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		const auto or = [](const T& l, const T& r)->T
		{
			return ComponentWiseOp<T>([&](const uint32_t i) {return l[i] || r[i]; });
		};
		return make_op2(L, R, or, kOpTypeBase_Operand1, spv::OpLogicalOr);
	}

	// logical or with constant left
	template <bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator||(const bool& l, const var_t<bool, Assemble, C1>& r)
	{
		return make_const<Assemble>(l) || r;
	}
	// logical or with constant right
	template <bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator||(const var_t<bool, Assemble, C1>& l, const bool& r)
	{
		return l || make_const<Assemble>(r);
	}

	//---------------------------------------------------------------------------------------------------
	// LOGICAL AND
	template <bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator&&(const var_t<bool, Assemble, C1>& l, const var_t<bool, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const bool& v1, const bool& v2)-> bool {return v1 && v2; }, kOpTypeBase_Result, spv::OpLogicalAnd);
	}

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_bool<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator&&(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		const auto and = [](const T& l, const T& r)->T
		{
			return ComponentWiseOp<T>([&](const uint32_t i) {return l[i] && r[i]; });
		};
		return make_op2(L, R, and , kOpTypeBase_Operand1, spv::OpLogicalAnd);
	}

	// logical and with constant left
	template <bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator&&(const bool& l, const var_t<bool, Assemble, C1>& r)
	{
		return make_const<Assemble>(l) && r;
	}
	// logical and with constant right
	template <bool Assemble, spv::StorageClass C1>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator&&(const var_t<bool, Assemble, C1>& l, const bool& r)
	{
		return l && make_const<Assemble>(r);
	}

	//---------------------------------------------------------------------------------------------------
	// BITWISE OR
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator|(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 | v2; }, kOpTypeBase_Result, spv::OpBitwiseOr);
	}
	// bitwise or with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator|(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) | r;
	}
	// bitwise or with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator|(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l | make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// BITWISE XOR
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator^(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 ^ v2; }, kOpTypeBase_Result, spv::OpBitwiseXor);
	}
	// bitwise xor with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator^(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) ^ r;
	}
	// bitwise xor with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator^(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l ^ make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// BITWISE AND
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator&(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 & v2; }, kOpTypeBase_Result, spv::OpBitwiseAnd);
	}
	// bitwise and with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator&(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) & r;
	}
	// bitwise and with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator&(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l & make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Less
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_scalar<T>>>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator<(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		return make_op2(L, R, [](const T& v1, const T& v2)-> bool {return v1 < v2; }, kOpTypeBase_Operand1, spv::OpFOrdLessThan, spv::OpSLessThan, spv::OpULessThan);
	}

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector<T>>>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator<(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		const auto less = [](const T& l, const T& r)->condition_t<T>
		{
			return ComponentWiseOp<condition_t<T>>([&](const uint32_t i) {return l[i] < r[i]; });
		};
		return make_op2(L, R, less, kOpTypeBase_Operand1, spv::OpFOrdLessThan, spv::OpSLessThan, spv::OpULessThan);
	}
	// Less with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator<(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) < r;
	}
	// Less with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator<(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l < make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Less then equal
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_scalar<T>>>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator<=(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		return make_op2(L, R, [](const T& v1, const T& v2)-> bool {return v1 <= v2; }, kOpTypeBase_Operand1, spv::OpFOrdLessThanEqual, spv::OpSLessThanEqual, spv::OpULessThanEqual);
	}

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector<T>>>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator<=(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		const auto lessthan = [](const T& l, const T& r)->condition_t<T>
		{
			return ComponentWiseOp<condition_t<T>>([&](const uint32_t i) {return l[i] <= r[i]; });
		};
		return make_op2(L, R, lessthan, kOpTypeBase_Operand1, spv::OpFOrdLessThanEqual, spv::OpSLessThanEqual, spv::OpULessThanEqual);
	}

	// Less then equal with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator<=(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) <= r;
	}
	// Less then equal with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator<=(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l <= make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// GREATER
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_scalar<T>>>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator>(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		return make_op2(L, R, [](const T& v1, const T& v2)-> bool {return v1 > v2; }, kOpTypeBase_Operand1, spv::OpFOrdGreaterThan, spv::OpSGreaterThan, spv::OpUGreaterThan);
	}

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector<T>>>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator>(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		const auto greater = [](const T& l, const T& r)->condition_t<T>
		{
			return ComponentWiseOp<condition_t<T>>([&](const uint32_t i) {return l[i] > r[i]; });
		};
		return make_op2(L, R, greater, kOpTypeBase_Operand1, spv::OpFOrdGreaterThan, spv::OpSGreaterThan, spv::OpUGreaterThan);
	}

	// greater with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator>(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) > r;
	}
	// greater with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator>(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l > make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Greater then equal
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_scalar<T>>>
	inline var_t<bool, Assemble, spv::StorageClassFunction> operator>=(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		return make_op2(L, R, [](const T& v1, const T& v2)-> bool {return v1 >= v2; }, kOpTypeBase_Operand1, spv::OpFOrdGreaterThanEqual, spv::OpSGreaterThanEqual, spv::OpUGreaterThanEqual);
	}

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector<T>>>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator>=(const var_t<T, Assemble, C1>& L, const var_t<T, Assemble, C2>& R)
	{
		const auto greaterthan = [](const T& l, const T& r)->condition_t<T>
		{
			return ComponentWiseOp<condition_t<T>>([&](const uint32_t i) {return l[i] >= r[i]; });
		};
		return make_op2(L, R, greaterthan, kOpTypeBase_Operand1, spv::OpFOrdGreaterThanEqual, spv::OpSGreaterThanEqual, spv::OpUGreaterThanEqual);
	}

	// Greater then equal with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator>=(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) >= r;
	}
	// Greater then equal with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<condition_t<T>, Assemble, spv::StorageClassFunction> operator>=(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l >= make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Logical Shift Right
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator>>(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 >> v2; }, kOpTypeBase_Result, spv::OpShiftRightLogical);
	}
	// logical shift right with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator>>(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) >> r;
	}
	// logical shift right with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator>>(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l >> make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// Logical Shift left
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator<<(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& v1, const T& v2)-> T {return v1 << v2; }, kOpTypeBase_Result, spv::OpShiftLeftLogical);
	}
	// logical shift left with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator<<(const V& l, const var_t<T, Assemble, C1>& r)
	{
		return make_const<Assemble>((T)l) << r;
	}
	// logical shift left with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_integer<T> || is_base_integer<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator<<(const var_t<T, Assemble, C1>& l, const V& r)
	{
		return l << make_const<Assemble>((T)r);
	}

	//---------------------------------------------------------------------------------------------------
	// DOT
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_vector_float<T>>>
	inline var_t<base_type_t<T>, Assemble, spv::StorageClassFunction> Dot(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_op2(l, r, [](const T& u, const T& v)-> base_type_t<T> {return glm::dot(u, v); }, kOpTypeBase_Result, spv::OpDot);
	}

	//---------------------------------------------------------------------------------------------------
	// Transpose Matrix
	template <class M, bool Assemble, spv::StorageClass C1,
		class RowT = row_type_t<M>, class ColT = col_type_t<M>, class R = mat_type_t<ColT, RowT>,
		typename = std::enable_if_t<is_matrix<M>>>
	inline var_t<R, Assemble, spv::StorageClassFunction> Transpose(const var_t<M, Assemble, C1>& _Mat)
	{
		return make_op1(_Mat, [](const M& m)-> R {return glm::transpose(m); }, spv::OpTranspose);
	}

	//---------------------------------------------------------------------------------------------------
	// Fragment derivative ddx
	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Ddx(const var_t<T, Assemble, C1>& P)
	{
		// TODO: DDX not implemented for CPU execution
		return make_op1(P, [](const T& p)-> T {return p; }, spv::OpDPdx);
	}

	//---------------------------------------------------------------------------------------------------
	// Fragment derivative ddy
	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Ddy(const var_t<T, Assemble, C1>& P)
	{
		// TODO: DDY not implemented for CPU execution
		return make_op1(P, [](const T& p)-> T {return p; }, spv::OpDPdy);
	}

	//---------------------------------------------------------------------------------------------------
	// Result is true if any component is true
	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_bool<T>>>
	inline var_t<bool, Assemble, spv::StorageClassFunction> Any(const var_t<T, Assemble, C1>& _Bools)
	{
		const auto any = [](const T& b)-> bool
		{
			for (uint32_t i = 0; i < Dimension<T>; ++i)
			{
				if (b[i])
					return true;
			};

			return false;
		};

		return make_op1(_Bools, any, spv::OpAny);
	}

	//---------------------------------------------------------------------------------------------------
	// Result is true if all components are true
	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_vector_bool<T>>>
	inline var_t<bool, Assemble, spv::StorageClassFunction> All(const var_t<T, Assemble, C1>& _Bools)
	{
		const auto any = [](const T& b)-> bool
		{
			for (uint32_t i = 0; i < Dimension<T>; ++i)
			{
				if (b[i] == false)
					return false;
			};

			return true;
		};

		return make_op1(_Bools, any, spv::OpAll);
	}

	//---------------------------------------------------------------------------------------------------
	// Select from two objects
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, typename = std::enable_if_t<is_vector<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Select(const var_t<condition_t<T>, Assemble, C1>& Condition, const var_t<T, Assemble, C2>& TrueVar, const var_t<T, Assemble, C3>& FalseVar)
	{
		const auto select = [](const condition_t<T>& cond, const T& l, const T& r)->T
		{
			return ComponentWiseOp<T>([&](const uint32_t& i) {return (cond[i]) ? l[i] : r[i]; });
		};
		return make_op3(Condition, TrueVar, FalseVar, select, kOpTypeBase_Result, spv::OpSelect);
	}

	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> Select(const var_t<bool, Assemble, C1>& Condition, const var_t<T, Assemble, C2>& TrueVar, const var_t<T, Assemble, C3>& FalseVar)
	{
		if constexpr(is_scalar<T>)
		{
			return make_op3(Condition, TrueVar, FalseVar, [](const bool& cond, const T& l, const T& r) -> T {return cond ? l : r; }, kOpTypeBase_Result, spv::OpSelect);
		}
		else
		{
			return Select(replicate<Dimension<T>>(Condition), TrueVar, FalseVar);
		}
	}

	//---------------------------------------------------------------------------------------------------
	// GLSLstd450 EXTENSION
	//---------------------------------------------------------------------------------------------------
	// https://www.khronos.org/registry/spir-v/specs/unified1/GLSL.std.450.pdf

	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Round(const var_t<T, Assemble, C1>& X)
	{
		return make_ext_op1(X, [](const T& x) -> T {return glm::round(x); }, ExtGLSL450, GLSLstd450Round);
	}

	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> RoundEven(const var_t<T, Assemble, C1>& X)
	{
		return make_ext_op1(X, [](const T& x) -> T {return glm::roundEven(x); }, ExtGLSL450, GLSLstd450RoundEven);
	}

	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Floor(const var_t<T, Assemble, C1>& X)
	{
		return make_ext_op1(X, [](const T& x) -> T {return glm::floor(x); }, ExtGLSL450, GLSLstd450Floor);
	}

	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Ceil(const var_t<T, Assemble, C1>& X)
	{
		return make_ext_op1(X, [](const T& x) -> T {return glm::ceil(x); }, ExtGLSL450, GLSLstd450Ceil);
	}

	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Frac(const var_t<T, Assemble, C1>& X)
	{
		return make_ext_op1(X, [](const T& x) -> T {return glm::frac(x); }, ExtGLSL450, GLSLstd450Frac);
	}

	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Trunc(const var_t<T, Assemble, C1>& X)
	{
		return make_ext_op1(X, [](const T& x) -> T {return glm::trunc(x); }, ExtGLSL450, GLSLstd450Trunc);
	}

	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Sign(const var_t<T, Assemble, C1>& X)
	{
		return make_ext_op1(X, [](const T& x) -> T {return glm::sign(x); }, ExtGLSL450, GLSLstd450FSign, GLSLstd450SSign);
	}

	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Abs(const var_t<T, Assemble, C1>& X)
	{
		return make_ext_op1(X, [](const T& x) -> T {return glm::abs(x); }, ExtGLSL450,  GLSLstd450FAbs, GLSLstd450SAbs);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Radians(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::radians(v1); }, ExtGLSL450, GLSLstd450Radians);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Degrees(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::degrees(v1); }, ExtGLSL450, GLSLstd450Degrees);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Sin(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sin(v1); }, ExtGLSL450, GLSLstd450Sin);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Cos(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::cos(v1); }, ExtGLSL450, GLSLstd450Cos);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Tan(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::tan(v1); }, ExtGLSL450, GLSLstd450Tan);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Asin(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::asin(v1); }, ExtGLSL450, GLSLstd450Asin);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Acos(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::acos(v1); }, ExtGLSL450, GLSLstd450Acos);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Atan(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::atan(v1); }, ExtGLSL450, GLSLstd450Atan);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Sinh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sinh(v1); }, ExtGLSL450, GLSLstd450Sinh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Cosh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::cos(v1); }, ExtGLSL450, GLSLstd450Cosh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Tanh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::tan(v1); }, ExtGLSL450, GLSLstd450Tanh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Asinh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::asinh(v1); }, ExtGLSL450, GLSLstd450Asinh);
	}
	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Acosh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::acosh(v1); }, ExtGLSL450, GLSLstd450Acosh);
	}
	//---------------------------------------------------------------------------------------------------
	// Result is undefined if abs x >= 1. Results are computed per component.
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Atanh(const var_t<T, Assemble, C1>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::atanh(v1); }, ExtGLSL450, GLSLstd450Atanh);
	}
	//---------------------------------------------------------------------------------------------------
	// Arc tangent. Result is an angle, in radians, whose tangent is y / x. The signs of x and y are used
	// to determine what quadrant the angle is in. The range of result values is[-pi,pi].
	// Result is undefined if x	and	y are both 0.
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Atan2(const var_t<T, Assemble, C1>& x, const var_t<T, Assemble, C2>& y)
	{
		return make_ext_op2(x, y, [](const T& _x, const T& _y) {return glm::atan(_x, _y); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Atan2);
	}
	//---------------------------------------------------------------------------------------------------
	// Exponential function x^y Results are computed per componen
	// Result is undefined if x	< 0. Result is undefined if	x = 0 and y <= 0
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Pow(const var_t<T, Assemble, C1>& x, const var_t<T, Assemble, C2>& y)
	{
		return make_ext_op2(x, y, [](const T& v1, const T& v2) {return glm::pow(v1, v2); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Pow);
	}
	// pow with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Pow(const V& x, const var_t<T, Assemble, C1>& y)
	{
		return Pow(make_const<Assemble>((T)x), y);
	}
	// pow with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Pow(const var_t<T, Assemble, C1>& x, const V& y)
	{
		return Pow(x, make_const<Assemble>((T)y));
	}

	//---------------------------------------------------------------------------------------------------
	// Log Results are computed per componen
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Log(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::log(v1); }, ExtGLSL450, GLSLstd450Log);
	}	
	//---------------------------------------------------------------------------------------------------
	// Log2 Base 2 Results are computed per componen
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Log2(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::log2(v1); }, ExtGLSL450, GLSLstd450Log2);
	}
	//---------------------------------------------------------------------------------------------------
	// Exponential function e^x
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Exp(const var_t<T, Assemble, Class>& x)
	{
		return make_ext_op1(x, [](const T& v1) {return glm::exp(v1); }, ExtGLSL450, GLSLstd450Exp);
	}
	//---------------------------------------------------------------------------------------------------
	// Exponential function base 2 2^x
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Exp2(const var_t<T, Assemble, Class>& x)
	{
		return make_ext_op1(x, [](const T& v1) {return glm::exp2(v1); }, ExtGLSL450, GLSLstd450Exp2);
	}
	//---------------------------------------------------------------------------------------------------
	// SquareRoot Results are computed per component.
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Sqrt(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::sqrt(v1); }, ExtGLSL450, GLSLstd450Sqrt);
	}
	//---------------------------------------------------------------------------------------------------
	// InverseSqrt Results are computed per component.
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> InvSqrt(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::inversesqrt(v1); }, ExtGLSL450, GLSLstd450InverseSqrt);
	}

	//---------------------------------------------------------------------------------------------------
	// Normalize
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<T, Assemble, spv::StorageClassFunction> Normalize(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::normalize(v1); }, ExtGLSL450, GLSLstd450Normalize);
	}
	//---------------------------------------------------------------------------------------------------
	// Length
	template <class T, bool Assemble, spv::StorageClass Class>
	inline var_t<base_type_t<T>, Assemble, spv::StorageClassFunction> Length(const var_t<T, Assemble, Class>& l)
	{
		return make_ext_op1(l, [](const T& v1) {return glm::length(v1); }, ExtGLSL450, GLSLstd450Length);
	}
	//---------------------------------------------------------------------------------------------------
	// Distance
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<base_type_t<T>, Assemble, spv::StorageClassFunction> Distance(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_ext_op2(l, r, [](const T& v1, const T& v2) {return glm::distance(v1, v2); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Distance);
	}
	//---------------------------------------------------------------------------------------------------
	// Cross product
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2/*, class T = vec_type_t<FloatT, 3>*/>
	inline var_t<T, Assemble, spv::StorageClassFunction> Cross(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return make_ext_op2(l, r, [](const T& v1, const T& v2) -> T{return glm::cross(v1, v2); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Cross);
	}
	//---------------------------------------------------------------------------------------------------
	// FMA fused multiply add
	template <class A, class B, class C, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3,
		typename = std::enable_if_t<is_base_float<A> && is_base_float<B> && is_base_float<C>>>
	inline auto Fma(const var_t<A, Assemble, C1>& va, const var_t<B, Assemble, C2>& vb, const var_t<C, Assemble, C3>& vc)
	{
		return make_ext_op3(va, vb, vc, [](const A& a, const B& b, const C& c) {return a * b + c; }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Fma);
	}
	//---------------------------------------------------------------------------------------------------
	// MatrixInverse
	//template <bool Assemble, spv::StorageClass Class, uint32_t Dim, class Mat = mat_type_dim_t<float, Dim, Dim>>
	template <
		class M, bool Assemble, spv::StorageClass Class,
		class Row = row_type_t<M>, class Col = col_type_t<M>,
		typename = std::enable_if_t<std::is_same_v<Row, Col>>> // Square matrix
	inline var_t<M, Assemble, spv::StorageClassFunction> Inverse(const var_t<M, Assemble, Class>& _Mat)
	{
		return make_ext_op1(_Mat, [](const M& m) {return glm::inverse(m); }, ExtGLSL450, GLSLstd450MatrixInverse);
	}
	//---------------------------------------------------------------------------------------------------
	// MatrixDeterminant
	template <
		class M, bool Assemble, spv::StorageClass Class,
		class Row = row_type_t<M>, class Col = col_type_t<M>, class R = base_type_t<M>,
		typename = std::enable_if_t<std::is_same_v<Row, Col>>> // Square matrix
		inline var_t<R, Assemble, spv::StorageClassFunction> Determinant(const var_t<M, Assemble, Class>& _Mat)
	{
		return make_ext_op1(_Mat, [](const M& m) {return glm::determinant(m); }, ExtGLSL450, GLSLstd450Determinant);
	}

	//---------------------------------------------------------------------------------------------------
	// Reflect: For the incident vector I and surface orientation N, the result is the reflection direction: I - 2 * dot(N,I) *	N
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Reflect(const var_t<T, Assemble, C1>& I, const var_t<T, Assemble, C2>& N)
	{
		return make_ext_op2(I, N, [](const T& i, const T& n) {return glm::reflect(i, n); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Reflect);
	}
	//---------------------------------------------------------------------------------------------------

	// Refract: For the incident vector I and surface normal N, and the ratio of indices of refraction eta, the result is the refraction vector.
	// The result is computed by k = 1.0 - eta * eta * (1.0 - dot(N,I) * dot(N,I))
	// if k < 0.0 the result is 0.0	otherwise, the result is eta * I - (eta	* dot(N,I) + sqrt(k)) *	N
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> Refract(const var_t<T, Assemble, C1>& I, const var_t<T, Assemble, C2>& N, const var_t<base_type_t<T>, Assemble, C3>& ETA)
	{
		return make_ext_op3(I, N, ETA, [](const T& i, const T& n, const base_type_t<T>& eta) {return glm::refract(i, n, eta); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Refract);
	}

	// Refract with constant ETA
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Refract(const var_t<T, Assemble, C1>& I, const var_t<T, Assemble, C2>& N, const base_type_t<T>& ETA)
	{
		return Refract(I, N, make_const<Assemble>(ETA));
	}

	//---------------------------------------------------------------------------------------------------
	// Clamp
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> Clamp(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Min, const var_t<T, Assemble, C3>& Max)
	{
		return make_ext_op3(X, Min, Max, [](const T& x, const T& min, const T& max) -> T{return glm::clamp(x, min, max); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450FClamp, GLSLstd450SClamp, GLSLstd450UClamp);
	}
	//---------------------------------------------------------------------------------------------------
	// Min
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Min(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y)
	{
		return make_ext_op2(X, Y, [](const T& x, const T& y) -> T {return glm::min(x, y); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450FMin, GLSLstd450SMin, GLSLstd450UMin);
	}
	// min with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Min(const var_t<T, Assemble, C1>& X, const V& Y)
	{
		return Min(X, make_const<Assemble>((T)Y));
	}
	// min with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Min(const V& X, const var_t<T, Assemble, C1>& Y)
	{
		return Min(make_const<Assemble>((T)X), Y);
	}
	// variadic min
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class ...Ts>
	inline var_t<T, Assemble, spv::StorageClassFunction> Min(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y, const Ts& ..._Args)
	{
		return Min(Min(X, Y), _Args...);
	}

	//---------------------------------------------------------------------------------------------------
	//Max
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Max(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y)
	{
		return make_ext_op2(X, Y, [](const T& x, const T& y) -> T {return glm::max(x, y); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450FMax, GLSLstd450SMax, GLSLstd450UMax);
	}
	// max with constant right
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Max(const var_t<T, Assemble, C1>& X, const V& Y)
	{
		return Max(X, make_const<Assemble>((T)Y));
	}
	// max with constant left
	template <class T, class V, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> Max(const V& X, const var_t<T, Assemble, C1>& Y)
	{
		return Max(make_const<Assemble>((T)X), Y);
	}
	// variadic max
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, class ...Ts>
	inline var_t<T, Assemble, spv::StorageClassFunction> Max(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y, const Ts& ..._Args)
	{
		return Max(Max(X, Y), _Args...);
	}

	//---------------------------------------------------------------------------------------------------
	// Mix  linear blend of x and y , i.e., x * (1-a) + y*a
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> Mix(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y, const var_t<T, Assemble, C3>& A)
	{
		return make_ext_op3(X, Y, A, [](const T& x, const T& y, const T& a) -> T {return glm::mix(x, y, a); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450FMix, GLSLstd450IMix);
	}
	//---------------------------------------------------------------------------------------------------
	// Step Result is 0.0 if x < edge; otherwise result is 1.0
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Step(const var_t<T, Assemble, C1>& Edge, const var_t<T, Assemble, C2>& X)
	{
		if constexpr (is_float_type<T>)// scalar, glm included in VulkanSDK does not have lessThan for non vector types (glm version from repo worked)		
		{
			return make_ext_op2(Edge, X, [](const T& e, const T& x) -> T {return glm::mix(static_cast<T>(1), static_cast<T>(0), x < e); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Step);
		}
		else if constexpr(is_vector_float<T>)
		{
			return make_ext_op2(Edge, X, [](const T& e, const T& x) -> T {return glm::step(e, x); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450Step);		
		}
	}
	//---------------------------------------------------------------------------------------------------
	// SmoothStep 
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3, typename = std::enable_if_t<is_base_float<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> SmoothStep(const var_t<T, Assemble, C1>& Edge1, const var_t<T, Assemble, C2>& Edge2, const var_t<T, Assemble, C3>& X)
	{
		return make_ext_op3(Edge1, Edge2, X, [](const T& e1, const T& e2, const T& x) -> T {return glm::smoothstep(e1, e2, x); }, ExtGLSL450, kOpTypeBase_Result, GLSLstd450SmoothStep);
	}
	//---------------------------------------------------------------------------------------------------
	// HELPER FUNCTIONS
	//---------------------------------------------------------------------------------------------------

	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<mul_result_t<T, T>, Assemble, spv::StorageClassFunction> Square(const var_t<T, Assemble, C1>& x)
	{
		return x * x;
	}

	template <class T, bool Assemble, spv::StorageClass C1/*, class R = mul_result_t<T, mul_result_t<T, T>>*/>
	inline auto Qubic(const var_t<T, Assemble, C1>& x)
	{
		return x * x * x;
	}

	// Clamp X between 0 and 1 componentwise
	template <class T, bool Assemble, spv::StorageClass C1, class BaseT = base_type_t<T>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Saturate(const var_t<T, Assemble, C1>& x)
	{
		constexpr uint32_t N{ Dimension<T> };
		std::array<BaseT, N> Zero; Zero.fill(BaseT(0));
		std::array<BaseT, N> One; One.fill(BaseT(1));

		return Clamp(x, make_const_vec<Assemble, N, BaseT>(Zero), make_const_vec<Assemble, N, BaseT>(One));
	}

	//---------------------------------------------------------------------------------------------------
	// LERP
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> Lerp(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r, const var_t<float, Assemble, C3> t)
	{
		return l * (1.f - t) + r * t;
		//return Mix(l, r, t);
	}

	// Lerp between constants
	template <class T, bool Assemble, spv::StorageClass C1, typename = std::enable_if_t<!is_var<T>>>
	inline var_t<T, Assemble, spv::StorageClassFunction> Lerp(const T& l, const T& r, const var_t<float, Assemble, C1> t)
	{
		return Lerp(make_const<Assemble>(l), make_const<Assemble>(r), t);
	}

	//---------------------------------------------------------------------------------------------------
	// NDC to [0..1]
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<T, Assemble, spv::StorageClassFunction> NDCToZeroOne(const var_t<T, Assemble, C1>& ndc)
	{
		return (ndc + 1.f) * 0.5f;
	}

	//---------------------------------------------------------------------------------------------------
	// NDC to range
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2, spv::StorageClass C3>
	inline var_t<T, Assemble, spv::StorageClassFunction> NDCToRange(const var_t<T, Assemble, C1>& ndc, const var_t<float, Assemble, C2>& low, const var_t<float, Assemble, C3> high)
	{
		return low + ((ndc + 1.f) * 0.5f * (high - low));
	}

	//---------------------------------------------------------------------------------------------------
	// returns size of the encapsulated type
	template <class T, bool Assemble, spv::StorageClass C1>
	inline var_t<uint32_t, Assemble, spv::StorageClassFunction> SizeOf(const var_t<T, Assemble, C1>& var)
	{
		// create variable initialized with constant
		if constexpr(Assemble)
		{
			return make_const<Assemble>(var.Type.GetSize());
		}
		else
		{
			//static_assert(is_struct<T> == false, "FromType not implemented for structures");
			return make_const<Assemble>(SPIRVType::FromType<T>().GetSize());
		}
	}

	//---------------------------------------------------------------------------------------------------
	// Modulo
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> Mod(const var_t<T, Assemble, C1>& X, const var_t<T, Assemble, C2>& Y)
	{
		constexpr uint32_t Dim = Dimension<T>;
		using FloatType = vec_type_t<float, Dim>;

		if constexpr (is_base_float<T>)
		{
			return X - Y * Floor(X / Y);
		}
		else
		{
			auto x = spv_cast<FloatType>(X);
			auto y = spv_cast<FloatType>(Y);

			return spv_cast<T>(x - x * Floor(x / y));
		}
	}

	//---------------------------------------------------------------------------------------------------
	template <class T, bool Assemble, spv::StorageClass C1, spv::StorageClass C2>
	inline var_t<T, Assemble, spv::StorageClassFunction> operator%(const var_t<T, Assemble, C1>& l, const var_t<T, Assemble, C2>& r)
	{
		return Mod(l, r);
	}
	//---------------------------------------------------------------------------------------------------

}; //!Spear

#endif // !SPEAR_SPIRVOPERATORIMPL_H
