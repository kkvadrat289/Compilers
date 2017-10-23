#ifndef BASICTYPE_H
#define BASICTYPE_H

#include "Visitor.h"

class IVisitor;

class CBasicType: public INode{
public:
    enum BasicType{
        INT,
        BOOL,
        INT_ARRAY
    };
    CBasicType(BasicType type_);
    void accept(IVisitor *v) const;
private:
    BasicType type;
};

#endif // BASICTYPE_H
