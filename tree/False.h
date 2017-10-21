#ifndef FALSE_H
#define FALSE_H

#include "Expression.h"
#include "Visitor.h"

class CFalse: public IExpression{
public:
    void accept(IVisitor* v) const{
        v->visit(this);
    }
}

#endif // FALSE_H
