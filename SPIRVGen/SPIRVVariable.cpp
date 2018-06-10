//Copyright(c) 2018
//Authors: Fabian Wahlster
//Website: https://twitter.com/singul4rity
//Contact: f.wahlster@tum.de
//License: MIT with attribution (see LICENSE.txt)

#include "SPIRVVariable.h"

using namespace Spear;

void var_decoration<true>::Decorate(const SPIRVDecoration& _Decoration)
{
	Decorations.push_back(_Decoration);
}
//---------------------------------------------------------------------------------------------------
void var_decoration<true>::MaterializeDecorations() const
{
	// TODO: materialize decorations of base variables too!

	if (uVarId == HUNDEFINED32)
		return;

	GlobalAssembler.AddVariableInfo(*this);

	// instantiate variable decorations
	for (const SPIRVDecoration& Decoration : Decorations)
	{
		GlobalAssembler.AddOperation(Decoration.MakeOperation(uMemberIndex == HUNDEFINED ? uVarId : uBaseTypeId, uMemberIndex));
	}
	Decorations.clear();

	// instantiate variable name

	if (sName.empty() == false && bMaterializedName == false)
	{
		if (uMemberIndex == HUNDEFINED32)
		{
			SPIRVOperation OpName(spv::OpName);
			OpName.AddLiteral(uVarId);
			OpName.AddLiterals(MakeLiteralString(sName));
			GlobalAssembler.AddOperation(std::move(OpName));
		}
		else
		{
			SPIRVOperation OpName(spv::OpMemberName);
			OpName.AddIntermediate(uBaseTypeId);
			OpName.AddLiteral(uMemberIndex);
			OpName.AddLiterals(MakeLiteralString(sName));
			GlobalAssembler.AddOperation(std::move(OpName));
		}

		bMaterializedName = true;
	}
}
//---------------------------------------------------------------------------------------------------
void var_decoration<true>::Store() const
{
	// store the lastest intermediate result
#ifdef HDIRECT_MEMACCESS
	if (uVarId != HUNDEFINED32 &&
        uResultId != HUNDEFINED32 &&
		uResultId != uLastStoreId)
    {
        uLastStoreId = uResultId;
#else
    if (uVarId != HUNDEFINED32 && uResultId != HUNDEFINED32 &&
        (kStorageClass != spv::StorageClassUniformConstant &&
            kStorageClass != spv::StorageClassInput &&
            kStorageClass != spv::StorageClassPushConstant))
    {
		const uint32_t uScopeLevel = GlobalAssembler.GetScopeLevel();
		const uint32_t uScopeID = GlobalAssembler.GetScopeID();

		// check if we can skip the store
		for (auto it = MemAccess.rbegin(); it != MemAccess.rend(); ++it)
		{
			const LSInfo& LS(*it);
			if ((LS.uResultId == uResultId && LS.kType == kLSType_Store) && // this result has been stored
				(LS.uScopeId == uScopeID || LS.uScopeLevel <= uScopeLevel)) // in a preceding scope
			{
				return;
			}
		}

        // save store info
        LSInfo& LD = MemAccess.emplace_back();
        LD.kType = kLSType_Store;
        LD.uScopeId = uScopeID;
        LD.uScopeLevel = uScopeLevel;
        LD.uResultId = uResultId;
#endif

		// create store
		GlobalAssembler.AddOperation(SPIRVOperation(spv::OpStore,
		{
			SPIRVOperand(kOperandType_Intermediate, uVarId), // destination
			SPIRVOperand(kOperandType_Intermediate, uResultId) // source
		}));

		MaterializeDecorations();
	}
}
//---------------------------------------------------------------------------------------------------

void var_decoration<true>::CreateAccessChain() const
{
	// create access chain for structures and composite types
	if (uVarId == HUNDEFINED32 && uBaseId != HUNDEFINED32 && AccessChain.empty() == false)
	{
		const uint32_t uPtrTypeId = GlobalAssembler.AddType(SPIRVType::Pointer(Type, kStorageClass));
		SPIRVOperation OpAccessChain(spv::OpAccessChain, uPtrTypeId, SPIRVOperand(kOperandType_Intermediate, uBaseId));

		for (const uint32_t& uMemberIdx : AccessChain)
		{
			OpAccessChain.AddIntermediate(GlobalAssembler.AddConstant(SPIRVConstant::Make(uMemberIdx)));
		}

		uVarId = GlobalAssembler.AddOperation(std::move(OpAccessChain));
	}
}
//---------------------------------------------------------------------------------------------------

uint32_t var_decoration<true>::Load() const
{
	HASSERT(uTypeId != HUNDEFINED32, "Invalid TypeId");

	CreateAccessChain();

	// instantiate variable decorations
	MaterializeDecorations();

#ifdef HDIRECT_MEMACCESS
    if (uResultId != HUNDEFINED32) // its an intermediate
        return uResultId;
#else
	if (uResultId != HUNDEFINED32 && uVarId == HUNDEFINED32) // its an intermediate
		return uResultId;

	const uint32_t uScopeLevel = GlobalAssembler.GetScopeLevel();
	const uint32_t uScopeID = GlobalAssembler.GetScopeID();

	// search for last memory access in parent/same scope
	for (auto it = MemAccess.rbegin(); it != MemAccess.rend(); ++it)
	{
		const LSInfo& LS(*it);
		if (LS.uScopeId == uScopeID || LS.uScopeLevel <= uScopeLevel)
		{
			return LS.uResultId;
		}
	}
#endif

	HASSERT(uVarId != HUNDEFINED32, "Invalid variable id");

	// OpLoad:
	// Result Type is the type of the loaded object.
	// Pointer is the pointer to load through. Its type must be an OpTypePointer whose Type operand is the same as ResultType.
	// Memory Access must be a Memory Access literal. If not present, it is the same as specifying None.
	// bsp: None, Volatile, Aligned, Nontemporal

	uResultId = GlobalAssembler.EmplaceOperation(spv::OpLoad, uTypeId, SPIRVOperand(kOperandType_Intermediate, uVarId));

#ifdef HDIRECT_MEMACCESS
    uLastStoreId = uResultId;
#else
	LSInfo& LD = MemAccess.emplace_back();
	LD.kType = kLSType_Load;
	LD.uScopeId = uScopeID;
	LD.uScopeLevel = uScopeLevel;
	LD.uResultId = uResultId;
#endif

	return uResultId;
}
//---------------------------------------------------------------------------------------------------
var_decoration<true>::var_decoration(const var_decoration<true>& _Other) :
	uVarId(_Other.uVarId),
	uResultId(_Other.uResultId),
	uBaseId(_Other.uBaseId),
	kStorageClass(_Other.kStorageClass),
	uTypeId(_Other.uTypeId),
	AccessChain(_Other.AccessChain),
	Type(_Other.Type),
#ifndef HDIRECT_MEMACCESS
	MemAccess(_Other.MemAccess),
#endif
	Decorations(_Other.Decorations)
{
	// TODO: copy descriptorset and others?
}
//---------------------------------------------------------------------------------------------------

var_decoration<true>::var_decoration(var_decoration<true>&& _Other) noexcept:
	uVarId(_Other.uVarId),
	uResultId(_Other.uResultId),
	uBaseId(_Other.uBaseId),
	kStorageClass(_Other.kStorageClass),
	uTypeId(_Other.uTypeId),
	AccessChain(std::move(_Other.AccessChain)),
	Type(std::move(_Other.Type)),
#ifndef HDIRECT_MEMACCESS
	MemAccess(std::move(_Other.MemAccess)),
#endif
	Decorations(std::move(_Other.Decorations))
{
	_Other.uVarId = HUNDEFINED32;
	_Other.uResultId = HUNDEFINED32;
	_Other.uTypeId = HUNDEFINED32;
	_Other.uBaseId = HUNDEFINED32;
}

//---------------------------------------------------------------------------------------------------

const var_decoration<true>& var_decoration<true>::operator=(const var_decoration<true>& _Other) const
{
	if (this == &_Other)
		return *this;

	HASSERT(uTypeId != HUNDEFINED32 && uTypeId == _Other.uTypeId, "Type mismatch!");

	CreateAccessChain(); // creat var id for structs
	_Other.Load();// load source

	if (uVarId != HUNDEFINED32) // this is a mem object (no intermediate)
	{
		uResultId = _Other.uResultId; // get result
		Store(); // store result
	}
	else // intermediate
	{
		uResultId = _Other.uResultId;
		uBaseId = _Other.uBaseId;
	}

	return *this;
}

//---------------------------------------------------------------------------------------------------

var_decoration<true>::~var_decoration()
{
	// store the lastest intermediate result
	Store();
}
//---------------------------------------------------------------------------------------------------
void var_decoration<true>::SetBinding(const uint32_t _uBinding, const uint32_t _uDescriptorSet)
{
	HASSERT(uDescriptorSet == HUNDEFINED32 && uBinding == HUNDEFINED32, "Variable already has a binding");
	Decorate(SPIRVDecoration(spv::DecorationDescriptorSet, _uDescriptorSet));
	Decorate(SPIRVDecoration(spv::DecorationBinding, _uBinding));

	uDescriptorSet = _uDescriptorSet;
	uBinding = _uBinding;
}
//---------------------------------------------------------------------------------------------------

void var_decoration<true>::SetLocation(const uint32_t _uLocation)
{
	HASSERT(uLocation == HUNDEFINED32, "Variable already has a location");
	Decorate(SPIRVDecoration(spv::DecorationLocation, _uLocation));

	uLocation = _uLocation;
}
//---------------------------------------------------------------------------------------------------
void var_decoration<true>::SetName(const std::string& _sName)
{
	sName = _sName;
}
//---------------------------------------------------------------------------------------------------
uint32_t var_decoration<true>::GetLastStore() const
{
#ifdef HDIRECT_MEMACCESS
    return uLastStoreId;
#else
	for (auto it = MemAccess.rbegin(); it != MemAccess.rend(); ++it)
	{
		const LSInfo& LS(*it);
		if (LS.kType == kLSType_Store)
		{
			return LS.uResultId;
		}
	}

	return HUNDEFINED32;
#endif
}
