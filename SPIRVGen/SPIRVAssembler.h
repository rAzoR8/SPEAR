//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#ifndef SPEAR_SPIRVASSEMBLER_H
#define SPEAR_SPIRVASSEMBLER_H

#include "SPIRVOperation.h"
#include "SPIRVInstruction.h"
#include "SPIRVModule.h"
#include "Flag.h"
#include "Logger.h"
#include <mutex>

namespace Spear
{
	using namespace hlx;

	inline constexpr bool is_type_op(spv::Op _Op) {return _Op >= spv::OpTypeVoid && _Op <= spv::OpTypeForwardPointer; };
	inline constexpr bool is_const_op (spv::Op _Op) {return _Op >= spv::OpConstantTrue && _Op <= spv::OpSpecConstantOp; };
	inline constexpr bool is_type_or_const_op(spv::Op _Op) { return is_type_op(_Op) || is_const_op(_Op); }	
	inline constexpr bool is_decorate_op (spv::Op _Op) {return _Op >= spv::OpDecorate && _Op <= spv::OpGroupMemberDecorate; };
	inline constexpr bool is_var_op(spv::Op _Op) {return _Op == spv::OpVariable; };
	inline constexpr bool is_name_op(spv::Op _Op) { return _Op == spv::OpName || _Op == spv::OpMemberName; };

	// forward decls
	template <bool Assemble>
	class SPIRVProgram;

	template <bool Assemble>
	struct var_decoration;

	class SPIRVConstant;

	static const std::string ExtGLSL450 = "GLSL.std.450";

	enum EOptimizationPassFlag : uint32_t
	{
		kOptimizationPassFlag_None = 0,
		kOptimizationPassFlag_AllPerformance = 1 << 0,
		kOptimizationPassFlag_AllSize = 1 << 1,
		kOptimizationPassFlag_All = UINT32_MAX
	};

	using TOptimizationPassFlags = hlx::Flag<EOptimizationPassFlag>;

	struct OptimizationSettings
	{
		TOptimizationPassFlags kPasses;
	};

	class SPIRVAssembler
	{
	public:
		using TIdMap = std::unordered_map<size_t, uint32_t>;

        inline static SPIRVAssembler& Instance()
        {
            static SPIRVAssembler inst;
            return inst;
        }

		SPIRVAssembler() noexcept;
		virtual ~SPIRVAssembler();

		template <class TProg, class... Ts>
		void InitializeProgram(Ts&& ..._args);

		template <class TProg, class... Ts>
		void RecordInstructions(Ts&& ..._args);

		SPIRVModule Assemble();

		// calls InitializeProgram with Ts args, RecordInstructions without args and Assemble
		template <class TProg, class... Ts>
		SPIRVModule AssembleSimple(const bool _bUseDefaults = true, Ts&& ..._args);

		uint32_t GetExtensionId(const std::string& _sExt = ExtGLSL450);

		// _pOutInstr gets a pointer to the stored instruction so that i can be modified later (add operands)
		//uint32_t AddOperation(const SPIRVOperation& _Instr, SPIRVOperation** _pOutInstr = nullptr);

        // move op
        uint32_t AddOperation(SPIRVOperation&& _Instr, SPIRVOperation** _pOutInstr = nullptr);

        template <class ...Ts>
        uint32_t EmplaceOperation(Ts&& ..._args);

		uint32_t AddConstant(const SPIRVConstant& _Const);
		uint32_t AddType(const SPIRVType& _Type);

		void AddVariableInfo(const var_decoration<true>& _Var);

		void SetDefaults() noexcept;
		void UseDefaultSetLocation(const uint32_t _uDefaultSet = 0u, const uint32_t _uDefaultInputLocation = 0u, const uint32_t _uDefaultOutputLocation = 0u) noexcept;
		void UseDefaultSpecConstId(const uint32_t _uStartId = 0u) noexcept;
		void UseDefaultInputAttachmentIndex(const uint32_t _uStartIndex = 0u) noexcept;
		void ConfigureOptimization(const OptimizationSettings& _Settings);

		void RemoveUnusedOperations(const bool _bEnable = true) noexcept;
		bool GetRemoveUnusedOperations() const noexcept;

		void EnterScope();
		void LeaveScope();

		const uint32_t& GetScopeLevel() const;
		const uint32_t& GetScopeID() const;

		const uint32_t& GetDefaultSet() const noexcept;
		const uint32_t GetCurrentBinding(const uint32_t _uSet);

		const uint32_t GetCurrentInputLocation() noexcept;
		const uint32_t GetCurrentOutputLocation() noexcept;
		const uint32_t GetCurrentSpecConstId() noexcept;
		const uint32_t GetCurrentInputAttchmentIndex() noexcept;

		static SPIRVModule ExternalOptimize(const SPIRVModule& _Module, const OptimizationSettings& _Settings);

	private:
		void Init(const std::unique_ptr<SPIRVProgram<true>>& _pProgram);

		void Resolve();

		SPIRVInstruction Translate(SPIRVOperation& _Op);

		void AddInstruction(const SPIRVInstruction& _Instr);

		void AssignId(SPIRVOperation& _Op);

		void FlagUnused();

		spv::StorageClass GetStorageClass(const SPIRVOperation& _Op) const;

		template <class Fn, class Pred>
		void ForEachOp(const Fn& _fn, const Pred& _Pred);

		template <class Fn, class Pred>
		void ForEachOpEx(const Fn& _fn, const Pred& _Pred);

		void AddPreambleId(const uint32_t& _uId);

	private:
		std::mutex m_Mutex;

		OptimizationSettings m_OptSettings;

		// remove variables, types, constants
		bool m_bRemoveUnused = true;

		std::unique_ptr<SPIRVProgram<true>> m_pAssembleProgram = nullptr;
		std::unique_ptr<SPIRVProgram<false>> m_pExecuteProgram = nullptr;

		std::vector<std::string> m_Extensions;
		std::unordered_map<std::string, uint32_t> m_ExtensionIds;

		uint32_t m_uInstrId = 0u; // internal instruction id
		uint32_t m_uResultId = 1u; // actual result ids

		SPIRVOperation* m_pOpEntryPoint = nullptr;
		SPIRVOperation* m_pOpExeutionMode = nullptr;

		std::string m_sEntryPoint;
		spv::ExecutionModel m_kModel = spv::ExecutionModelMax;
		spv::ExecutionMode m_kMode = spv::ExecutionModeMax;
		std::vector<spv::Capability> m_Capabilities;
		
		std::vector<SPIRVInstruction> m_Instructions;

		uint32_t m_uScopeLevel = 0;
		uint32_t m_uScopeID = 0;

		uint32_t m_uDefaultSet = HUNDEFINED32;

		// set -> binding
		std::unordered_map<uint32_t, uint32_t> m_Bindings;

		uint32_t m_uCurrentInputLocation = HUNDEFINED32;
		uint32_t m_uCurrentOutputLocation = HUNDEFINED32;
		uint32_t m_uCurrentSpecConstId = HUNDEFINED32;
		uint32_t m_uCurrentInputAttachmentIndex = HUNDEFINED32;

		// type instruction id
		TIdMap m_TypeIds;
		// constant instruction id
		TIdMap m_ConstantIds;

		std::vector<SPIRVOperation> m_Operations; // unresolved local instruction stream

		uint32_t m_uFunctionPreambleIndex = 0u;
		std::vector<uint32_t> m_PreambleOpIds;

		// var id -> VariableInfo
		std::unordered_map<uint32_t, VariableInfo> m_UsedVariables; // info on loaded / stored variables
	};
	//---------------------------------------------------------------------------------------------------
	inline void SPIRVAssembler::SetDefaults() noexcept
	{
		UseDefaultSetLocation();
		UseDefaultSpecConstId();
		UseDefaultInputAttachmentIndex();
	}

	inline void SPIRVAssembler::UseDefaultSetLocation(const uint32_t _uDefaultSet, const uint32_t _uDefaulInputLocation, const uint32_t _uDefaultOutputLocation) noexcept
	{
		m_uDefaultSet = _uDefaultSet;
		m_uCurrentInputLocation = _uDefaulInputLocation;
		m_uCurrentOutputLocation = _uDefaultOutputLocation;
	}

	inline void SPIRVAssembler::UseDefaultSpecConstId(const uint32_t _uStartId) noexcept
	{
		m_uCurrentSpecConstId = _uStartId;
	}

	inline void SPIRVAssembler::UseDefaultInputAttachmentIndex(const uint32_t _uStartIndex) noexcept
	{
		m_uCurrentInputAttachmentIndex = _uStartIndex;
	}

	inline void SPIRVAssembler::ConfigureOptimization(const OptimizationSettings & _Settings)
	{
		m_OptSettings = _Settings;
	}

	inline void SPIRVAssembler::RemoveUnusedOperations(const bool _bEnable) noexcept
	{
		m_bRemoveUnused = _bEnable;
	}

	inline bool SPIRVAssembler::GetRemoveUnusedOperations() const noexcept
	{
		return m_bRemoveUnused;
	}

	inline void SPIRVAssembler::EnterScope()
	{
		++m_uScopeID;
		++m_uScopeLevel;
	}

	inline void SPIRVAssembler::LeaveScope()
	{
		--m_uScopeLevel;
	}

	inline const uint32_t& SPIRVAssembler::GetScopeLevel() const
	{
		return m_uScopeLevel;
	}

	inline const uint32_t& SPIRVAssembler::GetScopeID() const
	{
		return m_uScopeID;
	}

	inline const uint32_t& SPIRVAssembler::GetDefaultSet() const noexcept
	{
		return m_uDefaultSet;
	}

	inline const uint32_t SPIRVAssembler::GetCurrentBinding(const uint32_t _uSet)
	{
		// TODO: assert if to high
		auto it = m_Bindings.find(_uSet);
		if (it != m_Bindings.end())
		{
			return it->second++;
		}
		else
		{
			m_Bindings.insert({ _uSet, 1 });
			return 0u;
		}
	}

	inline const uint32_t SPIRVAssembler::GetCurrentInputLocation() noexcept
	{
		// TODO: assert if to high
		return m_uCurrentInputLocation++;
	}

	inline const uint32_t SPIRVAssembler::GetCurrentOutputLocation() noexcept
	{
		// TODO: assert if to high
		return m_uCurrentOutputLocation++;
	}

	inline const uint32_t SPIRVAssembler::GetCurrentSpecConstId() noexcept
	{
		return m_uCurrentSpecConstId++;
	}

	inline const uint32_t SPIRVAssembler::GetCurrentInputAttchmentIndex() noexcept
	{
		return m_uCurrentInputAttachmentIndex++;
	}

#ifndef GlobalAssembler
#define GlobalAssembler (Spear::SPIRVAssembler::Instance())
#endif

	template<class TProg, class ...Ts>
	inline void SPIRVAssembler::InitializeProgram(Ts&& ..._args)
	{
		constexpr bool bAssemble = std::is_base_of_v<SPIRVProgram<true>, TProg>;
		constexpr bool bExecute = std::is_base_of_v<SPIRVProgram<false>, TProg>;

		if constexpr(bAssemble)
		{
			m_Mutex.lock();
			m_pAssembleProgram = std::make_unique<TProg>(std::forward<Ts>(_args)...);
			Init(m_pAssembleProgram);
		}
		else if constexpr(bExecute)
		{
			m_pExecuteProgram = std::make_unique<TProg>(std::forward<Ts>(_args)...);
		}
	}

	template<class TProg, class ...Ts>
	inline void SPIRVAssembler::RecordInstructions(Ts&& ..._args)
	{
		HASSERT(m_pAssembleProgram != nullptr || m_pExecuteProgram != nullptr, "Invalid program (InitializeProgram not called)");
		
		if (m_pAssembleProgram)
		{
			m_pAssembleProgram->Execute<TProg>(std::forward<Ts>(_args)...);
			m_pAssembleProgram.reset(); // destroy prog here to record variable destructors
		}
		else if (m_pExecuteProgram)
		{
			m_pExecuteProgram->Execute<TProg>(std::forward<Ts>(_args)...);
			m_pExecuteProgram.reset();
		}
	}

	template<class TProg, class ...Ts>
	inline SPIRVModule SPIRVAssembler::AssembleSimple(const bool _bUseDefaults,	Ts&& ..._args)
	{
		if (_bUseDefaults)
		{
			SetDefaults();
		}

		InitializeProgram<TProg>(std::forward<Ts>(_args)...);
		RecordInstructions<TProg>();

		constexpr bool bAssemble = std::is_base_of_v<SPIRVProgram<true>, TProg>;

		if constexpr(bAssemble)
			return Assemble();
		else
			return SPIRVModule(0);
	}

    template<class ...Ts>
    inline uint32_t SPIRVAssembler::EmplaceOperation(Ts&& ..._args)
    {
        m_Operations.emplace_back(std::forward<Ts>(_args)...).m_uInstrId = m_uInstrId;
        return m_uInstrId++;
    }

	template<class Fn, class Pred>
	inline void SPIRVAssembler::ForEachOp(const Fn& _fn, const Pred& _Pred)
	{
		for (SPIRVOperation& Op : m_Operations)
		{
			if (_Pred(Op.GetOpCode()))
			{
				_fn(Op);
			}
		}
	}

	template<class Fn, class Pred>
	inline void SPIRVAssembler::ForEachOpEx(const Fn& _fn, const Pred& _Pred)
	{
		for (SPIRVOperation& Op : m_Operations)
		{
			if (_Pred(Op))
			{
				_fn(Op);
			}
		}
	}
} // Spear

#endif // !SPEAR_SPIRVASSEMBLER_H
