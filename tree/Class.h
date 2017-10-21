#ifndef CLASS_H
#define CLASS_H

#include "Node.h"
#include "Visitor.h"

class CClass: public INode{
public:
    CClass(std::string name_, std::string extends_, std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CMethodSeq> methods_):
        name(name_),
        extends(extends_),
        vars(vars_),
        methods(methods_)
    {}
    CClass(std::string name_, std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CMethodSeq> methods_):
        name(name_),
        vars(vars_),
        methods(methods_)
    {}
    void accept(IVisitor *v) const{
          v->visit(this);
    }
private:
    std::string name;
    std::string extends;
    std::shared_ptr<CVariableSeq> vars;
    std::shared_ptr<CMethodSeq> methods;
}

#endif // CLASS_H
