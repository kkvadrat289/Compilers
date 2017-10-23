#ifndef METHOD_H
#define METHOD_H

#include "Node.h"

class CMethod: public INode{
public:
    CMethod(std::string modifier_, std::shared_ptr<INode> type_, std::string name_, std::shared_ptr<CVariableSeq> params_,
             std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CStatementSeq> statements_,std::shared_ptr<INode> res_):
        modifier(modifier_),
        type(type_),
        name(name_),
        res(res_)
    {
        std::vector<std::shared_ptr<CVariable> > newVecP(params_->getVector());
        params.clear();
        params.swap(newVecP);

        std::vector<std::shared_ptr<CVariable> > newVecV(vars_->getVector());
        vars.clear();
        vars.swap(newVecV);

        std::vector<std::shared_ptr<IStatement> > newVec(statements_->getVector());
        statements.clear();
        statements.swap(newVec);
    }
    void accept(IVisitor *v) const  override;
private:
    std::string modifier;
    std::shared_ptr<INode> type;
    std::string name;
    std::vector<std::shared_ptr<CVariable> > params;
    std::vector<std::shared_ptr<CVariable> > vars;
    std::vector<std::shared_ptr<IStatement> > statements;
    std::shared_ptr<INode> res;
};

#endif // METHOD_H
