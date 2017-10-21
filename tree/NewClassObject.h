#ifndef NEWCLASSOBJECT_H
#define NEWCLASSOBJECT_H

#include "Visitor.h"

class CNewClassObject: public IExpression{
public:
    CNewClassObject(std::string name_):
        name(name_)
    {}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    std::string name;
}

#endif // NEWCLASSOBJECT_H
