#ifndef PRINTLINE_H
#define PRINTLINE_H

#include "Statement.h"

class CPrintLine: public IStatement{
public:
    CPrintLine(std::shared_ptr<IExpression> object_, Position pos_):
        object(object_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<IExpression> object;
};

#endif // PRINTLINE_H
