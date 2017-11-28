#ifndef TYPEINFO_H
#define TYPEINFO_H

#include "InternSymbol.h"

namespace STable {

class CTypeInfo {
public:
    CTypeInfo(VarType type_, CInternSymbol* userClass_ = nullptr):
        type(type_)
    {
        if (type == VarType::T_CLASS){
            userClass = userClass_;
        }
    }
    CTypeInfo(VarType type, std::string userClass):
        type(type_)
    {
        if(type == VarType::T_CLASS) {
            userClass = CInternSymbol::GetIntern(userClass);
        }
    }

    CInternSymbol* GetClassName(){return userClass;}
    VarType GetType(){return type;}
private:
    VarType type;
    CInternSymbol* userClass;
};

}

#endif // TYPEINFO_H
