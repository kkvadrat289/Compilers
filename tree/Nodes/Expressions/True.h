#ifndef BOOLEXPRESSION_H
#define BOOLEXPRESSION_H

#include "Expression.h"

class CTrue: public IExpression{
public:
    void accept(IVisitor* v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }
    CTrue (Position pos_):
        pos(pos_)
    {}

    Position pos;
};

#endif // BOOLEXPRESSION_H
