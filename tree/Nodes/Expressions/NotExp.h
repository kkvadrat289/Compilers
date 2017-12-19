#ifndef UNARYEXP_H
#define UNARYEXP_H

#include "Expression.h"

class CNotExp: public IExpression{
public:
    CNotExp(std::shared_ptr<IExpression> right_, Position pos_):
        right(right_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<IExpression> right;
};

#endif // UNARYEXP_H
