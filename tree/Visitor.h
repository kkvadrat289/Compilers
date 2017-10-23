#ifndef VISITOR_H
#define VISITOR_H

#include "includes.h"

class CAssignStatement;

class IVisitor
{
public:
    void visit(CBinExpression* node);
    void visit(CId* node);
    void visit(CTrue* node);
    void visit(CFalse* node);
    void visit(CClass* node);
    void visit(CMain* node);
    void visit(CMethod* node);
    void visit(CProgram* node);
    void visit(CBooleanExp* node);
    void visit(CIntegerExp* node);
    void visit(CAssignStatement* node);
    void visit(CIf* node);
    void visit(CIdExp* node);
    void visit(CNotExp* node);
    void visit(CCallMethod* node);
    void visit(CNewIntArray* node);
    void visit(CNewClassObject* node);
    void visit(CRandomAccess* node);
    void visit(CLength* node);
    void visit(CPrintLine* node);
    void visit(CWhile* node);
};

#endif // VISITOR_H
