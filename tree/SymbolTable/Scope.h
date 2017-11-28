#ifndef SCOPE_H
#define SCOPE_H
#include <unordered_map>
#include "ClassInfo.h"
#include "MethodInfo.h"

namespace STable {

class CScope
{
public:
    CScope(std::unordered_map<CInternSymbol*, std::unique_ptr<CVariableInfo> >* variablesBlock_ = nullptr,
          std::unordered_map<CInternSymbol*, std::unique_ptr<CMethodInfo> >* methodsBlock_ = nullptr,
          CClassInfo* className_ = nullptr) :
        methodsBlock(methodsBlock_),
        variablesBlock(variablesBlock_),
        className(className_)
    {}

    std::unordered_map<CInternSymbol*, std::unique_ptr<CMethodInfo > >* GetMethodsBlock(){return methodsBlock;}
    std::unordered_map<CInternSymbol*, std::unique_ptr<CVariableInfo> >* GetVariablesBlock(){return variablesBlock;}
    CClassInfo* GetClassName(){return className;}

private:
    std::unordered_map<CInternSymbol*, std::unique_ptr<CMethodInfo> >* methodsBlock;
    std::unordered_map<CInternSymbol*, std::unique_ptr<CVariableInfo> >* variablesBlock;
    CClassInfo* className;
};

}

#endif // SCOPE_H
