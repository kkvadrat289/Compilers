#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "Node.h"

class CVariable: public INode{
public:
    CVariable(std::shared_ptr<INode> type_, std::string name_):
        type(type_),
        name(name_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::shared_ptr<INode> type;
    std::string name;
};

#endif // VARIABLE_H
