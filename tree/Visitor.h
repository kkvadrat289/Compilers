#ifndef VISITOR_H
#define VISITOR_H

#include "includes.h"

class IVisitor
{
public:
    virtual void visit(const CBinExpression* node) = 0;
    virtual void visit(const CId* node) = 0;
    virtual void visit(const CTrue* node) = 0;
    virtual void visit(const CFalse* node) = 0;
    virtual void visit(const CClass* node) = 0;
    virtual void visit(const CMain* node) = 0;
    virtual void visit(const CMethod* node) = 0;
    virtual void visit(const CProgram* node) = 0;
    virtual void visit(const CBooleanExp* node) = 0;
    virtual void visit(const CIntegerExp* node) = 0;
    virtual void visit(const CAssignStatement* node) = 0;
    virtual void visit(const CIf* node) = 0;
    virtual void visit(const CIdExp* node) = 0;
    virtual void visit(const CNotExp* node) = 0;
    virtual void visit(const CCallMethod* node) = 0;
    virtual void visit(const CNewIntArray* node) = 0;
    virtual void visit(const CNewClassObject* node) = 0;
    virtual void visit(const CRandomAccess* node) = 0;
    virtual void visit(const CLength* node) = 0;
    virtual void visit(const CPrintLine* node) = 0;
    virtual void visit(const CWhile* node) = 0;
};

#endif // VISITOR_H
