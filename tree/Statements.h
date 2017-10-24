#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "Statement.h"

class CStatements: public IStatement{
public:
    CStatements(std::shared_ptr<CStatementSeq> statements_){
        std::vector<std::shared_ptr<IStatement> > newVec(statements_->getVector());
        statements.clear();
        statements.swap(newVec);
    }
    void accept(IVisitor *v) const override;
private:
    std::vector<std::shared_ptr<IStatement> > statements;
};

#endif // STATEMENTS_H
