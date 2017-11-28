#ifndef VARIABLEINFO_H
#define VARIABLEINFO_H

#include "Symbol.h"
#include "TypeInfo.h"

namespace STable {

class CVariableInfo : public CSymbol{
public:
    CVariableInfo(const CVariableInfo&) = delete;
    CVariableInfo(std::string name_, VarType type_): CSymbol(name){
        type = new CTypeInfo(type_);
    }
    CVariableInfo(std::string name_, CTypeInfo* type_):
        CSymbol(name_),
        type(type_)
    {}
    //если пользовательский тип:
    CVariableInfo(std::string name_, VarType type_, std::string className): CSymbol(name){
        type = new CTypeInfo(type_, className);
    }

    CTypeInfo* GetType(){return type;}
private:
    CTypeInfo* type;
};

}

#endif // VARIABLEINFO_H
