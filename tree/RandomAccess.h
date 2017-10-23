#ifndef RANDOMACCESS_H
#define RANDOMACCESS_H

#include "Expression.h"

class CRandomAccess: public IExpression{
public:
    CRandomAccess(std::shared_ptr<IExpression> array_, std::shared_ptr<IExpression> position_):
        array(array_),
        position(position_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<IExpression> array;
    std::shared_ptr<IExpression> position;
};

#endif // RANDOMACCESS_H
