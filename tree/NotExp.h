#ifndef UNARYEXP_H
#define UNARYEXP_H

#include "Expression.h"

class CNotExp: public IExpression{
public:
    CNotExp(std::shared_ptr<IExpression> right_):
        right(right_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<IExpression> right;
};

#endif // UNARYEXP_H
