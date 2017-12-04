#include "SymbolTable.h"


#include <string>
#include <vector>
#include <unordered_map>
#include <assert.h>

namespace STable {

void CTable::AddClass(CClassInfo *newClass){
    if (classes.find(newClass->GetName()) == classes.end()){
        classes[newClass->GetName()] = std::shared_ptr<CClassInfo>(newClass);

    }
    else{
        //already declared
    }
}

CClassInfo* CTable::getClassInfo(std::string className){
    CInternSymbol *nameIntern = CInternSymbol::GetIntern(className);
    auto info = classes.find(nameIntern);
    if (info != classes.end()){
        return info->second.get();
    }
    //not declared

}

void CTable::checkClass(CClassInfo *classToCheck){
    if (checked.find(classToCheck->GetName()) != checked.end()){
        return;
    }
    std::set<CInternSymbol*> chain;
    for(auto class_ = classToCheck; class_->GetSuperClass() != nullptr; class_ = getClassInfo(class_->GetSuperClass()->GetString())) {
            if(chain.find(class_->GetName()) != chain.end()) {
                //cycle
                return;
            }
            chain.insert(classToCheck->GetName());
        }
        for(auto class_ : chain) {
            checked.insert(class_);
        }
}

void CTable::AddNewClass(std::string newClassName){
    CClassInfo* newClass = getClassInfo(newClassName);
    checkClass(newClass);
    std::vector<CClassInfo*> chain;
    chain.push_back(newClass);
    for (CClassInfo* class_ = newClass; class_ != nullptr; class_ = getClassInfo(class_->GetSuperClass()->GetString())){
        chain.push_back(class_);
    }
    for(auto class_ : chain) {
        auto varBlock = class_->GetVarBlock();
        auto methBlock = class_->GetMethodsBlock();
        scopes.push_back(std::shared_ptr<CScope>(new CScope(&varBlock, &methBlock, class_)));
    }
}

CMethodInfo* CTable::getMethodInfo(std::string methodName){
    CInternSymbol* symbol = CInternSymbol::GetIntern(methodName);
    for(auto scope : scopes) {
        auto method = scope.get()->GetMethodsBlock()->find(symbol);
        if(method != scope.get()->GetMethodsBlock()->end()) {
            return method->second.get();
        }
    }
    //not declared
    return nullptr;
}

void CTable::FreeLastScope(){
    assert(scopes.size() > 0);
    scopes.pop_back();
}

void CTable::AddNewMethod(std::string newMethodName){
    CMethodInfo* method = getMethodInfo(newMethodName);
    auto varBlock = method->GetVariablesBlock();
    scopes.push_back(std::shared_ptr<CScope>(new CScope(&varBlock, nullptr, scopes.begin()->get()->GetClassName())));
}

}
