#ifndef METHOD_H
#define METHOD_H

#include "Node.h"
#include "Visitor.h"

class CMethod: public INode{
public:
    CMethod(std::string modifier_, std::shared_ptr<INode> type_, std::string name_, std::shared_ptr<CVariableSeq> params_,
             std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CStatementSeq> statements_,std::shared_ptr<INode> res_):
        modifier(modifier_),
        type(type_),
        name(name_),
        params(params_),
        vars(vars_),
        statements(statements_),
        res(res_)
    {}
    void accept(IVisitor *v) const {
        v->visit(this);
    }
private:
    std::string modifier;
    std::shared_ptr<INode> type;
    std::string name;
    std::shared_ptr<CVariableSeq> params;
    std::shared_ptr<CVariableSeq> vars;
    std::shared_ptr<CStatementSeq> statements;
    std::shared_ptr<INode> res;
}

#endif // METHOD_H
