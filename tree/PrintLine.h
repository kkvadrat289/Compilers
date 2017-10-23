#ifndef PRINTLINE_H
#define PRINTLINE_H

#include "Visitor.h"

class CPrintLine: public IStatement{
public:
    CPrintLine(std::shared_ptr<IExpression> object_):
        object(object_)
    {}
    void accept(IVisitor *v) const{
        v->visit(this);
    }
private:
    std::shared_ptr<IExpression> object;
}

#endif // PRINTLINE_H
