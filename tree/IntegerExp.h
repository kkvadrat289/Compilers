#ifndef INTEGEREXPR_H
#define INTEGEREXPR_H

#include "Visitor.h"

class CIntegerExp: public IExpression{
public:
    CIntegerExp(int val_):
        val(val_)
    {}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    int val;
}

#endif // INTEGEREXPR_H
