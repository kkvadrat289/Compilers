#ifndef IF_H
#define IF_H

#include "Statement.h"
#include "StatementSeq.h"

class CIf: public IStatement{
public:
    CIf(std::shared_ptr<INode> cond_, std::shared_ptr<CStatementSeq> ifTrue_, std::shared_ptr<CStatementSeq> ifFalse_):
        cond(cond_),
        ifTrue(ifTrue_),
        ifFalse(ifFalse_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<INode> cond;
    std::shared_ptr<CStatementSeq> ifTrue;
    std::shared_ptr<CStatementSeq> ifFalse;
};

#endif // IF_H
