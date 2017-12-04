#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

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

class CClassInfo: public CSymbol{
public:
    CClassInfo( std::string name_) ;

    void AddMethodInfo(CMethodInfo* method);

    void AddVariableInfo(CVariableInfo* var);

    CInternSymbol* GetSuperClass();
    void SetSuperClass(std::string& name);
    void SetSuperClass(CInternSymbol* name);

    std::vector<CInternSymbol*> GetVars();
    std::vector<CInternSymbol*> GetMethods();

    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> > GetVarBlock();

    std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> > GetMethodsBlock();
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

class CInternSymbol {
public:
    static CInternSymbol* GetIntern(const std::string& name);

    const std::string& GetString()  ;

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
    CVariableInfo* GetVariableInfo(CInternSymbol *name);
    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> > GetVariablesBlock();
    CInternSymbol* GetClassName();

private:
    CInternSymbol* className;
    std::vector<CInternSymbol*> args;
    std::vector<CInternSymbol*> vars;
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

private:
    std::unordered_map<CInternSymbol*, std::shared_ptr<CMethodInfo> >* methodsBlock;
    std::unordered_map<CInternSymbol*, std::shared_ptr<CVariableInfo> >* variablesBlock;
    CClassInfo* className;
};



/* **************************TypeInfo***********************8 */

class CTypeInfo {
public:
    CTypeInfo(VarType type_, CInternSymbol* userClass_ = nullptr);
    CTypeInfo(VarType type_, std::string userClass_);

    CInternSymbol* GetClassName();
    VarType GetType();
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

}

#endif // TABLE_H
