#ifndef NEWCLASSOBJECT_H
#define NEWCLASSOBJECT_H

#include "Expression.h"

class CNewClassObject: public IExpression{
public:
    CNewClassObject(std::string name_):
        name(name_)
    {}
    void accept(IVisitor *v) const override;
private:
    std::string name;
};

#endif // NEWCLASSOBJECT_H
