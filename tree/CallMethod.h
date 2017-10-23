#ifndef CALLMETHOD_H
#define CALLMETHOD_H

#include "Expression.h"

class CCallMethod: public IExpression{
public:
    CCallMethod(std::shared_ptr<INode> object_, std::string name_, std::shared_ptr<IExpressionSeq> params_):
        object(object_),
        name(name_)
    {
        //add to vector
    }
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<INode> object;
    std::string name;
    std::vector<std::shared_ptr<IExpression> > params;
};

#endif // CALLMETHOD_H
