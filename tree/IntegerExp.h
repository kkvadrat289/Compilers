#ifndef INTEGEREXPR_H
#define INTEGEREXPR_H

#include "Visitor.h"

class IVisitor;

class CIntegerExp: public IExpression{
public:
    CIntegerExp(int val_);
    void accept(IVisitor *v) const;
private:
    int val;
};

#endif // INTEGEREXPR_H
