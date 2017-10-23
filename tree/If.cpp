#include "If.h"

CIf::CIf(std::shared_ptr<INode> cond_, std::shared_ptr<CStatementSeq> ifTrue_, std::shared_ptr<CStatementSeq> ifFalse_):
    cond(cond_),
    ifTrue(ifTrue_),
    ifFalse(ifFalse_)
{}
void CIf::accept(IVisitor *v) const{
    v->visit(this);
}
