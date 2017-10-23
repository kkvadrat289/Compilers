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
        expressions.clear();
        std::vector<std::shared_ptr<IExpression> > newVec(exps->getVector());
        newVec.push_back(exp);
        expressions.swap(newVec);
    }
    std::vector<std::shared_ptr<IExpression> > getVector(){
        return expressions;
    }
private:
    std::vector<std::shared_ptr<IExpression> > expressions;
};

#endif // EXPRSEQ_H
