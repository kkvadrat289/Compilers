#ifndef BASICTYPE_H
#define BASICTYPE_H

#include "Visitor.h"

class CBasicType: public INode{
public:
    enum BasicType{
        INT,
        BOOL,
        INT_ARRAY
    };
    CBasicType(BasicType type_): type(type_){}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    BasicType type;
}

#endif // BASICTYPE_H
