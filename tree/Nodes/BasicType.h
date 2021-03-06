#ifndef BASICTYPE_H
#define BASICTYPE_H

#include "Node.h"

enum BasicType{
    INT_,
    BOOL_,
    INT_ARRAY_,
    NON_BASIC
};

class CBasicType: public IType{
public:

    CBasicType(BasicType type_): type(type_){
        if (type == INT_) label = "int";
        if (type == BOOL_) label = "bool";
        if (type == INT_ARRAY_) label = "int[]";
    }
    virtual const Position& GetPosition() const {
        return pos;
    }
    Position pos;
    BasicType type;
};

#endif // BASICTYPE_H
