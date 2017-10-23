#ifndef IDEXP_H
#define IDEXP_H

#include "Visitor.h"

class IVisitor;

class CIdExp: public IExpression{
public:
    CIdExp(std::string id_);
    void accept(IVisitor *v) const;
private:
    std::string id;
};

#endif // IDEXP_H
