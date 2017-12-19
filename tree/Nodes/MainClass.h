#ifndef MAIN_H
#define MAIN_H

#include "Node.h"
#include "statements/StatementSeq.h"
#include <string>

class CMain: public INode{
public:
    CMain(std::shared_ptr<CId> id_, std::shared_ptr<CId> paramId_, std::shared_ptr<CStatementSeq> statements_,
          Position pos_):
        id (id_),
        pos(pos_),
        paramId(paramId_)
    {
        std::vector<std::shared_ptr<IStatement> > newVec(statements_->getVector());
        statements.clear();
        statements.swap(newVec);
    }
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<CId> id;
    std::shared_ptr<CId> paramId;
    std::vector<std::shared_ptr<IStatement> > statements;
};

#endif // MAIN_H
