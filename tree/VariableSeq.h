#ifndef VARIABLESEQ_H
#define VARIABLESEQ_H

#include "Variable.h"

class CVariableSeq{
public:
    CVariableSeq(std::shared_ptr<CVariableSeq> prev, std::shared_ptr<CVariable> newVar_):
        previousVars(prev),
        newVar(newVar_)
    {}
private:
    std::shared_ptr<CVariableSeq> previousVars;
    std::shared_ptr<CVariable> newVar;
};

#endif // VARIABLESEQ_H
