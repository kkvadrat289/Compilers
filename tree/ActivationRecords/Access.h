#ifndef ACCESS_H
#define ACCESS_H

#include "../SymbolTable/table.h"
#include "Temp.h"
#include <string>

namespace Records {

enum T_RecordsType {
    RT_Formal,
    RT_Local,
    RT_FramePointer,
    RT_StackPointer,
    RT_AddressExit,
    RT_AddressReturnValue
};


class IAccess {
public:
    virtual ~IAccess() {}
    virtual const T_RecordsType GetRecordType() = 0;
    virtual const int GetSize() const = 0;
    virtual void print(Temp fp) const = 0;
};

}

#endif // ACCESS_H
