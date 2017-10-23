#ifndef BINEXPRESSION_H
#define BINEXPRESSION_H

#include "Visitor.h"
#include "Expression.h"
#include <memory>

class IVisitor;

class CBinExpression: public IExpression{
public:
    enum BinType { AND,
                   OR,
                   LESS,
                   PLUS,
                   MINUS,
                   TIMES,
                   MOD
    };

    CBinExpression(std::shared_ptr<INode> left_, BinType type_, std::shared_ptr<INode> right_);

    void accept(IVisitor *v) const ;
private:
    BinType type;
    std::shared_ptr<INode> left;
    std::shared_ptr<INode> right;
};

#endif // BINEXPRESSION_H
