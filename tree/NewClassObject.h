#ifndef NEWCLASSOBJECT_H
#define NEWCLASSOBJECT_H

#include "Visitor.h"

class IVisitor;

class CNewClassObject: public IExpression{
public:
    CNewClassObject(std::string name_);
    void accept(IVisitor *v) const;
private:
    std::string name;
};

#endif // NEWCLASSOBJECT_H
