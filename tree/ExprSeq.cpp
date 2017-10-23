#include "ExprSeq.h"

IExpressionSeq::IExpressionSeq(std::shared_ptr<IExpression> exp):
{
    expressions.assign(1, exp);
}
IExpressionSeq::IExpressionSeq(std::shared_ptr<IExpressionSeq> exps, std::shared_ptr<IExpression> exp){

    //add vector
}
