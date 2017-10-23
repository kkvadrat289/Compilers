#ifndef IEXPRESSION_H
#define IEXPRESSION_H

#include "Node.h"
#include "Visitor.h"

class IVisitor;

class IExpression: public INode{
public:
    void accept(IVisitor *v) const ;
};

#endif // IEXPRESSION_H
