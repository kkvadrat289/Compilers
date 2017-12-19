#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <set>
#include <assert.h>
#include "../Exceptions.h"

namespace STable {

class CInternSymbol;
class CSymbol;
class CVariableInfo;
class CMethodInfo;
class CClassInfo;
class CTypeInfo;

/* ****************SYMBOL************************ */

class CSymbol {
public:
    CSymbol(std::string name_);
    CSymbol(CInternSymbol* name_);

  CInternSymbol* GetName() const ;

  CSymbol( const CSymbol& ) = delete;
  void operator=( const CSymbol& ) = delete;

  bool operator ==( const CSymbol& symbol );
  bool operator !=( const CSymbol& symbol );

  virtual ~CSymbol();

protected:

  CInternSymbol* name;

};

/* ******* CLASS ************************ */

class CClassInfo: public CSymbol{
public:
    CClassInfo( std::string name_) ;
    void AddMethodInfo(CMethodInfo* method);
    void AddVariableInfo(CVariableInfo* var);
    CInternSymbol *GetSuperClass() const;
    void SetSuperClass(std::string& name);
    void SetSuperClass(CInternSymbol* name);

    std::vector<CInternSymbol*> GetVars();
    std::vector<CInternSymbol*> GetMethods();

    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* GetVarBlock();

    std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> >* GetMethodsBlock();
    const CTypeInfo *GetTypeInfo() const;
private:
    CClassInfo(const CClassInfo&) = delete;
    std::vector<CInternSymbol*> vars;
    std::vector<CInternSymbol*> methods;
    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> > variablesBlock;
    std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> > methodsBlock;
    CInternSymbol* superClass;
};

enum VarType{
    T_INT,
    T_BOOL,
    T_INT_ARR,
    T_CLASS
};

/* ********** INTERN SYMBOL *************** */

class CInternSymbol {
public:
    static CInternSymbol* GetIntern(const std::string& name);

    const std::string& GetString() const;

private:
    std::string body;

    CInternSymbol(std::string name) : body(name) { }
    CInternSymbol(  CInternSymbol& ) = delete;
    void operator=( const CInternSymbol& ) = delete;
};

/* ************METHOD********************* */

class CMethodInfo: public CSymbol
{
public:
    CMethodInfo(const CMethodInfo&) = delete;
    CMethodInfo(std::string name_, CTypeInfo* returnType_, std::string& className_);
    CTypeInfo* GetType();
    void AddVariable(CVariableInfo* var);
    void AddArg(CVariableInfo *arg);
    CVariableInfo* GetVariableInfo(CInternSymbol *name) const;
    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* GetVariablesBlock();
    CInternSymbol* GetClassName();
    CTypeInfo* GetReturnType() const;
    int GetArgsCount()const {return args.size();}
    const std::vector<CInternSymbol *> *GetArgs() const;
    std::vector<CInternSymbol*>* GetVars();


    std::vector<CInternSymbol*> args;
    std::vector<CInternSymbol*> vars;
private:
    CInternSymbol* className;
    CTypeInfo* returnType;
    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> > variablesBlock;
};

/* *****************SCOPE***************** */

class CScope
{
public:
    CScope(std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* variablesBlock_ = nullptr,
          std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> >* methodsBlock_ = nullptr,
          CClassInfo* className_ = nullptr) ;

    std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo > >* GetMethodsBlock();
    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* GetVariablesBlock();
    CClassInfo* GetClassName();
    std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> >* methodsBlock;
    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* variablesBlock;
    CClassInfo* classInfo;
};



/* **************************TypeInfo***********************8 */

class CTypeInfo {
public:
    CTypeInfo(VarType type_, CInternSymbol* userClass_ = nullptr);
    CTypeInfo(VarType type_, std::string userClass_);
    bool operator==(const CTypeInfo& other) const;
    const CInternSymbol *GetClassName() const;
    const VarType GetType() const;
private:
    VarType type;
    CInternSymbol* userClass;
};

/* ******************* VARIABLE *******************8 */


class CVariableInfo : public CSymbol{
public:
    CVariableInfo(const CVariableInfo&) = delete;
    CVariableInfo(std::string name_, VarType type_);
    CVariableInfo(std::string name_, CTypeInfo* type_);
    //если пользовательский тип:
    CVariableInfo(std::string name_, VarType type_, std::string className);

    CTypeInfo* GetType();
private:
    CTypeInfo* type;
};

/* ************************************************** */

class CTable {
public:
    void AddClass(CClassInfo* newClass);
    void AddNewClass(std::string neClassName);
    void AddNewMethod(std::string newMethodName);
    void FreeLastScope();
    bool DoesTypeHaveSuper(const CClassInfo* classInfo, const CInternSymbol *super) const;
    CClassInfo* getClassInfo(const std::string className) const;
    CVariableInfo* getVariableInfo(const std::string &name);
    CMethodInfo* GetMethodInfo(std::string& name);
    CTypeInfo* GetTypeInfo(std::string& name);
    std::vector<CInternSymbol*>& GetClassesNames(){ return classesNames; }
    const CClassInfo* GetScopedClass() const ;
    CTable(const CTable&) = delete;
    CTable(){}

private:
    CMethodInfo* getMethodInfo(std::string methodName);
    void checkClass(CClassInfo* classToCheck);
    std::vector<CClassInfo*> getChain(CClassInfo* newClass);
    std::vector<std::shared_ptr<CScope> > scopes;
    std::unordered_map<CInternSymbol*, std::shared_ptr<CClassInfo> > classes;
    std::vector<CInternSymbol*> classesNames;
    std::set<CInternSymbol*> checked;

};

}

#endif // TABLE_H
