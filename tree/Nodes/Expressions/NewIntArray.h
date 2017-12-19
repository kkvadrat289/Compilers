#ifndef NEWINTARRAY_H
#define NEWINTARRAY_H

#include "Expression.h"

class CNewIntArray: public IExpression
{
public:
    CNewIntArray(std::shared_ptr<IExpression> size_, Position pos_):
        size(size_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<IExpression> size;
};

#endif // NEWINTARRAY_H
