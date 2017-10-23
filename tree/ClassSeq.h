#ifndef CLASSSEQ_H
#define CLASSSEQ_H

#include "Node.h"
#include "Visitor.h"

class IVisitor;

class CClassSeq{
public:
    CClassSeq(std::shared_ptr<CClassSeq> prev, std::shared_ptr<CClass> newClass_);
private:
    std::shared_ptr<CClassSeq> previousClasses;
    std::shared_ptr<CClass> newClass;
};

#endif // CLASSSEQ_H
