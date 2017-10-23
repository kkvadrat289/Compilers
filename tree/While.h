#ifndef WHILE_H
#define WHILE_H

#include "Visitor.h"

class IVisitor;

class CWhile: public IStatement{
public:
    CWhile(std::shared_ptr<IExpression> cond_, std::shared_ptr<IStatement> actions_);
    void accept(IVisitor *v) const;
private:
    std::shared_ptr<IExpression> cond;
    std::shared_ptr<IStatement> actions;
};

#endif // WHILE_H
