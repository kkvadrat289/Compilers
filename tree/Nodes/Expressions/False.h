#ifndef FALSE_H
#define FALSE_H

#include "Expression.h"

class CFalse: public IExpression{
public:
    void accept(IVisitor* v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }
    CFalse(Position pos_):
        pos(pos_)
    {}
    Position pos;
};

#endif // FALSE_H
