#ifndef MAIN_H
#define MAIN_H

#include "Node.h"
#include "StatementSeq.h"
#include <string>

class CMain: public INode{
public:
    CMain(std::shared_ptr<CId> id_, std::shared_ptr<CId> paramId_, std::shared_ptr<CStatementSeq> statements_):
        id (id_),
        paramId(paramId_)
    {
        std::vector<std::shared_ptr<IStatement> > newVec(statements_->getVector());
        statements.clear();
        statements.swap(newVec);
    }
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<CId> id;
    std::shared_ptr<CId> paramId;
    std::vector<std::shared_ptr<IStatement> > statements;
};

#endif // MAIN_H
