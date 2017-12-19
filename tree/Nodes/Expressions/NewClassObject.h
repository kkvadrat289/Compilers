#ifndef NEWCLASSOBJECT_H
#define NEWCLASSOBJECT_H

#include "Expression.h"

class CNewClassObject: public IExpression{
public:
    CNewClassObject(std::shared_ptr<CId> id_, Position pos_):
        id(id_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<CId> id;
};

#endif // NEWCLASSOBJECT_H
