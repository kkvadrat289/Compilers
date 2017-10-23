#ifndef METHODSEQ_H
#define METHODSEQ_H

#include "Method.h"

class CMethodSeq{
public:
    CMethodSeq(std::shared_ptr<CMethodSeq> prev, std::shared_ptr<CMethod> newMethod_):
        previousMethods(prev),
        newMethod(newMethod_)
    {}
private:
    std::shared_ptr<CMethodSeq> previousMethods;
    std::shared_ptr<CMethod> newMethod;
}

#endif // METHODSEQ_H
