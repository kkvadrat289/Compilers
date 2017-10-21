#ifndef PROGRAM_H
#define PROGRAM_H

#include "Node.h"
#include <vector>
#include <memory>

class CProgram: public INode{
public:
    CProgram(std::shared_ptr<CMain> main_, std::shared_ptr<CClassSeq> classes_):
      main(main_),
      classes(classes_)
    {}
    void accept(IVisitor *v) const {
        v->visit(this);
    }

private:
   std::shared_ptr<CMain> main;
   std::shared_ptr<CClassSeq> classes;
}

#endif // PROGRAM_H
