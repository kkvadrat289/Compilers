#ifndef STATEMENT_H
#define STATEMENT_H

#include "Node.h"
#include "Visitor.h"

class IStatement: public INode{
public:
    virtual void accept(IVisitor *v) const override;
}

#endif // STATEMENT_H
