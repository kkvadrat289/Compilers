#include "table.h"

namespace STable {

/* ******************CLASS INFO****************** */

CClassInfo::CClassInfo( std::string name_) :
    CSymbol(name_),
    superClass(nullptr)
{}

void CClassInfo::AddMethodInfo(CMethodInfo* method)
{
      methods.push_back(method->GetName());
      methodsBlock[method->GetName()]= std::shared_ptr<CMethodInfo>(method);
}

void CClassInfo::AddVariableInfo(CVariableInfo* var)
{
      vars.push_back(var->GetName());
      variablesBlock[var->GetName()] = std::shared_ptr<CVariableInfo>(var);
}

CInternSymbol* CClassInfo::GetSuperClass(){
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

std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> > CClassInfo::GetVarBlock(){
    return variablesBlock;
}

std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> > CClassInfo::GetMethodsBlock(){
    return methodsBlock;

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

const std::string& CInternSymbol::GetString()  {
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
    vars.push_back(var->GetName());
    variablesBlock[var->GetName()] = std::shared_ptr<CVariableInfo>(var);
}

void CMethodInfo::AddArg(CVariableInfo *arg){
    args.push_back(arg->GetName());
    variablesBlock[arg->GetName()] = std::shared_ptr<CVariableInfo>(arg);
}

CVariableInfo* CMethodInfo::GetVariableInfo(CInternSymbol *name){
    CVariableInfo *res = variablesBlock.find(name)->second.get();
    if (res == nullptr){
        //exception
    }
    return res;
}

std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> > CMethodInfo::GetVariablesBlock(){
    return variablesBlock;
}

CInternSymbol* CMethodInfo::GetClassName(){
    return className;
}


/* *********************SCOPE*************************** */
CScope::CScope(std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* variablesBlock_,
      std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> >* methodsBlock_ ,
      CClassInfo* className_) :
    methodsBlock(methodsBlock_),
    variablesBlock(variablesBlock_),
    className(className_)
{}

std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo > >* CScope::GetMethodsBlock(){return methodsBlock;}
std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* CScope::GetVariablesBlock(){return variablesBlock;}
CClassInfo* CScope::GetClassName(){return className;}


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

CInternSymbol* CTypeInfo::GetClassName(){return userClass;}
VarType CTypeInfo::GetType(){return type;}


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


}
