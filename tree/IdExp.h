#ifndef IDEXP_H
#define IDEXP_H

#include "Visitor.h"

class CIdExp: public IExpression{
public:
    CIdExp(std::string id_): id(id_){}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    std::string id;
}

#endif // IDEXP_H
