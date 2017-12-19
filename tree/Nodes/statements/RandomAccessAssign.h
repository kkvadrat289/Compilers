#ifndef RANDOMACCESSASSIGN_H
#define RANDOMACCESSASSIGN_H

#include "Statement.h"

class CRandomAccessAssign: public IStatement{
public:
    CRandomAccessAssign(std::shared_ptr<CId> id_, std::shared_ptr<IExpression> position_, std::shared_ptr<IExpression> expression_,
                        Position pos_):
        id(id_),
        position(position_),
        expression(expression_),
        pos(pos_)
    {}
    void accept(IVisitor *v) const override;
    virtual const Position& GetPosition() const {
        return pos;
    }

    Position pos;
    std::shared_ptr<CId> id;
    std::shared_ptr<IExpression> position;
    std::shared_ptr<IExpression> expression;

};

#endif // RANDOMACCESS_H
