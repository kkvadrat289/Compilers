#ifndef NEWINTARRAY_H
#define NEWINTARRAY_H

#include "Visitor.h"

class CNewIntArray: public IExpression
{
public:
    CNewIntArray(std::shared_ptr<IExpression> size_):
        size(size_)
    {}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    std::shared_ptr<IExpression> size;
};

#endif // NEWINTARRAY_H
