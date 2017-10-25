#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "Node.h"
#include "Type.h"

class CVariable: public INode{
public:
    CVariable(std::shared_ptr<IType> type_, std::shared_ptr<CId> id_):
        type(type_),
        id(id_)
    {}
    void accept(IVisitor *v) const override;

    std::shared_ptr<IType> type;
    std::shared_ptr<CId> id;
};

#endif // VARIABLE_H
