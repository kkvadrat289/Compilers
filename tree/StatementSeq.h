#ifndef STATEMENTSSEQ_H
#define STATEMENTSSEQ_H

#include "Statement.h"

class CStatementSeq: public IStatement{
public:
    CStatementSeq(std::shared_ptr<CStatementSeq> prev, std::shared_ptr<IStatement> newStatement_):
        previousStatements(prev),
        newStatement(newStatement_)
    {}
    void accept(IVisitor *v) const{
        //pass
    }
private:
    std::shared_ptr<CStatementSeq> previousStatements;
    std::shared_ptr<IStatement> newStatement;
};

#endif // STATEMENTSSEQ_H
