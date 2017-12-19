#ifndef PROGRAM_H
#define PROGRAM_H

#include "Node.h"
#include "ClassSeq.h"
#include <vector>

class CProgram: public INode{
public:
    CProgram(std::shared_ptr<CMain> main_, std::shared_ptr<CClassSeq> classes_, Position pos_):
      main(main_),
      pos(pos_)
    {
        classes.clear();
        std::vector<std::shared_ptr<CClass> > newVec(classes_->getVector());
        classes.swap(newVec);
    }
    CProgram(std::shared_ptr<CMain> main_, Position pos_):
        main(main_),
        pos(pos_)
    { }
    void SetPosition(int line, int coloumn){
        pos = Position(line, coloumn);
    }

    void accept(IVisitor *v) const  override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<CMain> main;
    std::vector<std::shared_ptr<CClass> > classes;
};

#endif // PROGRAM_H
