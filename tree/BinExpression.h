#ifndef BINEXPRESSION_H
#define BINEXPRESSION_H

#include "Expression.h"

enum BinType { AND_,
               OR_,
               LESS_,
               PLUS_,
               MINUS_,
               TIMES_,
               MOD_
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
            case OR_:
                label = "or";
            case PLUS_:
                label = "+";
            case MINUS_:
                label = "-";
            case TIMES_:
                label = "*";
            case LESS_:
                label = std::string("less");
            case MOD_:
                label = "%";
        }
    }

    void accept(IVisitor *v) const  override;
    BinType type;
    std::shared_ptr<IExpression> left;
    std::shared_ptr<IExpression> right;
};

#endif // BINEXPRESSION_H
