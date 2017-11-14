#ifndef VARIABLESEQ_H
#define VARIABLESEQ_H

#include "Variable.h"

class CVariableSeq{
public:
    CVariableSeq(std::shared_ptr<CVariableSeq> prev, std::shared_ptr<CVariable> newVar_)
    {
        vars.clear();
        std::vector<std::shared_ptr<CVariable> > newVec(prev->getVector());
        vars.swap(newVec);
        vars.push_back(newVar_);
    }
    CVariableSeq(std::shared_ptr<CVariable> var){
        vars.clear();
        vars.push_back(var);
    }

    std::vector<std::shared_ptr<CVariable> > getVector(){
        return vars;
    }

    std::vector<std::shared_ptr<CVariable> > vars;
};

#endif // VARIABLESEQ_H
