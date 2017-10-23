#include "Variable.h"

CVariable::CVariable(std::shared_ptr<INode> type_, std::string name_):
    type(type_),
    name(name_)
{}
void CVariable::accept(IVisitor *v) const{
    v->visit(this);
}
