#include "This.h"

void CThis::accept(IVisitor* v){
    v->visit(this);
}
