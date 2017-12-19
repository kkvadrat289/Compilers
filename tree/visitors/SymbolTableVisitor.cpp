#include "SymbolTableVisitor.h"
#include "../includes.h"

using namespace STable;

CTableVisitor::CTableVisitor(){
    table = new CTable();
}

CTableVisitor::CTableVisitor(CProgram* program){
    program->accept(this);
}

void CTableVisitor::visit(const CProgram *node){
    for (auto item : node->classes){
        item->accept(this);
    }
}

void CTableVisitor::visit(const CMethod *node){}

void CTableVisitor::visit(const CClass *node){
    CClassInfo* classInfo = new CClassInfo(node->id->name, node->pos);
    if (node->extends.get() != nullptr)
        classInfo->SetSuperClass(node->extends->name);
    for(auto var : node->vars) {
        CVariableInfo* newVar = new CVariableInfo(var->id->name, convertType(var->type.get()), node->pos);
        classInfo->AddVariableInfo(newVar);
    }
    for (auto method : node->methods){
        CMethodInfo* methodInfo = new CMethodInfo(method->id->name, convertType(method->type.get()), node->id->name, node->pos);
        for(auto arg : method->params) {
            methodInfo->AddArg(new CVariableInfo(arg->id->name,convertType(arg->type.get()), node->pos));
        }
        for(auto var : method->vars) {
            methodInfo->AddVariable(new CVariableInfo(var->id->name, convertType(var->type.get()), node->pos));
        }
        classInfo->AddMethodInfo(methodInfo);
    }
    table->AddClass(classInfo);
}

void CTableVisitor::FillTable(CProgram* program){
    program->accept(this);
}

CTypeInfo* CTableVisitor::convertType(const IType *type){
    std::string label = type->label;
    VarType res;

    if (label == "bool")
        res = VarType::T_BOOL;
    else if (label == "int")
        res = VarType::T_INT;
    else if (label == "int[]")
        res = VarType::T_INT_ARR;
    else
        res = VarType::T_CLASS;

    if (res == VarType::T_CLASS){
        return new CTypeInfo(res, label);
    }
    else
        return new CTypeInfo(res);

}

void CTableVisitor::printClassInfo(CClassInfo* classInfo) const
{
    if(classInfo->GetSuperClass() != nullptr) {
        std::cout << "  Super: " << classInfo->GetSuperClass()->GetString() << std::endl;
        auto superClass = table->getClassInfo(classInfo->GetSuperClass()->GetString());
        printClassInfo(superClass);
    }

    for(auto varName : classInfo->GetVars())
    {
        std::cout << "\t";
        std::string str = varName->GetString();
        auto variable = table->getVariableInfo(str);
        printVariableInfo(variable);
    }
    std::cout << "\tMethods:\n";
    for(auto methodName : classInfo->GetMethods()) {
        std::cout << "\t\t";
        std::string name = methodName->GetString();
        auto method = table->GetMethodInfo(name, Position(0,0));
        table->AddNewMethod(method->GetName()->GetString(), Position(0,0));
        printTypeInfo(method->GetReturnType());
        std::cout << method->GetName()->GetString() << std::endl << "\t\t\tArgs:";
        for(auto arg : method->args) {
            std::string str = arg->GetString();
            auto var = table->getVariableInfo(str);
            std::cout << "\t";
            printVariableInfo(var);
        }
        std::cout << "\n\t\t\tLocal vars:" ;
        for(auto var : method->vars) {
            std::string str =var-> GetString();
            auto varInfo = table->getVariableInfo(str);
            std::cout  << std::endl << "\t\t\t\t";
            printVariableInfo(varInfo);
        }
        std::cout << std::endl;
        table->FreeLastScope();
    }
}

void CTableVisitor::printVariableInfo(CVariableInfo* varInfo) const
{
    if (varInfo != nullptr){
        printTypeInfo(varInfo->GetType());
        std::cout << " " << varInfo->GetName()->GetString() ;
    }

}

void CTableVisitor::printTypeInfo(CTypeInfo* type) const
{
    switch (type->GetType()) {
    case T_INT:
        std::cout << "int ";
        break;
    case T_INT_ARR:
        std::cout << "int[] ";
        break;
    case T_BOOL:
        std::cout << "boolean ";
        break;
    case T_CLASS:
        std::cout << "class " << type->GetClassName()->GetString();
        break;
    default:
        break;
    }
}

void CTableVisitor::ParseProgram(CProgram* program)
{
    program->accept(this);
    for(auto className : table->GetClassesNames())
    {

            std::string name = className->GetString();
            std::cout << "class " << name << ":" << std::endl;
            auto classInfo = table->getClassInfo(name);
            table->AddNewClass(name);
            printClassInfo(classInfo);
            table->FreeLastScope();
            std::cout << std::endl;
    }
}
