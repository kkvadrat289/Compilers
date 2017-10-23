#ifndef METHODSEQ_H
#define METHODSEQ_H

#include "Method.h"

class CMethodSeq{
public:
    CMethodSeq(std::shared_ptr<CMethodSeq> prev, std::shared_ptr<CMethod> newMethod_)
    {
        methods.clear();
        std::vector<std::shared_ptr<CMethod> > newVec(prev->getVector());
        methods.swap(newVec);
        methods.push_back(newMethod_);
    }
    CMethodSeq(std::shared_ptr<CMethod> method){
        methods.clear();
        methods.push_back(method);
    }
    std::vector<std::shared_ptr<CMethod> > getVector(){
        return methods;
    }
private:
    std::vector<std::shared_ptr<CMethod> > methods;
};

#endif // METHODSEQ_H
