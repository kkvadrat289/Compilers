#ifndef ASSIGN_H
#define ASSIGN_H

#include "Visitor.h"

class IVisitor;

class CAssignStatement: public IStatement{

public:
    CAssignStatement(std::shared_ptr<CIdExp> left_, std::shared_ptr<INode> right_);
    void accept(IVisitor *v) const;
private:
    std::shared_ptr<CIdExp> left;
    std::shared_ptr<INode> right;
};

#endif // ASSIGN_H
