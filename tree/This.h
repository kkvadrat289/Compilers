#ifndef THIS_H
#define THIS_H

#include "Visitor.h"

class IVisitor;

class CThis: public IExpression{
public:
    void accept(IVisitor* v);
};

#endif // THIS_H
