#ifndef WHILE_H
#define WHILE_H

#include "Statement.h"

class CWhile: public IStatement{
public:
    CWhile(std::shared_ptr<IExpression> cond_, std::shared_ptr<CStatementSeq> actions_):
        cond(cond_)
    {
        actions.clear();
        std::vector<std::shared_ptr<IStatement> > newVec(actions_->getVector());
        actions.swap(newVec);
    }
    void accept(IVisitor *v) const override;

private:
    std::shared_ptr<IExpression> cond;
    std::vector<std::shared_ptr<IStatement> > actions;
};

#endif // WHILE_H
