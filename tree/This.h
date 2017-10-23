#ifndef THIS_H
#define THIS_H

#include "Expression.h"

class CThis: public IExpression{
public:
    void accept(IVisitor* v) const override;
};

#endif // THIS_H
