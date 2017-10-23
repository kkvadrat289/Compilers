#include "BooleanExp.h"

CBooleanExp::CBooleanExp(bool val_): val(val_){}
void CBooleanExp::accept(IVisitor *v) const{
    v->visit(this);
}
