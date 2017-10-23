#include "Program.h"

CProgram::CProgram(std::shared_ptr<CMain> main_, std::shared_ptr<CClassSeq> classes_):
  main(main_),
  classes(classes_)
{}
void CProgram::accept(IVisitor *v) const {
    v->visit(this);
}
