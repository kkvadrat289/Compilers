#ifndef NODE_H
#define NODE_H

#include <memory>
#include "Visitor.h"

class IVisitor;

class INode
{
public:
    virtual void accept(IVisitor *v) const = 0;
    virtual ~INode();
};

#endif // NODE_H
