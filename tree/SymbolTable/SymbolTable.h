#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "Scope.h"
#include "ClassInfo.h"
#include "MethodInfo.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

namespace STable {

class CTable {
public:
    void AddClass(CClassInfo* newClass);
    void AddNewClass(std::string neClassName);
    void AddNewMethod(std::string newMethodName);
    void FreeLastScope();

private: 
    CClassInfo* getClassInfo(std::string className);
    CMethodInfo* getMethodInfo(std::string methodName);
    void checkClass(CClassInfo* classToCheck);
    std::vector<CClassInfo*> getChain(CClassInfo* newClass);

    std::vector<std::unique_ptr<CScope> > scopes;
    std::unordered_map<CInternSymbol*, std::unique_ptr<CClassInfo> > classes;
    std::set<CInternSymbol*> checked;
};

}

#endif // SYMBOLTABLE_H
