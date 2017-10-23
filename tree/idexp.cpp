#include "IdExp.h"

CIdExp::CIdExp(std::string id_): id(id_)
{

}

void CIdExp::accept(IVisitor *v) const{
    v->visit(this);
}
