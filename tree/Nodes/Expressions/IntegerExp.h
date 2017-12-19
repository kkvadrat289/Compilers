#ifndef INTEGEREXPR_H
#define INTEGEREXPR_H

#include "Expression.h"

class CIntegerExp: public IExpression{
public:
    CIntegerExp(int val_, Position pos_):
        val(val_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    int val;
};

#endif // INTEGEREXPR_H
