#ifndef BINEXPRESSION_H
#define BINEXPRESSION_H

#include "Expression.h"

enum BinType {
    LESS_  = 1,
    AND_ = 2,
    OR_ = 3,
    PLUS_ = 4,
    MINUS_ = 5,
    TIMES_ = 6,
    MOD_ = 7
};

class CBinExpression: public IExpression{
public:
    CBinExpression(std::shared_ptr<IExpression> left_, BinType type_, std::shared_ptr<IExpression> right_):
        type(type_),
        left(left_),
        right(right_)
    {
        switch(type){
            case AND_:
                label = "and";
            break;
            case OR_:
                label = "or";
            break;
            case PLUS_:
                label = "+";
            break;
            case MINUS_:
                label = "-";
            break;
            case TIMES_:
                label = "*";
            break;
            case LESS_:
                label = "<";
            break;
            case MOD_:
                label = "%";
            break;
        }
    }

    void accept(IVisitor *v) const  override;
    std::string label;
    BinType type;
    std::shared_ptr<IExpression> left;
    std::shared_ptr<IExpression> right;
};

#endif // BINEXPRESSION_H
