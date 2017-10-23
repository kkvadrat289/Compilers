#include "CallMethod.h"

CCallMethod::CCallMethod(std::shared_ptr<INode> object_, std::string name_, std::shared_ptr<CExpressionSeq> params_):
    object(object_),
    params(params_),
    params(params_)
{}
void CCallMethod::accept(IVisitor *v) const{
    v->visit(this);
}
