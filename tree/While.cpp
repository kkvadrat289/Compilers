#include "While.h"

CWhile::CWhile(std::shared_ptr<IExpression> cond_, std::shared_ptr<IStatement> actions_):
    cond(cond_),
    actions(actions_)
{}
void CWhile::accept(IVisitor *v) const{
    v->visit(this);
}
