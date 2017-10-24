#ifndef BASICTYPE_H
#define BASICTYPE_H

#include "Node.h"

enum BasicType{
    INT_,
    BOOL_,
    INT_ARRAY_
};

class CBasicType: public IType{
public:

    CBasicType(BasicType type_): type(type_){}
private:
    BasicType type;
};

#endif // BASICTYPE_H
