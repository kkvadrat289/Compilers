#ifndef CLASS_H
#define CLASS_H

#include "Node.h"
#include "VariableSeq.h"
#include "MethodSeq.h"

class CClass: public INode{
public:
    CClass(std::string name_, std::string extends_, std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CMethodSeq> methods_):
        name(name_),
        extends(extends_),
        methods(methods_)
    {
        //add to vector
    }
    CClass(std::string name_, std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CMethodSeq> methods_):
        name(name_),
        methods(methods_)
    {
        //add to vector
    }
    void accept(IVisitor *v) const override;
private:
    std::string name;
    std::string extends;
    std::shared_ptr<std::shared_ptr<CVariable> > vars;
    std::shared_ptr<CMethodSeq> methods;
};

#endif // CLASS_H
