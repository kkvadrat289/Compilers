#ifndef EXPRSEQ_H
#define EXPRSEQ_H

#include <vector>
#include "Node.h"
#include "Expression.h"

class IVisitor;

class IExpressionSeq: public INode{
public:
    IExpressionSeq(std::shared_ptr<IExpression> exp){
        expressions.clear();
        expressions.push_back(exp);
    }
    IExpressionSeq(std::shared_ptr<IExpressionSeq> exps, std::shared_ptr<IExpression> exp){
        //add to vector
    }
private:
    std::vector<std::shared_ptr<IExpression> > expressions;
};

#endif // EXPRSEQ_H
