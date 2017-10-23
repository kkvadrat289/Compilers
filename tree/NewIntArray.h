#ifndef NEWINTARRAY_H
#define NEWINTARRAY_H

#include "Expression.h"

class CNewIntArray: public IExpression
{
public:
    CNewIntArray(std::shared_ptr<IExpression> size_):
        size(size_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<IExpression> size;
};

#endif // NEWINTARRAY_H
