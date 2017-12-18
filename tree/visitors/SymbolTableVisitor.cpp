#include "SymbolTableVisitor.h"
#include "../includes.h"

using namespace TypeChecker;

static STable::CTypeInfo* convertType(const IType* type)
{
    std::string label = type->label;
    STable::VarType res;
    if (label == "bool")
        res = STable::VarType::T_BOOL;
    else if (label == "int")
        res = STable::VarType::T_INT;
    else if (label == "int[]")
        res = STable::VarType::T_INT_ARR;
    else
        res = STable::VarType::T_CLASS;

    if (res == STable::VarType::T_CLASS){
        return new STable::CTypeInfo(res, label);
    }
    else
        return new STable::CTypeInfo(res);
}

inline bool operator ==(const IType &a, const IType &b) {
    return a.label == b.label;
}

void CTypeChecker::Check(CProgram* root, STable::CTable* table)
{
    this->table = table;
    try {
        root->accept(this);
    } catch (DeclarationException e) {
        std::cout << "Declaration error: " << e.what() << std::endl;
    }
}

void CTypeChecker::visit(const CProgram *node)
{
    for (auto class_ : node->classes){
        class_->accept(this);
    }
}

void CTypeChecker::visit(const CClass *node)
{
    table->AddNewClass(node->id->name);
    for (auto method : node->methods){
        method->accept(this);
    }
    table->FreeLastScope();
}

void CTypeChecker::visit(const CVariable* node)
{
    if((node->type->label != BasicType::INT_) && (node->type != BasicType::INT_ARRAY_) &&
            (node->type->label != BasicType::BOOL_)) {
        table->getClassInfo(node->id->name);
    }
}

void CTypeChecker::visit(const CMethod* node)
{
    table->AddNewMethod(node->id->name);
    for (auto arg : node->params){
        arg->accept(this);
    }
    for (auto statement : node->statements){
        statement->accept(this);
    }
    if((node->type->label != BasicType::INT_) && (node->type->label != BasicType::INT_ARRAY_) &&
            (node->type->label != BOOL_)) {
        table->getClassInfo(node->type->label);
    }
    node->res->accept(this);
    auto returnedType = popTypeStack();
    if( !(*returnedType == convertType(node->type.get()))) {
        throw DeclarationException("Trying to return wrong type from method " + node->id->name);
    }
    table->FreeLastScope();
}

/*void CTypeChecker::visit(const IType* node)
{
    if(node->label != BasicType::BOOL_ && node->label != BasicType::INT_ && node->label && BasicType::INT_ARRAY_) {
        table->getClassInfo(node->label);
    }
}*/

void CTypeChecker::visit(const CRandomAccessAssign* node)
{
    auto array = table->getVariableInfo(node->id->name);
    if(array->GetType()->GetType() != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to subscript" + array->GetType()->GetType() + " as array");
    }
    node->position->accept(this);
    auto returned = popTypeStack();
    if(returned->GetType() != BasicType::INT_) {
        throw DeclarationException("Trying to return wrong type as index of array " + node->id->name);
    }
    node->expression->accept(this);
    returned = popTypeStack();
    if(returned->GetType() != BasicType::INT_) {
            throw DeclarationException("Trying to assign wrong type to int array " + node->id->name);
    }
}

void CTypeChecker::visit(const CAssignStatement* node)
{
    auto var = table->getVariableInfo(node->left->name);
    node->right->accept(this);
    auto returnedType = popTypeStack();
    if( !(var->GetType() == *returnedType) ) {
        throw DeclarationException("Trying to assign wrong type to variable " + node->left->name);
    }
}

void CTypeChecker::visit(const CPrintLine* node)
{
    node->object->accept(this); ;
    auto toPrint = popTypeStack();
    if(toPrint->GetType() != BasicType::INT_ && toPrint->GetType() != BasicType::BOOL_ &&
            toPrint->GetType() != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to return wrong user type ");
    }
}

void CTypeChecker::visit(const CWhile* node)
{
    node->cond->accept(this);
    auto returned = popTypeStack();
    if(returned->GetType() != BasicType::BOOL_) {
            throw DeclarationException("Trying to use wrong type as while condition");
    }
    node->action->accept(this);
}

void CTypeChecker::visit(const CStatements* node)
{
    for (auto statement : node->statements){
        statement->accept(this);
    }
}

void CTypeChecker::visit(const CIf* node)
{
    node->cond->accept(this);
    auto returned = popTypeStack();
    if(returned->GetType() != BasicType::BOOL_) {
            throw DeclarationException("Trying to use wrong type as if condition");
    }
    node->ifTrue->accept(this);
    node->ifFalse->accept(this);
}

static STable::CTypeInfo IntType(STable::T_INT);
static STable::CTypeInfo BooleanType(STable::T_BOOL);
static STable::CTypeInfo IntArrayType(STable::T_INT_ARR);

void CTypeChecker::visit(const CBinExpression* node)
{
//    LESS_  = 1,
//    AND_ = 2,
//    OR_ = 3,
//    PLUS_ = 4,
//    MINUS_ = 5,
//    TIMES_ = 6,
//    MOD_ = 7
    node->left->accept(this);
    auto returned = popTypeStack();
    switch (node->type) {
    case BinType::PLUS_:
    case BinType::MINUS_:
    case BinType::TIMES_:
    case BinType::MOD_:
    case BinType::LESS_:
        if(returned->GetType() != BasicType::INT_) {
                throw DeclarationException("Trying to apply math operation to non integer");
        }
        node->right->accept(this);
        returned = popTypeStack();
        if(returned->GetType() != BasicType::INT_) {
                throw DeclarationException("Trying to apply math operation to non integer");
        }
        if(node->type == BinType::LESS_) {
            typesStack.push(&BooleanType);
        } else {
            typesStack.push(&IntType);
        }
        break;
    case BinType::AND_:
    case BinType::OR_:
        if(returned->GetType() != BasicType::BOOL_) {
                throw DeclarationException("Trying to apply logical operation to non bool");
        }
        node->right->accept(this);
        returned = popTypeStack();
        if(returned->GetType() != BasicType::BOOL_) {
                throw DeclarationException("Trying to apply logical operation to non bool");
        }
        typesStack.push(&BooleanType);
    default:
        break;
    }
}

void CTypeChecker::visit(const CRandomAccessAssign* node)
{
    node->expression->accept(this);
    auto returnedBase = popTypeStack();
    if(returnedBase->GetType() != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to use wrong type as array");
    }
    node->position->accept(this);
    auto returned = popTypeStack();
    if(returned->GetType()!= BasicType::INT_) {
        throw DeclarationException("Trying to return non integer type as index of array ");
    }
    typesStack.push(&IntType);
}

void CTypeChecker::visit(const CLength* node)
{
    node->object->accept(this);
    auto returnedBase = popTypeStack();
    if(returnedBase->GetType() != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to use wrong type as array");
    }
    typesStack.push(&IntType);
}

void CTypeChecker::visit(const CCallMethod* node)
{
    node->expression->accept(this);
    auto returnedBase = popTypeStack();
    if(returnedBase->GetType() == BasicType::INT_ || returnedBase->GetType() == BasicType::INT_ARRAY_ ||
            returnedBase->GetType() == BasicType::BOOL_) {
        throw DeclarationException("Trying to use type basic type as user type");
    }
    auto classInfo = table->getClassInfo(returnedBase->GetClassName()->GetString());
    auto methodIterator = classInfo->GetMethodsBlock()->find(STable::CInternSymbol::GetIntern(node->id->name));
    if(methodIterator == classInfo->GetMethodsBlock()->end()) {
        throw DeclarationException("Requested method " + node->id->name + " is not present in class " +
                                                        classInfo->GetName()->GetString());
    }
    const STable::CMethodInfo* methodInfo = methodIterator->second.get();
    for (auto arg : node->params){
        arg->accept(this);
    }
    typesStack.push(&(methodInfo->GetReturnType()));
}

void CTypeChecker::visit(const CBooleanExp* node)
{
    typesStack.push(&IntType);
}

void CTypeChecker::visit(const CIntegerExp* node)
{
    typesStack.push(&BooleanType);
}

void CTypeChecker::visit(const CId* node)
{
    auto var = table->getVariableInfo(node->name);
    typesStack.push(&var->GetType());
}

void CTypeChecker::visit(const CThis* node)
{}

void CTypeChecker::visit(const CNewIntArray* node)
{
    node->size->accept(this);
    auto returned = popTypeStack();
    if(returned->GetType()!= BasicType::INT_) {
        throw DeclarationException("Trying to use non integer type as size of array ");
    }
    typesStack.push(&IntArrayType);
}

void CTypeChecker::visit(const CNewClassObject* node)
{
    auto objectType = table->getClassInfo(node->id->name);
    typesStack.push(&objectType->GetTypeInfo());
}

void CTypeChecker::visit(const CNotExp* node)
{
    node->right->accept(this);
    auto returned = popTypeStack();
    if(returned->GetType() != SymbolTable::VT_Boolean) {
        throw DeclarationException("Trying to use non boolean type as boolean expression ");
    }
    typesStack.push(&BooleanType);
}
void CTypeChecker::visit(const CThis* node){}
void CTypeChecker::visit(const CArg* node){}
void CTypeChecker::visit(const CMain* node){}
void CTypeChecker::visit(const CTrue* node){}
void CTypeChecker::visit(const CFalse* node){}




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

void CTableVisitor::printClassInfo(CClassInfo* classInfo)
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
        auto method = table->GetMethodInfo(name);
        table->AddNewMethod(method->GetName()->GetString());
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

void CTableVisitor::printVariableInfo(CVariableInfo* varInfo)
{
    if (varInfo != nullptr){
        printTypeInfo(varInfo->GetType());
        std::cout << " " << varInfo->GetName()->GetString() ;
    }

}

void CTableVisitor::printTypeInfo(CTypeInfo* type)
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
