#include "NewClassObject.h"

CNewClassObject::CNewClassObject(std::string name_):
    name(name_)
{}
void CNewClassObject::accept(IVisitor *v) const{
    v->visit(this);
}
