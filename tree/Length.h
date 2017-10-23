#ifndef LENGTH_H
#define LENGTH_H

#include "Expression.h"

class CLength: public IExpression{
public:
    CLength(std::shared_ptr<IExpression> object_):
        object(object_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<IExpression> object;
};

#endif // LENGTH_H
