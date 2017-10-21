#ifndef THIS_H
#define THIS_H

#include "Visitor.h"

class CThis: public IExpression{
public:
    void accept(IVisitor* v){
        v->visit(this);
    }
}

#endif // THIS_H
