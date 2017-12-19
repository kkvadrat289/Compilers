#ifndef BOOLEANEXP_H
#define BOOLEANEXP_H

#include "Expression.h"

class CBooleanExp: public IExpression{
public:
    CBooleanExp(bool val_, Position pos_):
        val(val_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    bool val;
};

#endif // BOOLEANEXP_H
