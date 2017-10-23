#ifndef IF_H
#define IF_H

#include "Statement.h"
#include "StatementSeq.h"

class CIf: public IStatement{
public:
    CIf(std::shared_ptr<INode> cond_, std::shared_ptr<CStatementSeq> ifTrue_, std::shared_ptr<CStatementSeq> ifFalse_):
        cond(cond_)
    {
        ifTrue.clear();
        ifFalse.clear();
        std::vector<std::shared_ptr<IStatement> > newVecTrue(ifTrue_->getVector());
        ifTrue.swap(newVecTrue);
        std::vector<std::shared_ptr<IStatement> > newVecFalse(ifFalse_->getVector());
        ifFalse.swap(newVecFalse);
    }
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<INode> cond;
    std::vector<std::shared_ptr<IStatement> > ifTrue;
    std::vector<std::shared_ptr<IStatement> > ifFalse;
};

#endif // IF_H
