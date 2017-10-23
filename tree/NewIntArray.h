#ifndef NEWINTARRAY_H
#define NEWINTARRAY_H

#include "Visitor.h"

class IVisitor;

class CNewIntArray: public IExpression
{
public:
    CNewIntArray(std::shared_ptr<IExpression> size_);
    void accept(IVisitor *v) const;
private:
    std::shared_ptr<IExpression> size;
};

#endif // NEWINTARRAY_H
