#ifndef RANDOMACCESS_H
#define RANDOMACCESS_H

#include "Visitor.h"

class IVisitor;

class CRandomAccess: public IExpression{
public:
    CRandomAccess(std::shared_ptr<IExpression> array_, std::shared_ptr<IExpression> position_);
    void accept(IVisitor *v) const;
private:
    std::shared_ptr<IExpression> array;
    std::shared_ptr<IExpression> position;
};

#endif // RANDOMACCESS_H
