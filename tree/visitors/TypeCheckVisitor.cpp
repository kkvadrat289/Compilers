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

static std::string ToString(const STable::VarType type){
    if (type == STable::VarType::T_BOOL){
        return "bool";
    }
    else if (type == STable::VarType::T_INT){
        return "int";
    }
    else if (type == STable::VarType::T_INT_ARR){
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
        throw DeclarationException("Trying to return " + node->type->label +  " from method " + node->id->name);
    }
    table->FreeLastScope();
}

void CTypeChecker::visit(const CAssignStatement* node)
{
    auto var = table->getVariableInfo(node->left->name);
    node->right->accept(this);
    auto returnedType = popTypeStack();
    if( !(convertType(var->GetType()) == convertType(returnedType->GetType())) ) {
        throw DeclarationException("Trying to assign " + ToString(returnedType->GetType()) + " to variable " + node->left->name +
                                   " of type " + ToString(var->GetType()));
    }
}

void CTypeChecker::visit(const CPrintLine* node)
{
    node->object->accept(this); ;
    auto toPrint = popTypeStack();
    if(convertType(toPrint->GetType()) != BasicType::INT_ && convertType(toPrint->GetType()) != BasicType::BOOL_ &&
            convertType(toPrint->GetType()) != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to return wrong user type " + toPrint->GetClassName()->GetString());
    }
}

void CTypeChecker::visit(const CWhile* node)
{
    node->cond->accept(this);
    auto returned = popTypeStack();
    if(convertType(returned->GetType()) != BasicType::BOOL_) {
            throw DeclarationException("Trying to use " + ToString(returned->GetType()) + " type as while condition");
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
            throw DeclarationException("Trying to use " + ToString(returned->GetType()) + " type as if condition");
    }
    node->ifTrue->accept(this);
    node->ifFalse->accept(this);
}

static STable::CTypeInfo IntType(STable::T_INT);
static STable::CTypeInfo BoolType(STable::T_BOOL);
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
                throw DeclarationException("Trying to apply math operation to " + ToString(returned->GetType()));
        }
        node->right->accept(this);
        returned = popTypeStack();
        if(convertType(returned->GetType()) != BasicType::INT_) {
                throw DeclarationException("Trying to apply math operation to " + ToString(returned->GetType()));
        }
        if(node->type == BinType::LESS_) {
            typesStack.push(&BoolType);
        } else {
            typesStack.push(&IntType);
        }
        break;
    case BinType::AND_:
    case BinType::OR_:
        if(convertType(returned->GetType()) != BasicType::BOOL_) {
                throw DeclarationException("Trying to apply logical operation to " + ToString(returned->GetType()));
        }
        node->right->accept(this);
        returned = popTypeStack();
        if(convertType(returned->GetType()) != BasicType::BOOL_) {
                throw DeclarationException("Trying to apply logical operation to " + ToString(returned->GetType()));
        }
        typesStack.push(&BoolType);
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
        throw DeclarationException("Trying to return " + ToString(returned->GetType()) + " as index of array " + node->id->name);
    }
    node->expression->accept(this);
    returned = popTypeStack();
    if(convertType(returned->GetType()) != BasicType::INT_) {
            throw DeclarationException("Trying to assign " + ToString(returned->GetType()) + " to int array " + node->id->name);
    }
}

void CTypeChecker::visit(const CRandomAccess* node)
{
    node->object->accept(this);
    auto returnedBase = popTypeStack();
    if(convertType(returnedBase->GetType()) != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to use " + ToString(returnedBase->GetType()) + " as array");
    }
    node->position->accept(this);
    auto returned = popTypeStack();
    if(convertType(returned->GetType())!= BasicType::INT_) {
        throw DeclarationException("Trying to return " + ToString(returned->GetType()) + " type as index of array ");
    }
    typesStack.push(&IntType);
}

void CTypeChecker::visit(const CLength* node)
{
    node->object->accept(this);
    auto returnedBase = popTypeStack();
    if(convertType(returnedBase->GetType()) != BasicType::INT_ARRAY_) {
        throw DeclarationException("Trying to use " + ToString(returnedBase->GetType()) + " as array");
    }
    typesStack.push(&IntType);
}

void CTypeChecker::visit(const CCallMethod* node)
{
    node->expression->accept(this);
    auto returnedBase = popTypeStack();
    if(convertType(returnedBase->GetType()) == BasicType::INT_ || convertType(returnedBase->GetType()) == BasicType::INT_ARRAY_ ||
            convertType(returnedBase->GetType()) == BasicType::BOOL_) {
        throw DeclarationException("Trying to use type " + ToString(returnedBase->GetType()) + " as user type");
    }
    STable::CClassInfo* classInfo = table->getClassInfo(returnedBase->GetClassName()->GetString());
    auto methodIterator = classInfo->GetMethodsBlock()->find(STable::CInternSymbol::GetIntern(node->id->name));
    if(methodIterator == classInfo->GetMethodsBlock()->end()) {
        throw DeclarationException("Requested method " + node->id->name + " is not declared in class " +
                                                        classInfo->GetName()->GetString());
    }
    const STable::CMethodInfo* methodInfo = methodIterator->second.get();
    auto scoped = table->GetScopedClass();
    if(scoped == nullptr || scoped->GetName() != classInfo->GetName()) { }
    for (auto arg : node->params){
        arg->accept(this);
    }

    if(node->params.size() != methodInfo->GetArgsCount()) {
        throw DeclarationException("Requested method " + classInfo->GetName()->GetString() + "::" + node->id->name + " has " + std::to_string(methodInfo->GetArgsCount()) +
                                                               " arguments, but " + std::to_string(node->params.size()) + " passed");
        for(auto argument = methodInfo->GetArgs()->rbegin(); argument != methodInfo->GetArgs()->rend(); ++argument) {
            auto arg = *argument;
            auto passed = popTypeStack();
            if( !(convertType(methodInfo->GetVariableInfo(arg)->GetType()) == convertType(passed))) {
                if(ToString(passed->GetType()) == "user class" &&
                    table->TypeHaveSuper(table->getClassInfo(passed->GetClassName()->GetString()),
                                                    methodInfo->GetVariableInfo(arg)->GetType()->GetClassName())) {
                    continue;
                }
                throw DeclarationException("Requested method " + classInfo->GetName()->GetString() + "::" + node->id->name +
                                                                   " was called with invalid argument - expected " + ToString(methodInfo->GetVariableInfo(arg)->GetType()) +
                                           ", got " + ToString(passed->GetType()));
            }
        }
    }
    typesStack.push(methodInfo->GetReturnType());
}

void CTypeChecker::visit(const CClassType *node){
    table->getClassInfo(node->label);
}

void CTypeChecker::visit(const CBooleanExp* node)
{
    typesStack.push(&BoolType);
}

void CTypeChecker::visit(const CIntegerExp* node)
{
    typesStack.push(&IntType);
}

void CTypeChecker::visit(const CId* node)
{
    STable::CVariableInfo* var = table->getVariableInfo(node->name);
    typesStack.push(var->GetType());
}

void CTypeChecker::visit(const CThis* node)
{
    auto scopedClass = table->GetScopedClass();
    typesStack.push(scopedClass->GetTypeInfo());
}

void CTypeChecker::visit(const CNewIntArray* node)
{
    node->size->accept(this);
    auto returned = popTypeStack();
    if(convertType(returned->GetType()) != BasicType::INT_) {
        throw DeclarationException("Trying to use " + ToString(returned->GetType()) + " type as size of array ");
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
        throw DeclarationException("Trying to use " + ToString(returned->GetType()) + " type as boolean expression ");
    }
    typesStack.push(&BoolType);
}

void CTypeChecker::visit(const CArg* node){}
void CTypeChecker::visit(const CTrue* node){
    typesStack.push(&BoolType);
}
void CTypeChecker::visit(const CFalse* node){
    typesStack.push(&BoolType);
}
void CTypeChecker::visit(const CStatementSeq *node){}
