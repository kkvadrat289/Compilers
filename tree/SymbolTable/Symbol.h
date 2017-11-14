#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

namespace STable {

class Symbol{
public:
    Symbol(std::string name_): name(name_) {}
    bool operator ==(const Symbol& symbol){
        return &symbol == this;
    }
    bool operator !=(const Symbol& symbol){
        return &symbol != this;
    }
    std::string name;
};

}

#endif // SYMBOL_H
