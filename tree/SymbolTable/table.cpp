#include "table.h"

namespace STable {

/* ******************CLASS INFO****************** */

CClassInfo::CClassInfo( std::string name_) :
    CSymbol(name_),
    superClass(nullptr)
{}

const CTypeInfo* CClassInfo::GetTypeInfo() const{
    return new CTypeInfo(VarType::T_CLASS, this->name->GetString());
}

bool CTypeInfo::operator==(const CTypeInfo &other) const
{
    if(other.GetType() != VarType::T_CLASS) {
        return this->GetType() == other.GetType();
    }
    return this->GetType() == other.GetType() &&
            this->GetClassName() == other.GetClassName();
}

void CClassInfo::AddMethodInfo(CMethodInfo* method)
{
    auto newMethod= methodsBlock.find(method->GetName());
    if (newMethod != methodsBlock.end()){
        throw  DeclarationException("Method " + method->GetName()->GetString() + "  already declared");
    }
    methods.push_back(method->GetName());
    methodsBlock[method->GetName()]= std::shared_ptr<CMethodInfo>(method);
}

void CClassInfo::AddVariableInfo(CVariableInfo* var)
{
    if (variablesBlock.find(var->GetName()) != variablesBlock.end()){
        throw  DeclarationException("Variable " + var->GetName()->GetString() + "  already declared");
    }
    vars.push_back(var->GetName());
    variablesBlock[var->GetName()] = std::shared_ptr<CVariableInfo>(var);
}

CInternSymbol* CClassInfo::GetSuperClass() const{
    return superClass;
}
void CClassInfo::SetSuperClass(std::string& name){
    superClass = CInternSymbol::GetIntern(name);
}
void CClassInfo::SetSuperClass(CInternSymbol* name){
    superClass = name;
}

std::vector<CInternSymbol*> CClassInfo::GetVars(){
    return vars;
}
std::vector<CInternSymbol*> CClassInfo::GetMethods(){
    return methods;
}

std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* CClassInfo::GetVarBlock(){
    return &variablesBlock;
}

std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> >* CClassInfo::GetMethodsBlock(){
    return &methodsBlock;

}

/* ***************INTERN SYMBOL********************** */

CInternSymbol* CInternSymbol::GetIntern(const std::string& name)
    {
        static std::unordered_map<std::string, std::shared_ptr<CInternSymbol>> strings;
        auto cached = strings.find(name);
        if (cached != strings.end()){
            return cached->second.get();
        }
        CInternSymbol* newVal = new CInternSymbol(name);
        strings[name] = std::shared_ptr<CInternSymbol>(newVal);
        return newVal;
    }

const std::string& CInternSymbol::GetString()  const{
        return body;
    }

/* ******************METHOD************************* */


CMethodInfo::CMethodInfo(std::string name_, CTypeInfo* returnType_, std::string& className_):
    CSymbol(name_),
    returnType(returnType_),
    className(CInternSymbol::GetIntern(className_))
{}
CTypeInfo* CMethodInfo::GetType(){
    return returnType;
}
void CMethodInfo::AddVariable(CVariableInfo* var){
    if (variablesBlock.find(var->GetName()) != variablesBlock.end()){
        throw DeclarationException("Variable " + var->GetName()->GetString() + " in method "
                                   + this->name->GetString() + " already declared");
    }
    vars.push_back(var->GetName());
    variablesBlock[var->GetName()] = std::shared_ptr<CVariableInfo>(var);
}

void CMethodInfo::AddArg(CVariableInfo *arg){
    if (variablesBlock.find(arg->GetName()) != variablesBlock.end()){
        throw DeclarationException("Variable " + arg->GetName()->GetString() + " in method "
                                   + this->name->GetString() + " already declared");
    }
    args.push_back(arg->GetName());
    variablesBlock[arg->GetName()] = std::shared_ptr<CVariableInfo>(arg);
}

CVariableInfo* CMethodInfo::GetVariableInfo(CInternSymbol *name) const {
    CVariableInfo *res = variablesBlock.find(name)->second.get();
    if (res == nullptr){
        throw DeclarationException("Variable " + name->GetString() + " in method " + this->name->GetString() + " undeclared");
    }
    return res;
}

std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* CMethodInfo::GetVariablesBlock(){
    return &variablesBlock;
}

CInternSymbol* CMethodInfo::GetClassName(){
    return className;
}

CTypeInfo* CMethodInfo::GetReturnType() const {
    return returnType;
}

const std::vector<CInternSymbol*>* CMethodInfo::GetArgs() const{
    return &args;
}

std::vector<CInternSymbol*>* CMethodInfo::GetVars(){
    return &vars;
}


/* *********************SCOPE*************************** */
CScope::CScope(std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* variablesBlock_,
      std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> >* methodsBlock_ ,
      CClassInfo* className_) :
    methodsBlock(methodsBlock_),
    variablesBlock(variablesBlock_),
    classInfo(className_)
{}

std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo > >* CScope::GetMethodsBlock(){return methodsBlock;}
std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* CScope::GetVariablesBlock(){return variablesBlock;}
CClassInfo* CScope::GetClassName(){return classInfo;}


/* ******************** TYPEINFO *********************** */

CTypeInfo::CTypeInfo(VarType type_, CInternSymbol* userClass_):
    type(type_)
{
    if (type == VarType::T_CLASS){
        userClass = userClass_;
    }
}
CTypeInfo::CTypeInfo(VarType type_, std::string userClass_):
    type(type_)
{
    if(type == VarType::T_CLASS) {
        userClass = CInternSymbol::GetIntern(userClass_);
    }
}

const CInternSymbol* CTypeInfo::GetClassName() const {return userClass;}
const VarType CTypeInfo::GetType() const {return type;}


/* ******************VARIABLE ******************** */



CVariableInfo::CVariableInfo(std::string name_, VarType type_): CSymbol(name){
    type = new CTypeInfo(type_);
}
CVariableInfo::CVariableInfo(std::string name_, CTypeInfo* type_):
    CSymbol(name_),
    type(type_)
{}
//если пользовательский тип:
CVariableInfo::CVariableInfo(std::string name_, VarType type_, std::string className): CSymbol(name){
    type = new CTypeInfo(type_, className);
}

CTypeInfo* CVariableInfo::GetType(){return type;}

CSymbol::CSymbol(std::string name_): name(CInternSymbol::GetIntern(name_)){}
CSymbol::CSymbol(CInternSymbol* name_): name(name_){}

CInternSymbol* CSymbol::GetName() const {
  return name;
}


bool CSymbol::operator ==( const CSymbol& symbol ){
  return &symbol == this;
}
bool CSymbol::operator !=( const CSymbol& symbol ){
  return &symbol != this;
}

CSymbol::~CSymbol() {}

/* ************************CLASS********************************************************************* */


void CTable::AddClass(CClassInfo *newClass){
    if (classes.find(newClass->GetName()) == classes.end()){
        classesNames.push_back(newClass->GetName());
        classes[newClass->GetName()] = std::shared_ptr<CClassInfo>(newClass);

    }
    else{
        throw DeclarationException("Class " + newClass->GetName()->GetString() + " already declared");
    }
}

CClassInfo* CTable::getClassInfo(const std::string className) const{
    CInternSymbol *nameIntern = CInternSymbol::GetIntern(className);
    auto info = classes.find(nameIntern);
    if (info != classes.end()){
        return info->second.get();
    }
    throw DeclarationException("Class " + className + " not declared");
}

bool CTable::DoesTypeHaveSuper(const CClassInfo* classInfo, const CInternSymbol *super) const
{
    for(auto info = classInfo;
        info->GetSuperClass() != nullptr;
        info = getClassInfo(info->GetSuperClass()->GetString()))
    {
        if(classInfo->GetSuperClass() == super) {
            return true;
        }
    }
    return false;
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
    for (CClassInfo* class_ = newClass; class_ ->GetSuperClass()!= nullptr; class_ = getClassInfo(class_->GetSuperClass()->GetString())){
        for (auto super : chain){
            if (super->GetName()->GetString() == class_->GetName()->GetString()){
                //cyclic dependency
                throw DeclarationException("cyclic dependency in class " + class_->GetName()->GetString());
            }
        }
        chain.push_back(class_);
    }
    for(auto class_ : chain) {
        auto varBlock = class_->GetVarBlock();
        auto methBlock = class_->GetMethodsBlock();
        scopes.push_back(std::shared_ptr<CScope>(new CScope(varBlock, methBlock, class_)));
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
    throw DeclarationException("method " + methodName + " not declared");
}

void CTable::FreeLastScope(){
    assert(scopes.size() > 0);
    scopes.pop_back();
}

void CTable::AddNewMethod(std::string newMethodName){
    CMethodInfo* method = getMethodInfo(newMethodName);
    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* varBlock = method->GetVariablesBlock();
    scopes.push_back(std::shared_ptr<CScope>(new CScope(varBlock, nullptr, scopes.begin()->get()->GetClassName())));
}

const CClassInfo* CTable::GetScopedClass() const {
    return scopes.size() > 0 ? scopes.rbegin()->get()->classInfo : nullptr;
}

CVariableInfo* CTable::getVariableInfo(const std::string &name)
{
    CInternSymbol* varName = CInternSymbol::GetIntern(name);
    for(auto scope : this-> scopes) {
    //auto scope = this->scopes[0];
        if (scope->GetVariablesBlock() != nullptr){
            auto variable = scope->GetVariablesBlock()->find(varName);
            if(variable != scope->GetVariablesBlock()->end()) {
                return variable->second.get();
            }
        }
    }
    throw DeclarationException("Variable " + name + " not declared");
}

CMethodInfo* CTable::GetMethodInfo(std::string& name)
{
    CInternSymbol* methodName = CInternSymbol::GetIntern(name);
    for(auto scope : scopes) {
        auto method = scope->methodsBlock->find(methodName);
        if(method != scope->GetMethodsBlock()->end()) {
            return method->second.get();
        }
    }
    throw DeclarationException("Method " + name + " not declared");
}
}
