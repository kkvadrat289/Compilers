#ifndef SYMBOLTABLEVISITOR_H
#define SYMBOLTABLEVISITOR_H

#include "Visitor.h"

#include "../SymbolTable/table.h"
#include "../SymbolTable/SymbolTable.h"

/*#include "../SymbolTable/ClassInfo.h"
#include "../SymbolTable/InternSymbol.h"
#include "../SymbolTable/MethodInfo.h"
#include "../SymbolTable/Scope.h"
#include "../SymbolTable/TypeInfo.h"
#include "../SymbolTable/VariableInfo.h"*/

namespace STable {

class CTableVisitor: public IVisitor{
public:
    CTableVisitor(CProgram* program);
    CTypeInfo *convertType(IType* type);
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

