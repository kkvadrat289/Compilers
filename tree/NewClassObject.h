#ifndef NEWCLASSOBJECT_H
#define NEWCLASSOBJECT_H

#include "Expression.h"

class CNewClassObject: public IExpression{
public:
    CNewClassObject(std::shared_ptr<CId> id_):
        id(id_)
    {}
    void accept(IVisitor *v) const override;

    std::shared_ptr<CId> id;
};

#endif // NEWCLASSOBJECT_H
