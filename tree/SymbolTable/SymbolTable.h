#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "table.h"
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
    CTable(const CTable&) = delete;
    CTable(){}

private:
    CClassInfo* getClassInfo(std::string className);
    CMethodInfo* getMethodInfo(std::string methodName);
    void checkClass(CClassInfo* classToCheck);
    std::vector<CClassInfo*> getChain(CClassInfo* newClass);
    std::vector<std::shared_ptr<CScope> > scopes;
    std::unordered_map<CInternSymbol*, std::shared_ptr<CClassInfo> > classes;
    std::set<CInternSymbol*> checked;
};

}

#endif // SYMBOLTABLE_H
