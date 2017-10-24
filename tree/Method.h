#ifndef METHOD_H
#define METHOD_H

#include "Node.h"
#include "Args.h"

class CMethod: public INode{
public:
    CMethod(std::shared_ptr<IType> type_, std::shared_ptr<CId> id_, std::shared_ptr<CArgs> params_,
             std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CStatementSeq> statements_,std::shared_ptr<IExpression> res_):
        type(type_),
        id(id_),
        res(res_)
    {
        params.clear();
        if (params_){
            std::vector<std::shared_ptr<CArg> > newVecP(params_->getVector());
            params.swap(newVecP);
        }

        vars.clear();
        if (vars_){
            std::vector<std::shared_ptr<CVariable> > newVecV(vars_->getVector());
            vars.swap(newVecV);
        }

        statements.clear();
        if (statements_){
            std::vector<std::shared_ptr<IStatement> > newVec(statements_->getVector());
            statements.swap(newVec);
        }
    }
    void accept(IVisitor *v) const  override;
private:
    std::shared_ptr<IType> type;
    std::shared_ptr<CId> id;
    std::vector<std::shared_ptr<CArg> > params;
    std::vector<std::shared_ptr<CVariable> > vars;
    std::vector<std::shared_ptr<IStatement> > statements;
    std::shared_ptr<IExpression> res;
};

#endif // METHOD_H
