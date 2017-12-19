#ifndef FILLE_H
#define FILLE_H


#include "../SymbolTable/table.h"

namespace Records {

class FrameFiller {
public:
    FrameFiller(STable::CTable* table) : table(table), filled(false) {}
    void Fill();
private:
    STable::CTable* table;
    bool filled;
};

}

#endif // FILLE_H
