#include "Id.h"

CId::CId(const std::string name_): name(name_)
{

}

void CId::accept(IVisitor* v) const
{
    v->visit(this);
}
