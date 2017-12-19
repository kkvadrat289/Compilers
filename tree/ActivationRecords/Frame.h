#ifndef FRAME_H
#define FRAME_H

#include "Access.h"
#include "../SymbolTable/table.h"

namespace Records {

class IFrame {
public:
    virtual ~IFrame() { }

    virtual void AddFormal( const STable::CVariableInfo& var) = 0;
    virtual void AddLocal( const STable::CVariableInfo& var) = 0;
    virtual void AddAddressExit() = 0;
    virtual void AddAddressReturnValue(STable::VarType type) = 0;
    virtual int FormalsCount() const = 0;
    virtual const IAccess* Formal( int index ) const = 0;
    virtual const IAccess* FindLocalOrFormal( const STable::CInternSymbol* symbol ) const = 0;
    virtual const IAccess* ExitAddress() const = 0;
    virtual const IAccess* ReturnAddress() const = 0;
    virtual const Temp FP() const = 0;
    virtual const Temp SP() const = 0;
    virtual const STable::CTypeInfo WordType() const = 0;
};

}


#endif // FRAME_H
