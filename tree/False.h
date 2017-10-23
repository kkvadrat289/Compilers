#ifndef FALSE_H
#define FALSE_H

#include "Expression.h"
#include "Visitor.h"

class IVisitor;

class CFalse: public IExpression{
public:
    void accept(IVisitor* v) const;
};

#endif // FALSE_H
