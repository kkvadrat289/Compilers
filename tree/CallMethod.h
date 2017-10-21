#ifndef CALLMETHOD_H
#define CALLMETHOD_H

#include "Visitor.h"

class CCallMethod: public IExpression{
public:
    CCallMethod(std::shared_ptr<CExpSeq> params_):
        params(params_)
    {}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    std::shared_ptr<CExpSeq> params;
}

#endif // CALLMETHOD_H
