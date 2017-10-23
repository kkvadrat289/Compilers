#include "NewIntArray.h"

CNewIntArray::CNewIntArray(std::shared_ptr<IExpression> size_):
    size(size_)
{}
void CNewIntArray::accept(IVisitor *v) const{
    v->visit(this);
}
