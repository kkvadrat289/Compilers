#ifndef MAIN_H
#define MAIN_H

#include "Node.h"
#include <string>
#include <memory>
#include "Visitor.h"

class IVisitor;
class CStatementSeq;

class CMain: public INode{
public:
    CMain(std::string class_, std::string param_, std::shared_ptr<CStatementSeq> statements_);
    void accept(IVisitor *v) const;
private:
    std::string className;
    std::string paramName;
    std::shared_ptr<CStatementSeq> statements;
};

#endif // MAIN_H
