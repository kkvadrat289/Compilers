#ifndef ARGS_H
#define ARGS_H

#include "Arg.h"
#include "Id.h"
#include "Type.h"
#include "Variable.h"

class CArgs{
public:
    CArgs(){
        vars.clear();
    }
    CArgs(std::shared_ptr<CArgs> prev, std::shared_ptr<IType> type_, std::shared_ptr<CId> id_)
    {
        CArg *newArg = new CArg(type_, id_);
        vars.clear();
        std::vector<std::shared_ptr<CArg> > newVec(prev->getVector());
        vars.swap(newVec);
        vars.push_back(std::shared_ptr<CArg>(newArg));
    }
    CArgs(std::shared_ptr<IType> type_,std::shared_ptr<CId> id_){
        vars.clear();
        CArg *newArg = new CArg(type_, id_);
        vars.push_back(std::shared_ptr<CArg>(newArg));
    }

    std::vector<std::shared_ptr<CArg> > getVector(){
        return vars;
    }
private:
    std::vector<std::shared_ptr<CArg> > vars;
};

#endif // ARGS_H
