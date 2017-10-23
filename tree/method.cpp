#include "Method.h"

CMethod::CMethod(std::string modifier_, std::shared_ptr<INode> type_, std::string name_, std::shared_ptr<CVariableSeq> params_,
         std::shared_ptr<CVariableSeq> vars_, std::shared_ptr<CStatementSeq> statements_,std::shared_ptr<INode> res_):
    modifier(modifier_),
    type(type_),
    name(name_),
    params(params_),
    vars(vars_),
    statements(statements_),
    res(res_)
{}
void CMethod::accept(IVisitor *v) const {
    v->visit(this);
}
