#ifndef ALLPROBLEMSSOLUTION_CPP
#define ALLPROBLEMSSOLUTION_CPP

#include "visitors/Visitor.h"

void CAssignStatement::accept(IVisitor *v) const{
    v->visit(this);
}
void CStatementSeq::accept(IVisitor *v) const{
    v->visit(this);
}
void CBinExpression::accept(IVisitor *v) const{
    v->visit(this);
}
void CId::accept(IVisitor *v) const{
    v->visit(this);
}
void CTrue::accept(IVisitor *v) const{
    v->visit(this);
}
void CFalse::accept(IVisitor *v) const{
    v->visit(this);
}
void CClass::accept(IVisitor *v) const{
    v->visit(this);
}
void CMethod::accept(IVisitor *v) const{
    v->visit(this);
}
void CProgram::accept(IVisitor *v) const{
    v->visit(this);
}
void CBooleanExp::accept(IVisitor *v) const{
    v->visit(this);
}
void CIntegerExp::accept(IVisitor *v) const{
    v->visit(this);
}
void CIf::accept(IVisitor *v) const{
    v->visit(this);
}

void CNotExp::accept(IVisitor *v) const{
    v->visit(this);
}
void CCallMethod::accept(IVisitor *v) const{
    v->visit(this);
}
void CNewIntArray::accept(IVisitor *v) const{
    v->visit(this);
}
void CNewClassObject::accept(IVisitor *v) const{
    v->visit(this);
}
void CRandomAccessAssign::accept(IVisitor *v) const{
    v->visit(this);
}
void CLength::accept(IVisitor *v) const{
    v->visit(this);
}
void CPrintLine::accept(IVisitor *v) const{
    v->visit(this);
}
void CWhile::accept(IVisitor *v) const{
    v->visit(this);
}
void CStatements::accept(IVisitor *v) const{
    v->visit(this);
}
void CRandomAccess::accept(IVisitor *v) const{
    v->visit(this);
}
void CArg::accept(IVisitor *v) const{
    v->visit(this);
}
void CMain::accept(IVisitor *v) const{
    v->visit(this);
}
void CThis::accept(IVisitor *v) const{
    v->visit(this);
}
void CVariable::accept(IVisitor *v) const{
    v->visit(this);
}
INode::~INode(){}


#endif // ACCEPTVISITOR_CPP
