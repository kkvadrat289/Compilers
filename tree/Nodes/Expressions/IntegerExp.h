#ifndef INTEGEREXPR_H
#define INTEGEREXPR_H

#include "Expression.h"

class CIntegerExp: public IExpression{
public:
    CIntegerExp(int val_):
        val(val_)
    {}
    void accept(IVisitor *v) const override;
    int val;
};

#endif // INTEGEREXPR_H
