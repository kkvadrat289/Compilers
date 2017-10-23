#ifndef UNARYEXP_H
#define UNARYEXP_H

#include "Visitor.h"

class IVisitor;

class CNotExp: public IExpression{
public:
    CNotExp(std::shared_ptr<IExpression> right_);
    void accept(IVisitor *v) const;
private:
    std::shared_ptr<IExpression> right;
};

#endif // UNARYEXP_H
