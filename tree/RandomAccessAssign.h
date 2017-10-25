#ifndef RANDOMACCESSASSIGN_H
#define RANDOMACCESSASSIGN_H

#include "Statement.h"

class CRandomAccessAssign: public IStatement{
public:
    CRandomAccessAssign(std::shared_ptr<CId> id_, std::shared_ptr<IExpression> position_, std::shared_ptr<IExpression> expression_):
        id(id_),
        position(position_),
        expression(expression_)
    {}
    void accept(IVisitor *v) const override;

    std::shared_ptr<CId> id;
    std::shared_ptr<IExpression> position;
    std::shared_ptr<IExpression> expression;

};

#endif // RANDOMACCESS_H
