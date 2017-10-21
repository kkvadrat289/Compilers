#ifndef UNARYEXP_H
#define UNARYEXP_H

#include "Visitor.h"

class CNotExp: public IExpression{
public:
    CNotExp(std::shared_ptr<IExpression> right_):
        right(righgt_)
    {}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    std::shared_ptr<IExpression> right;
}

#endif // UNARYEXP_H
