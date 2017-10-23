#include "BinExpression.h"

CBinExpression::CBinExpression(std::shared_ptr<INode> left_, BinType type_, std::shared_ptr<INode> right_):
    type(type_),
    left(left_),
    right(right_)
{}

void CBinExpression::accept(IVisitor *v) const {
    v->visit(this);
}
