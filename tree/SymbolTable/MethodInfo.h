#ifndef METHODINFO_H
#define METHODINFO_H

#include <vector>
#include <unordered_map>
#include "InternSymbol.h"
#include "Symbol.h"
#include "VariableInfo.h"

namespace  STable {

class CMethodInfo: public CSymbol
{
public:
    CMethodInfo(const CMethodInfo&) = delete;
    CMethodInfo(std::string name_, CTypeInfo* returnType_, std::string& className_):
        CSymbol(name_),
        returnType(returnType_),
        className(CInternSymbol::GetIntern(className_))
    {}
    CTypeInfo* GetType(){
        return returnType;
    }
    void AddVariable(CVariableInfo* var){
        vars.push_back(var->GetName());
        variablesBlock[var->GetName()] = std::unique_ptr<CVariableInfo>(var);
    }

    void AddArg(CVariableInfo *arg){
        args.push_back(arg->GetName());
        variablesBlock[arg->GetName()] = std::unique_ptr<CVariableInfo>(arg);
    }

    CVariableInfo* GetVariableInfo(CInternSymbol *name){
        CVariableInfo *res = variablesBlock.find(name)->second.get();
        if (res == nullptr){
            //exception
        }
        return res;
    }

    std::unordered_map<CInternSymbol*, std::unique_ptr<CVariableInfo> > GetVariablesBlock(){
        return variablesBlock;
    }

    CInternSymbol* GetClassName(){
        return className;
    }

private:
    CInternSymbol* className;
    std::vector<CInternSymbol*> args;
    std::vector<CInternSymbol*> vars;
    CTypeInfo* returnType;
    std::unordered_map<CInternSymbol*, std::unique_ptr<CVariableInfo> > variablesBlock;
};

}


#endif // METHODINFO_H
