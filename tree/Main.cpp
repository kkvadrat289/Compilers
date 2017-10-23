#include "Main.h"

CMain::CMain(std::string class_, std::string param_, std::shared_ptr<CStatementSeq> statements_):
    className(class_),
    paramName(param_),
    statements(statements_)
{}
void CMain::accept(IVisitor *v) const{
    v->visit(this);
}
