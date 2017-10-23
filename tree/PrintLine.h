#ifndef PRINTLINE_H
#define PRINTLINE_H

#include "Visitor.h"

class IVisitor;

class CPrintLine: public IStatement{
public:
    CPrintLine(std::shared_ptr<IExpression> object_);
    void accept(IVisitor *v) const;
private:
    std::shared_ptr<IExpression> object;
};

#endif // PRINTLINE_H
