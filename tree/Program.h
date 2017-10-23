#ifndef PROGRAM_H
#define PROGRAM_H

#include "Node.h"
#include "ClassSeq.h"
#include <vector>

class CProgram: public INode{
public:
    CProgram(std::shared_ptr<CMain> main_, std::shared_ptr<CClassSeq> classes_):
      main(main_)
    {
        classes.clear();
        std::vector<std::shared_ptr<CClass> > newVec(classes_->getVector());
        classes.swap(newVec);
    }
    void accept(IVisitor *v) const  override;

private:
   std::shared_ptr<CMain> main;
   std::vector<std::shared_ptr<CClass> > classes;
};

#endif // PROGRAM_H
