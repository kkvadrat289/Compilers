#ifndef ID_H
#define ID_H

#include <string>
#include <iostream>
#include "Expression.h"

class CId: public IExpression{
public:
    CId(std::string name_, Position pos_):
        pos(pos_)
    {
        if (name_!=""){
            name = name_;
        }

    }
    void accept(IVisitor* v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::string name;
};

#endif // ID_H
