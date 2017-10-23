#ifndef PROGRAM_H
#define PROGRAM_H

#include "Node.h"
#include "Visitor.h"
#include <vector>
#include <memory>

class IVisitor;
class CClassSeq;

class CProgram: public INode{
public:
    CProgram(std::shared_ptr<CMain> main_, std::shared_ptr<CClassSeq> classes_);
    void accept(IVisitor *v) const ;

private:
   std::shared_ptr<CMain> main;
   std::shared_ptr<CClassSeq> classes;
};

#endif // PROGRAM_H
