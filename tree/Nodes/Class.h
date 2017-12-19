#ifndef CLASS_H
#define CLASS_H

#include "Node.h"
#include "VariableSeq.h"
#include "MethodSeq.h"

class CClass: public INode{
public:
    CClass(std::shared_ptr<CId> id_, std::shared_ptr<CId> extends_, std::shared_ptr<CVariableSeq> vars_,
           std::shared_ptr<CMethodSeq> methods_, Position pos_):
        id(id_),
        extends(extends_),
        pos(pos_)
    {
        std::vector<std::shared_ptr<CVariable> > newVec(vars_->getVector());
        vars.clear();
        vars.swap(newVec);
        std::vector<std::shared_ptr<CMethod> > newVecM(methods_->getVector());
        methods.clear();
        methods.swap(newVecM);
    }
    CClass(std::shared_ptr<CId> id_, std::shared_ptr<CId> extends_, std::shared_ptr<CVariableSeq> vars_,
           Position pos_):
        id(id_),
        extends(extends_),
        pos(pos_)
    {
        std::vector<std::shared_ptr<CVariable> > newVec(vars_->getVector());
        vars.clear();
        vars.swap(newVec);
    }
    CClass(std::shared_ptr<CId> id_, std::shared_ptr<CId> extends_, std::shared_ptr<CMethodSeq> methods_, Position pos_):
        id(id_),
        extends(extends_),
        pos(pos_)
    {
        std::vector<std::shared_ptr<CMethod> > newVecM(methods_->getVector());
        methods.clear();
        methods.swap(newVecM);
    }
    CClass(std::shared_ptr<CId> id_, std::shared_ptr<CId> extends_, Position pos_):
        id(id_),
        extends(extends_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;

    std::shared_ptr<CId> id;
    std::shared_ptr<CId> extends;
    std::vector<std::shared_ptr<CVariable> > vars;
    std::vector<std::shared_ptr<CMethod> > methods;
};

#endif // CLASS_H
