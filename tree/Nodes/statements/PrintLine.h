#ifndef PRINTLINE_H
#define PRINTLINE_H

#include "Statement.h"

class CPrintLine: public IStatement{
public:
    CPrintLine(std::shared_ptr<IExpression> object_):
        object(object_)
    {}
    void accept(IVisitor *v) const override;

    std::shared_ptr<IExpression> object;
};

#endif // PRINTLINE_H
