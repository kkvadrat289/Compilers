#ifndef SYMBOLTABLEVISITOR_H
#define SYMBOLTABLEVISITOR_H

#include <iostream>
#include <stack>
#include <string>

#include "Visitor.h"
#include "../Exceptions.h"

#include "../SymbolTable/table.h"

namespace STable {

class CTableVisitor: public IVisitor{
public:
    CTableVisitor();
    ~CTableVisitor(){}
    CTableVisitor(CProgram* program);
    CTypeInfo *convertType(const IType *type);
    void printClassInfo(CClassInfo* classInfo);
    void printVariableInfo(CVariableInfo *varInfo);
    void printTypeInfo(CTypeInfo* type);
    void ParseProgram(CProgram* program);
    void FillTable(CProgram* program);
    CTable* GetTable(){
        return table;
    }

    void visit(const CProgram* node)  override;
    void visit(const CMain* node)  override{}
    void visit(const CClass* node)  override;
    void visit(const CMethod* node)  override;
    void visit(const CVariable* node)  override{}
    void visit(const CBinExpression* node)  override{}
    void visit(const CId* node)  override{}
    void visit(const CTrue* node)  override{}
    void visit(const CFalse* node)  override{}
    void visit(const CBooleanExp* node)  override{}
    void visit(const CIntegerExp* node)  override{}
    void visit(const CAssignStatement* node)  override{}
    void visit(const CIf* node)  override{}
    void visit(const CNotExp* node)  override{}
    void visit(const CCallMethod* node)  override{}
    void visit(const CNewIntArray* node)  override{}
    void visit(const CNewClassObject* node)  override{}
    void visit(const CRandomAccessAssign* node)  override{}
    void visit(const CLength* node)  override{}
    void visit(const CPrintLine* node)  override{}
    void visit(const CWhile* node)  override{}
    void visit(const CStatements* node)  override{}
    void visit(const CRandomAccess* node)  override{}
    void visit(const CArg* node)  override{}
    void visit(const CStatementSeq* node)  override{}
    void visit(const CThis* node) override {}
private:
    CTable* table;
};

}




#endif // SYMBOLTABLEVISITOR_H

