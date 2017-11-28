#include "SymbolTableVisitor.h"
#include "../SymbolTable/ClassInfo.h"

namespace STable {

CTableVisitor::CTableVisitor(CProgram* program){
    program->accept(this);

}

CTableVisitor::visit(const CProgram *node){
    for (auto item : node->classes){
        item->accept(this);
    }
}

CTableVisitor::visit(const CClass *node){
    CClassInfo* classInfo = new CClassInfo(node->id->name);
    if (node->extends.get() != nullptr)
        classInfo->SetSuperClass(node->extends->name);

    for(auto var : node->vars) {
        CVariableInfo* newVar = new CVariableInfo(var->id->name, convertType(var->type.get()));
        classInfo->AddVariableInfo(newVar);
    }

    for (auto method : node->methods){
        CMethodInfo* methodInfo = new CMethodInfo(method->id->name, convertType(method->type.get()), node->id->name);
        for(auto arg : method->params) {
            methodInfo->AddArg(new CVariableInfo(arg->id->name,convertType(arg->type.get())));
        }

        for(auto var : method->vars) {
            methodInfo->AddVariable(new CVariableInfo(var->id->name, convertType(var->type.get())));
        }
        classInfo->AddMethodInfo(methodInfo);
    }
    table.AddClass(classInfo);
}

CTypeInfo* CTableVisitor::convertType(IType *type){
    std::string label = type->label;
    VarType res;

    switch (label) {
    case "bool":
        res = VarType::T_BOOL;
        break;
    case "int":
        res = VarType::T_INT;
        break;
    case "int[]":
        res = VarType::T_INT_ARR;
        break;
    default:
        res = VarType::T_CLASS;
        break;
    }
    if (res == VarType::T_CLASS){
        return new CTypeInfo(res, label);
    }
    else
        return new CTypeInfo(res);

}

}
