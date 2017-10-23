#include "PrintLine.h"

CPrintLine::CPrintLine(std::shared_ptr<IExpression> object_):
    object(object_)
{}
void CPrintLine::accept(IVisitor *v) const{
    v->visit(this);
}
