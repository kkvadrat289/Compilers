#ifndef STATEMENT_H
#define STATEMENT_H

#include "Node.h"
#include "Visitor.h"

class IVisitor;

class IStatement: public INode{
public:
    virtual void accept(IVisitor *v) const{
        //pass
    }
};

#endif // STATEMENT_H
