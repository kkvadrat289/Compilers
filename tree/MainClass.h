#ifndef MAIN_H
#define MAIN_H

#include "Node.h"
#include "StatementSeq.h"
#include <string>

class CMain: public INode{
public:
    CMain(std::string class_, std::string param_, std::shared_ptr<CStatementSeq> statements_):
        className(class_),
        paramName(param_),
        statements(statements_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::string className;
    std::string paramName;
    std::shared_ptr<CStatementSeq> statements;
};

#endif // MAIN_H
