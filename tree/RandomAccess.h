#ifndef RANDOMACCESS_H
#define RANDOMACCESS_H

#include "Expression.h"

class CRandomAccess: public IExpression{
public:
    CRandomAccess(std::shared_ptr<IExpression> left_, std::shared_ptr<IExpression> right_):
        left(left_),
        right(right_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<IExpression> left;
    std::shared_ptr<IExpression> right;

};

#endif // RANDOMACCESS_H
