#ifndef BOOLEXPRESSION_H
#define BOOLEXPRESSION_H

#include "Expression.h"
#include "Visitor.h"

class CTrue: public IExpression{
public:
    void accept(IVisitor* v) const{
        v->visit(this);
    }
}

#endif // BOOLEXPRESSION_H
