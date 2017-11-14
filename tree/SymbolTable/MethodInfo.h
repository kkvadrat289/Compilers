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
    CMethodInfo(std::string name_, VarType returnType_):CSymbol(name_), returnType(returnType_){}
    VarType GetType(){
        return returnType;
    }
    void AddVariable(CVariableInfo* var){
        vars.push_back(var->GetName());
        variablesBlock.insert(var->GetName(), std::unique_ptr<CVariableInfo>(var));
    }

    void AddArg(CVariableInfo *arg){
        args.push_back(arg->GetName());
        variablesBlock.insert(arg->GetName(), std::unique_ptr<CVariableInfo>(arg));
    }

    CVariableInfo* GetVariableInfo(CInternSymbol *name){
        CVariableInfo *res = variablesBlock.find(name)->second.get();
        if (res == nullptr){
            //exception
        }
        return res;
    }

private:
    std::vector<CInternSymbol*> args;
    std::vector<CInternSymbol*> vars;
    VarType returnType;
    std::unordered_map<CInternSymbol*, std::unique_ptr<CVariableInfo>> variablesBlock;
};

}


#endif // METHODINFO_H
