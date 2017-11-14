#ifndef ASSIGN_H
#define ASSIGN_H

#include "Statement.h"
#include "../Expressions/Id.h"

class CAssignStatement: public IStatement{
public:
    CAssignStatement(std::shared_ptr<CId> left_, std::shared_ptr<IExpression> right_):
        left(left_),
        right(right_)
    {}
    void accept(IVisitor *v) const override;
    std::shared_ptr<CId> left;
    std::shared_ptr<IExpression> right;
};

#endif // ASSIGN_H
