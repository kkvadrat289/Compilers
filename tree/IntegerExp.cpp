#include "IntegerExp.h"

CIntegerExp::CIntegerExp(int val_):
    val(val_)
{}
void CIntegerExp::accept(IVisitor *v) const{
    v->visit(this);
}
