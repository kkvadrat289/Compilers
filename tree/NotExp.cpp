#include "NotExp.h"

CNotExp::CNotExp(std::shared_ptr<IExpression> right_):
    right(righgt_)
{}
void CNotExp::accept(IVisitor *v) const{
    v->visit(this);
}
