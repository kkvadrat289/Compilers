#ifndef VARIABLEINFO_H
#define VARIABLEINFO_H

#include "Symbol.h"

namespace STable {

class CVariableInfo : public CSymbol{
public:
    CVariableInfo(std::string name_, VarType type_): CSymbol(name), type(type_){}
    CVariableInfo(std::string name_, VarType type_, std::string className): CSymbol(name), type(type_), userClass(className){}
    VarType GetType(){return userClass;}
private:
    VarType type;
    CSymbol* userClass;
};

}

#endif // VARIABLEINFO_H
