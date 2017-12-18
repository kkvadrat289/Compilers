#include "TypeCheckVisitor.h"

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

static BasicType convertType(const STable::CTypeInfo *type){
    if (type->GetType() == STable::VarType::T_BOOL){
        return BasicType::BOOL_;
    }
    else if (type->GetType() == STable::VarType::T_INT){
        return BasicType::INT_;
    }
    else if (type->GetType() == STable::VarType::T_INT_ARR){
        return BasicType::INT_ARRAY_;
    }
    return BasicType::NON_BASIC;
}

static BasicType convertType(const STable::VarType type){
    if (type == STable::VarType::T_BOOL){
        return BasicType::BOOL_;
    }
    else if (type == STable::VarType::T_INT){
        return BasicType::INT_;
    }
    else if (type == STable::VarType::T_INT_ARR){
        return BasicType::INT_ARRAY_;
    }
    return BasicType::NON_BASIC;
}

static std::string ToString(const STable::CTypeInfo *type){
    if (type->GetType() == STable::VarType::T_BOOL){
        return "bool";
    }
    else if (type->GetType() == STable::VarType::T_INT){
        return "int";
    }
    else if (type->GetType() == STable::VarType::T_INT_ARR){
        return "int[]";
    }
    return "user class";
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

void CTypeChecker::visit(const CMain *node){
    for (auto statement : node->statements){
        statement->accept(this);
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
    if((node->type.get()->label != "int") && (node->type.get()->label != "int[]") &&
            (node->type.get()->label != "bool")) {
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
    if((node->type->label != "int") && (node->type->label != "int[]") &&
            (node->type->label != "bool")) {
        table->getClassInfo(node->type->label);
    }
    node->res->accept(this);
    auto returnedType = popTypeStack();
    if( !(*returnedType == *convertType(node->type.get()))) {
        throw DeclarationException("Trying to return wrong type from method " + node->id->name);
    }
    table->FreeLastScope();
}

void CTypeChecker::visit(const CClassType* node)
{
    table->getClassInfo(node->label);

}

void CTypeChecker::visit(const CAssignStatement* node)
{
    auto var = table->getVariableInfo(node->left->name);
    node->right->accept(this);
    auto returnedType = popTypeStack();
    if( !(*(var->GetType()) == *returnedType) ) {
        throw DeclarationException("Trying to assign wrong type to variable " + node->left->name);
    }
}

void CTypeChecker::visit(const CPrintLine* node)
{
    node->object->accept(this); ;
    auto toPrint = popTypeStack();
    if(convertType(toPrint->GetType()) != BasicType::INT_ && convertType(toPrint->GetType()) != BasicType::BOOL_ &&
            convertType(toPrint->GetType()) != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to return wrong user type ");
    }
}

void CTypeChecker::visit(const CWhile* node)
{
    node->cond->accept(this);
    auto returned = popTypeStack();
    if(convertType(returned->GetType()) != BasicType::BOOL_) {
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
    if(convertType(returned->GetType()) != BasicType::BOOL_) {
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
        if(convertType(returned->GetType() )!= BasicType::INT_) {
                throw DeclarationException("Trying to apply math operation to non integer");
        }
        node->right->accept(this);
        returned = popTypeStack();
        if(convertType(returned->GetType()) != BasicType::INT_) {
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
        if(convertType(returned->GetType()) != BasicType::BOOL_) {
                throw DeclarationException("Trying to apply logical operation to non bool");
        }
        node->right->accept(this);
        returned = popTypeStack();
        if(convertType(returned->GetType()) != BasicType::BOOL_) {
                throw DeclarationException("Trying to apply logical operation to non bool");
        }
        typesStack.push(&BooleanType);
    default:
        break;
    }
}

void CTypeChecker::visit(const CRandomAccessAssign* node)
{
    auto array = table->getVariableInfo(node->id->name);
    if(convertType(array->GetType()) != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to subscript" + ToString(array->GetType()) + " as array");
    }
    node->position->accept(this);
    auto returned = popTypeStack();
    if(convertType(returned->GetType()) != BasicType::INT_) {
        throw DeclarationException("Trying to return wrong type as index of array " + node->id->name);
    }
    node->expression->accept(this);
    returned = popTypeStack();
    if(convertType(returned->GetType()) != BasicType::INT_) {
            throw DeclarationException("Trying to assign wrong type to int array " + node->id->name);
    }
}

void CTypeChecker::visit(const CRandomAccess* node)
{
    node->object->accept(this);
    auto returnedBase = popTypeStack();
    if(convertType(returnedBase->GetType()) != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to use wrong type as array");
    }
    node->position->accept(this);
    auto returned = popTypeStack();
    if(convertType(returned->GetType())!= BasicType::INT_) {
        throw DeclarationException("Trying to return non integer type as index of array ");
    }
    typesStack.push(&IntType);
}

void CTypeChecker::visit(const CLength* node)
{
    node->object->accept(this);
    auto returnedBase = popTypeStack();
    if(convertType(returnedBase->GetType()) != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to use wrong type as array");
    }
    typesStack.push(&IntType);
}

void CTypeChecker::visit(const CCallMethod* node)
{
    node->expression->accept(this);
    auto returnedBase = popTypeStack();
    if(convertType(returnedBase->GetType()) == BasicType::INT_ || convertType(returnedBase->GetType()) == BasicType::INT_ARRAY_ ||
            convertType(returnedBase->GetType()) == BasicType::BOOL_) {
        throw DeclarationException("Trying to use type basic type as user type");
    }
    STable::CClassInfo* classInfo = table->getClassInfo(returnedBase->GetClassName()->GetString());
    auto methodIterator = classInfo->GetMethodsBlock()->find(STable::CInternSymbol::GetIntern(node->id->name));
    if(methodIterator == classInfo->GetMethodsBlock()->end()) {
        throw DeclarationException("Requested method " + node->id->name + " is not present in class " +
                                                        classInfo->GetName()->GetString());
    }
    const STable::CMethodInfo* methodInfo = methodIterator->second.get();
    for (auto arg : node->params){
        arg->accept(this);
    }
    typesStack.push(methodInfo->GetReturnType());
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
    STable::CVariableInfo* var = table->getVariableInfo(node->name);
    typesStack.push(var->GetType());
}

void CTypeChecker::visit(const CThis* node)
{}

void CTypeChecker::visit(const CNewIntArray* node)
{
    node->size->accept(this);
    auto returned = popTypeStack();
    if(convertType(returned->GetType()) != BasicType::INT_) {
        throw DeclarationException("Trying to use non integer type as size of array ");
    }
    typesStack.push(&IntArrayType);
}

void CTypeChecker::visit(const CNewClassObject* node)
{
    STable::CClassInfo* objectType = table->getClassInfo(node->id->name);
    typesStack.push(objectType->GetTypeInfo());
}

void CTypeChecker::visit(const CNotExp* node)
{
    node->right->accept(this);
    auto returned = popTypeStack();
    if(convertType(returned->GetType()) != BasicType::BOOL_) {
        throw DeclarationException("Trying to use non boolean type as boolean expression ");
    }
    typesStack.push(&BooleanType);
}

void CTypeChecker::visit(const CArg* node){}
void CTypeChecker::visit(const CTrue* node){}
void CTypeChecker::visit(const CFalse* node){}



