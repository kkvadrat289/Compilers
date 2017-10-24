#ifndef ARG_H
#define ARG_H

#include <string>
#include "Node.h"
#include "Type.h"

class CArg: public INode{
public:
    CArg(std::shared_ptr<IType> type_, std::shared_ptr<CId> id_):
        type(type_),
        id(id_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<IType> type;
    std::shared_ptr<CId> id;
};

#endif // ARG_H
