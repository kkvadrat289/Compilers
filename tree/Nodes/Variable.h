#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "Node.h"
#include "Type.h"

class CVariable: public INode{
public:
    CVariable(std::shared_ptr<IType> type_, std::shared_ptr<CId> id_, Position pos_):
        type(type_),
        id(id_),
        pos(pos_)
    {}
    std::string GetUserClassName(){return id->name;}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<IType> type;
    std::shared_ptr<CId> id;
};

#endif // VARIABLE_H
