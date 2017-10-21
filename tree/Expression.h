#ifndef IEXPRESSION_H
#define IEXPRESSION_H

#include "Node.h"
#include "Visitor.h"

class IExpression: public INode{
public:
    void accept(IVisitor *v) const {
        //pass
    }
}

#endif // IEXPRESSION_H
