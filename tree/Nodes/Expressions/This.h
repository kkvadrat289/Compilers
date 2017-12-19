#ifndef THIS_H
#define THIS_H

#include "Expression.h"

class CThis: public IExpression{
public:
    void accept(IVisitor* v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }
    CThis(Position pos_):
        pos(pos_)
    {}

    Position pos;
};

#endif // THIS_H
