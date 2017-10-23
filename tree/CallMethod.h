#ifndef CALLMETHOD_H
#define CALLMETHOD_H

#include "Visitor.h"

class IVisitor;

class CCallMethod: public IExpression{
public:
    CCallMethod(std::shared_ptr<INode> object_, std::string name_, std::shared_ptr<IExpressionSeq> params_);
    void accept(IVisitor *v) const;
private:
    std::shared_ptr<INode> object;
    std::string name;
    std::shared_ptr<IExpressionSeq> params;
};

#endif // CALLMETHOD_H
