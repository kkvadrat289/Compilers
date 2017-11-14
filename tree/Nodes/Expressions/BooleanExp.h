#ifndef BOOLEANEXP_H
#define BOOLEANEXP_H

#include "Expression.h"

class CBooleanExp: public IExpression{
public:
    CBooleanExp(bool val_): val(val_){}
    void accept(IVisitor *v) const override;
    bool val;
};

#endif // BOOLEANEXP_H
