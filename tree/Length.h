#ifndef LENGTH_H
#define LENGTH_H

#include "Visitor.h"

class CLength: public IExpression{
public:
    CLength(std::shared_ptr<IExpression> object_):
        object(object_)
    {}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    std::shared_ptr<IExpression> object;
}

#endif // LENGTH_H
