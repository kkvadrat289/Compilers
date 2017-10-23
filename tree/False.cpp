#include "False.h"

void CFalse::accept(IVisitor* v) const{
    v->visit(this);
}
