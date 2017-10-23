#ifndef BOOLEXPRESSION_H
#define BOOLEXPRESSION_H

#include "Visitor.h"

class IVisitor;

class CTrue: public IExpression{
public:
    void accept(IVisitor* v) const;
};

#endif // BOOLEXPRESSION_H
