#ifndef CLASSSEQ_H
#define CLASSSEQ_H

#include "Node.h"
#include "Class.h"

class CClassSeq{
public:
    CClassSeq(std::shared_ptr<CClassSeq> prev, std::shared_ptr<CClass> newClass_)
    {
        classes.clear();
        std::vector<std::shared_ptr<CClass> > newVec(prev->getVector());
        newVec.push_back(newClass_);
        classes.swap(newVec);
    }
    CClassSeq(std::shared_ptr<CClass> class_){
        classes.clear();
        classes.push_back(class_);
    }
    std::vector<std::shared_ptr<CClass> > getVector(){
        return classes;
    }
private:
    std::vector<std::shared_ptr<CClass> > classes;
};

#endif // CLASSSEQ_H
