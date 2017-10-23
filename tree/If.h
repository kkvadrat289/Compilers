#ifndef IF_H
#define IF_H

#include "Visitor.h"

class IVisitor;

class CIf: public IStatement{
public:
    CIf(std::shared_ptr<INode> cond_, std::shared_ptr<CStatementSeq> ifTrue_, std::shared_ptr<CStatementSeq> ifFalse_);
    void accept(IVisitor *v) const;
private:
    std::shared_ptr<INode> cond;
    std::shared_ptr<CStatementSeq> ifTrue;
    std::shared_ptr<CStatementSeq> ifFalse;
};

#endif // IF_H
