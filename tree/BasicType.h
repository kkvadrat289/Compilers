#ifndef BASICTYPE_H
#define BASICTYPE_H

#include "Node.h"

class CBasicType: public INode{
public:
    enum BasicType{
        INT,
        BOOL,
        INT_ARRAY
    };
    CBasicType(BasicType type_): type(type_){}
    void accept(IVisitor *v) const override;
private:
    BasicType type;
}

#endif // BASICTYPE_H
