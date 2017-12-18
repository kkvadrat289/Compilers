#ifndef T_H
#define T_H
/*

#include <stack>
#include "../includes.h"
#include "SymbolTableVisitor.h"
#include "../Exceptions.h"
#include "../SymbolTable/table.h"

namespace TypeChecker {

class CTypeChecker : public IVisitor {
public:
    void Check(CProgram* root, STable::CTable* table);

    void visit(const CBinExpression* node)  override; //
    void visit(const CId* node)  override; //
    void visit(const CTrue* node)  override;
    void visit(const CFalse* node)  override;
    void visit(const CClass* node)  override;//
    void visit(const CMain* node)  override;
    void visit(const CMethod* node)  override;//
    void visit(const CProgram* node)  override; //
    void visit(const CBooleanExp* node)  override;//
    void visit(const CIntegerExp* node)  override;//
    void visit(const CAssignStatement* node)  override;//
    void visit(const CIf* node)  override;//
    void visit(const CNotExp* node)  override; //
    void visit(const CCallMethod* node)  override;//
    void visit(const CNewIntArray* node)  override; //
    void visit(const CNewClassObject* node)  override;//
    void visit(const CRandomAccessAssign* node)  override; //
    void visit(const CLength* node)  override;//
    void visit(const CPrintLine* node)  override;//
    void visit(const CWhile* node)  override;//
    void visit(const CStatements* node)  override;//
    void visit(const CRandomAccess* node)  override; //
    void visit(const CArg* node)  override;
    void visit(const CStatementSeq* node)  override;
    void visit(const CVariable* node)  override; //
    void visit(const CThis* node) override;

private:
    STable::CTable* table;
    std::stack<const STable::CTypeInfo*> typesStack;
    const STable::CTypeInfo *popTypeStack();
};


inline const STable::CTypeInfo *CTypeChecker::popTypeStack() {
    auto type = typesStack.top();
    typesStack.pop();
    return type;
}
}

*/

#endif // T_H
