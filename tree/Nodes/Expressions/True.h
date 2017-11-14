#ifndef BOOLEXPRESSION_H
#define BOOLEXPRESSION_H

#include "Expression.h"

class CTrue: public IExpression{
public:
    void accept(IVisitor* v) const override;
};

#endif // BOOLEXPRESSION_H
