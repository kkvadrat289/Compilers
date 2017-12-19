#ifndef LENGTH_H
#define LENGTH_H

#include "Expression.h"

class CLength: public IExpression{
public:
    CLength(std::shared_ptr<IExpression> object_, Position pos_):
        object(object_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<IExpression> object;
};

#endif // LENGTH_H
