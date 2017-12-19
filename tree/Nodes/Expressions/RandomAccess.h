#ifndef RANDOMACCESS_H
#define RANDOMACCESS_H

#include "Expression.h"

class CRandomAccess: public IExpression{
public:
    CRandomAccess(std::shared_ptr<IExpression> left_, std::shared_ptr<IExpression> right_, Position pos_):
        object(left_),
        position(right_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<IExpression> object;
    std::shared_ptr<IExpression> position;

};

#endif // RANDOMACCESS_H
