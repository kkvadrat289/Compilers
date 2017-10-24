#ifndef CLASSTYPE_H
#define CLASSTYPE_H

#include "Type.h"

class CClassType: public IType{
public:
    CClassType(std::shared_ptr<CId> id_):
        id(id_)
    {}
private:
    std::shared_ptr<CId> id;
};

#endif // CLASSTYPE_H
