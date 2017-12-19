#ifndef NODE_H
#define NODE_H

#include <vector>
#include <memory>
#include "Position.h"
#include "../visitors/Visitor.h"

class IVisitor;

class INode
{
public:
    virtual void accept(IVisitor *v) const = 0;
    virtual ~INode();
    virtual const Position& GetPosition() const = 0;
};

#endif // NODE_H
