#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <vector>
#include <string>
#include <unordered_map>
#include "InternSymbol.h"
#include "VariableInfo.h"
#include "MethodInfo.h"

namespace STable {

class CClassInfo: public CSymbol{
    CClassInfo( std::string name_) :
        CSymbol(name_),
        superClass(nullptr)
    {}

    void AddMethodInfo(const CMethodInfo* method)
    {
          methods.push_back(method->GetName());
          methodsBlock.insert(std::make_pair(method->GetName(), std::unique_ptr<CMethodInfo>(method)));
    }

    void AddVariableInfo(const CVariableInfo* var)
    {
          vars.push_back(var->GetName());
          variablesBlock.insert(std::make_pair(var->GetName(), std::unique_ptr<CVariableInfo>(var)));
    }

    CInternSymbol* GetSuperClass(){
        return superClass;
    }
    void SetSuperClass(std::string& name){
        superClass = CInternSymbol::GetIntern(name);
    }
    void SetSuperClass(CInternSymbol* name){
        superClass = name;
    }

    std::vector<CInternSymbol*> GetVars(){
        return vars;
    }
    std::vector<CInternSymbol*> GetMethods(){
        return methods;
    }


private:
    std::vector<CInternSymbol*> vars;
    std::vector<CInternSymbol*> methods;
    std::unordered_map<CInternSymbol*, std::unique_ptr<CVariableInfo>> variablesBlock;
    std::unordered_map<CInternSymbol*, std::unique_ptr<CMethodInfo>> methodsBlock;
    CInternSymbol* superClass;
};

}

#endif // CLASSINFO_H
