#ifndef STATEMENTSSEQ_H
#define STATEMENTSSEQ_H

#include "Statement.h"

class CStatementSeq: public IStatement{
public:
    CStatementSeq(std::shared_ptr<CStatementSeq> prev, std::shared_ptr<IStatement> newStatement_)
    {
        statements.clear();
        std::vector<std::shared_ptr<IStatement> > newVec(prev->getVector());
        statements.swap(newVec);
        statements.push_back(newStatement_);
    }
    CStatementSeq(std::shared_ptr<IStatement> statement){
        statements.clear();
        statements.push_back(statement);
    }
    std::vector<std::shared_ptr<IStatement> > getVector(){
        return statements;
    }
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::vector<std::shared_ptr<IStatement> > statements;
};

#endif // STATEMENTSSEQ_H
