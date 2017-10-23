#ifndef ASSIGN_H
#define ASSIGN_H

#include "Statement.h"
#include "IdExp.h"

class CAssignStatement: public IStatement{
public:
    CAssignStatement(std::shared_ptr<CIdExp> left_, std::shared_ptr<INode> right_):
        left(left_),
        right(right_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<CIdExp> left;
    std::shared_ptr<INode> right;
};

#endif // ASSIGN_H
