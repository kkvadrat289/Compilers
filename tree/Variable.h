#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include "Node.h"
#include "Visitor.h"

class CVariable: public INode{
public:
    CVariable(std::shared_ptr<INode> type_, std::string name_):
        type(type_),
        name(name_)
    {}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    std::shared_ptr<INode> type;
    std::string name;
}

#endif // VARIABLE_H
