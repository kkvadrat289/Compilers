#include "Frame.h"
#include "../SymbolTable/table.h"
#include "Access.h"
#include "InRegAccess.h"
#include "InFrameAccess.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <assert.h>

#include "X86MiniJavaFrame.h"

namespace Records {

static const int MAX_IN_REG = 4;
static const char* const EXIT_ADDRESS_NAME= "@EXIT_ADDRESS@";
static const char* const RETURN_ADDRESS_NAME= "@RETURN_ADDRESS@";

static const int intSize = 1 * X86MiniJavaFrame::WORD_SIZE;
static const int booleanSize = 1 * X86MiniJavaFrame::WORD_SIZE;
static const int refSymbolTableerenceSize = 1 * X86MiniJavaFrame::WORD_SIZE;

int typeSize(STable::VarType type) {
    switch (type) {
        case STable::VarType::T_INT:
            return intSize;
        case STable::VarType::T_INT_ARR:
            return referenceSize;
        case STable::VarType::T_BOOL:
            return booleanSize;
        case STable::VarType::T_CLASS:
            return referenceSize;
        default:
            assert(false);
    }
}

void X86MiniJavaFrame::AddFormal( const STable::CVariableInfo& name) {
    IAccess* var = createFormal(T_RecordsType::RT_Formal, typeSize(name.GetType().GetType()));
    formalAccess.insert(std::make_pair(name.GetName(), std::unique_ptr<IAccess>(var)));
    formalList.push_back(var);
}

void X86MiniJavaFrame::AddLocal( const STable::CVariableInfo& name) {
    IAccess* var = new InFrameAccess(RT_Formal, typeSize(name.GetType().GetType()), localTopPointer );
    localAccess.insert(std::make_pair(name.GetName(), std::unique_ptr<IAccess>(var)));
    localTopPointer += typeSize(name.GetType().GetType());
}

void X86MiniJavaFrame::AddAddressExit() {
    IAccess* var = createFormal(T_RecordsType::RT_AddressExit, referenceSize);
    formalAccess.insert(std::make_pair(STable::CInternSymbol::GetIntern(EXIT_ADDRESS_NAME),
                                       std::unique_ptr<IAccess>(var)));
    this->addressExitIndex = formalList.size();
    formalList.push_back(var);
}

void X86MiniJavaFrame::AddAddressReturnValue(STable::VarType type) {
    IAccess* var = createFormal(T_RecordsType::RT_AddressReturnValue, referenceSize);
    formalAccess.insert(std::make_pair(STable::CInternSymbol::GetIntern(RETURN_ADDRESS_NAME),
                                       std::unique_ptr<IAccess>(var)));
    this->addressReturnValueIndex = formalList.size();
    formalList.push_back(var);
}

int X86MiniJavaFrame::FormalsCount() const {
    return formalList.size();
}

const IAccess* X86MiniJavaFrame::Formal( int index ) const {
    return formalList[index];
}

const IAccess* X86MiniJavaFrame::FindLocalOrFormal( const STable::CInternSymbol* name ) const {
    auto res = localAccess.find(name);
    if( res == localAccess.end() ) {
        res = formalAccess.find(name);
        assert(res != formalAccess.end());
    }
    return res->second.get();
}

const IAccess* X86MiniJavaFrame::ExitAddress() const
{
    return formalList[addressExitIndex];
}

const IAccess* X86MiniJavaFrame::ReturnAddress() const
{
    return formalList[addressReturnValueIndex];
}

const int X86MiniJavaFrame::FormalSize(int index) const {
    return formalList[index]->GetSize();
}

const int X86MiniJavaFrame::FormalSize(const STable::CInternSymbol* name) const {
    auto res = formalAccess.find(name);
    assert(res != formalAccess.end());
    return res->second->GetSize();
}

const STable::CTypeInfo X86MiniJavaFrame::WordType() const
{
    return STable::CTypeInfo(STable::VarType::T_INT);
}

const Temp X86MiniJavaFrame::FP() const {
    return Temp(formalTopPointer);
}

const Temp X86MiniJavaFrame::SP() const
{
    return Temp(FP().GetAddress() + localTopPointer);
}

IAccess* X86MiniJavaFrame::createFormal(T_RecordsType type, int size)
{
    if(formalList.size() < MAX_IN_REG) {
        return new InRegAccess(type, size, formalList.size());
    } else {
        IAccess* access = new InFrameAccess(type, size, formalTopPointer);
        formalTopPointer += size;
        return access;
    }
}

}
