#ifndef ID_H
#define ID_H

#include <string>
#include <iostream>
#include "Node.h"

class CId: public IExpression{
public:
    CId(std::string name_){
        if (name_!=""){
            name = name_;
        }
        std::cout << name_ << std::endl;
    }
    void accept(IVisitor* v) const override;

    std::string name;
};

#endif // ID_H
