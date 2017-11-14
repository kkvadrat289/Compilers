#ifndef RANDOMACCESS_H
#define RANDOMACCESS_H

#include "Expression.h"

class CRandomAccess: public IExpression{
public:
    CRandomAccess(std::shared_ptr<IExpression> left_, std::shared_ptr<IExpression> right_):
        object(left_),
        position(right_)
    {}
    void accept(IVisitor *v) const override;

    std::shared_ptr<IExpression> object;
    std::shared_ptr<IExpression> position;

};

#endif // RANDOMACCESS_H
