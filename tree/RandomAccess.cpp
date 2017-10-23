#include "RandomAccess.h"

CRandomAccess::CRandomAccess(std::shared_ptr<IExpression> array_, std::shared_ptr<IExpression> position_):
    array(array_),
    position(position_)
{}
void CRandomAccess::accept(IVisitor *v) const{
    v->visit(this);
}
