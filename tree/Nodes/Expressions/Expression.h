#ifndef IEXPRESSION_H
#define IEXPRESSION_H

#include "../Node.h"

class IExpression: public INode{
public:
    std::string label;
};

#endif // IEXPRESSION_H
