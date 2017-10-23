#include "True.h"

void CTrue::accept(IVisitor* v) const{
    v->visit(this);
}
