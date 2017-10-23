#ifndef LENGTH_H
#define LENGTH_H

#include "Visitor.h"

class IVisitor;

class CLength: public IExpression{
public:
    CLength(std::shared_ptr<IExpression> object_);
    void accept(IVisitor *v) const;
private:
    std::shared_ptr<IExpression> object;
};

#endif // LENGTH_H
