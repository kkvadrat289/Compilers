#include "Length.h"

CLength::CLength(std::shared_ptr<IExpression> object_):
    object(object_)
{}
void CLength::accept(IVisitor *v) const{
    v->visit(this);
}
