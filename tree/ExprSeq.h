#ifndef EXPRSEQ_H
#define EXPRSEQ_H

#include <vector>
#include "Visitor.h"
#include "Node.h"

class IVisitor;

class IExpressionSeq: public INode{
public:
    IExpressionSeq(std::shared_ptr<IExpression> exp);
    IExpressionSeq(std::shared_ptr<IExpressionSeq> exps, std::shared_ptr<IExpression> exp);
private:
    std::vector<std::shared_ptr<IExpression> > expressions;
};

#endif // EXPRSEQ_H
