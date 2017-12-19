#ifndef CLASSTYPE_H
#define CLASSTYPE_H

#include "Type.h"

class CClassType: public IType{
public:
    CClassType(std::shared_ptr<CId> id_):
        id(id_)
    {
       // label = "class";
        label = id->name;
    }

    std::shared_ptr<CId> id;
};

#endif // CLASSTYPE_H
