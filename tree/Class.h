#ifndef CLASS_H
#define CLASS_H

#include "Visitor.h"
#include <memory>
#include <vector>

class IVisitor;
class CVariable;
class CMethodSeq;
class CVariableSeq;

class CClass: public INode{
public:
    CClass(std::string name_, std::string extends_, std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CMethodSeq> methods_);
    CClass(std::string name_, std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CMethodSeq> methods_);
    void accept(IVisitor *v) const;
private:
    std::string name;
    std::string extends;
    std::vector<std::shared_ptr<CVariable> > vars;
    std::vector<std::shared_ptr<CMethod> >methods;
};

#endif // CLASS_H
