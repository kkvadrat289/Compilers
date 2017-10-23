#include "Class.h"

CClass::CClass(std::string name_, std::string extends_, std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CMethodSeq> methods_):
    name(name_),
    extends(extends_)
{
    //add vectors
}
CClass::CClass(std::string name_, std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CMethodSeq> methods_):
    name(name_)
{

    //add vectors
}
void CClass::accept(IVisitor *v) const{
      v->visit(this);
}
