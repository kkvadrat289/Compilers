#include "BasicType.h"

CBasicType::CBasicType(BasicType type_): type(type_)
{}

void CBasicType::accept(IVisitor *v) const{
    v->visit(this);
}
