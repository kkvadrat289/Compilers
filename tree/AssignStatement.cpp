#include "AssignStatement.h"


CAssignStatement::CAssignStatement(std::shared_ptr<CIdExp> left_, std::shared_ptr<INode> right_):
    left(left_),
    right(right_)
{}
void CAssignStatement::accept(IVisitor *v) const{
    v->visit(this);
}
