#ifndef WHILE_H
#define WHILE_H

#include "Statement.h"

class CWhile: public IStatement{
public:
    CWhile(std::shared_ptr<IExpression> cond_, std::shared_ptr<IStatement> action_):
        cond(cond_),
        action(action_)
    {}
    void accept(IVisitor *v) const override;

private:
    std::shared_ptr<IExpression> cond;
    std::shared_ptr<IStatement> action;
};

#endif // WHILE_H
