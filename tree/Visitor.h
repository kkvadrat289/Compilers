#ifndef VISITOR_H
#define VISITOR_H

#include "includes.h"

class IVisitor
{
public:
    visit(CBinExpression* node);
    visit(CId* node);
    visit(CTrue* node);
    visit(CFalse* node);
    visit(CClass* node);
    visit(CMain* node);
    visit(CMethod* node);
    visit(CProgram* node);
    visit(CBooleanExp* node);
    visit(CIntegerExp* node);
    visit(CAssignStatement* node);
    visit(CIf* node);
    visit(CIdExp* node);
    visit(CNotExp* node);
    visit(CCallMethod* node);
    visit(CNewIntArray* node);
    visit(CNewClassObject* node);
    visit(CRandomAccess* node);
    visit(CLength* node);
    visit(CLength* node);
    visit(CPrintLine* node);
    visit(CWhile* node);
};

#endif // VISITOR_H
