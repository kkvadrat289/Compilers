#ifndef CALLMETHOD_H
#define CALLMETHOD_H

#include "Expression.h"

class CCallMethod: public IExpression{
public:
    CCallMethod(std::shared_ptr<IExpression> expression_, std::shared_ptr<CId> id_, std::shared_ptr<IExpressionSeq> params_):
        expression(expression_),
        id(id_)
    {
        params.clear();
        if(params_){
            std::vector<std::shared_ptr<IExpression> > newVec(params_->getVector());
            params.swap(newVec);
        }
    }
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<IExpression> expression;
    std::shared_ptr<CId> id;
    std::vector<std::shared_ptr<IExpression> > params;
};

#endif // CALLMETHOD_H
