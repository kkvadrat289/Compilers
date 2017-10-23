#ifndef ID_H
#define ID_H

#include <string>
#include "Node.h"
#include "Visitor.h"

class IVisitor;

class CId: public INode{
public:
    CId(const std::string name_);
    void accept(IVisitor* v) const;
private:
    std::string name;
};

#endif // ID_H
