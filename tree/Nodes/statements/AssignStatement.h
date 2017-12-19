#ifndef ASSIGN_H
#define ASSIGN_H

#include "Statement.h"
#include "../Expressions/Id.h"

class CAssignStatement: public IStatement{
public:
    CAssignStatement(std::shared_ptr<CId> left_, std::shared_ptr<IExpression> right_, Position pos_):
        left(left_),
        right(right_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<CId> left;
    std::shared_ptr<IExpression> right;
};

#endif // ASSIGN_H
