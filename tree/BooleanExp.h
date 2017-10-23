#ifndef BOOLEANEXP_H
#define BOOLEANEXP_H

#include "Visitor.h"

class CBooleanExp: public IExpression{
public:
    CBooleanExp(bool val_): val(val_){}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    bool val;
}

#endif // BOOLEANEXP_H
