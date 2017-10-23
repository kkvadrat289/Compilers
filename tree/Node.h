#ifndef NODE_H
#define NODE_H

#include "Visitor.h"

class IVisitor;

class INode
{
public:
    INode();
    virtual void accept(IVisitor *v) const = 0;
};

#endif // NODE_H
