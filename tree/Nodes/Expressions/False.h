#ifndef FALSE_H
#define FALSE_H

#include "Expression.h"

class CFalse: public IExpression{
public:
    void accept(IVisitor* v) const override;
};

#endif // FALSE_H
