#ifndef IDEXP_H
#define IDEXP_H

#include "Expression.h"

class CIdExp: public IExpression{
public:
    CIdExp(std::string id_): id(id_){}
    void accept(IVisitor *v) const override;

    std::string id;
};

#endif // IDEXP_H
