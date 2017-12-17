#include "tokens.h"
#include "Exceptions.h"
#include "../SymbolTable/table.h"
#include "../visitors/TypeCheckVisitor.h"
#include "../visitors/SymbolTableVisitor.h"


#include <iostream>
#include <unistd.h>

extern std::unique_ptr<CProgram> program;

int main(void) {
   yyparse();
   STable::CTableVisitor visitor;
   try {
      visitor.FillTable(program.get());
      std::unique_ptr<STable::CTable> symbolTable(visitor.GetTable());
      TypeChecker::CTypeChecker checker;
      checker.Check(program.get(), symbolTable.get());
   }
   catch(DeclarationException e) {}

  return 0;
}
