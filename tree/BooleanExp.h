#ifndef BOOLEANEXP_H
#define BOOLEANEXP_H

#include "Visitor.h"

class IVisitor;

class CBooleanExp: public IExpression{
public:
    CBooleanExp(bool val_);
    void accept(IVisitor *v) const;
private:
    bool val;
};

#endif // BOOLEANEXP_H
