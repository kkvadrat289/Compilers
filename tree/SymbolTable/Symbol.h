#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include "InternSymbol.h"

namespace STable {

class CSymbol {
public:
    CSymbol(std::string name_): name(CInternSymbol::GetIntern(name_)){}
    CSymbol(CInternSymbol* name_): name(name_){}

  CInternSymbol* GetName() const {
      return name;
  }

  CSymbol( const CSymbol& ) = delete;
  void operator=( const CSymbol& ) = delete;

  bool operator ==( const CSymbol& symbol ){
      return &symbol == this;
  }
  bool operator !=( const CSymbol& symbol ){
      return &symbol != this;
  }

  virtual ~CSymbol() {}

protected:

  CInternSymbol* name;

};

}

#endif // SYMBOL_H
