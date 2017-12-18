#include "tree/Exceptions.h"
#include "tree/SymbolTable/table.h"
#include "tree/visitors/TypeCheckVisitor.h"
#include "tree/visitors/SymbolTableVisitor.h"
#include "tokens.h"

#include <iostream>
#include <unistd.h>

extern std::unique_ptr<CProgram> program;

int main(void) {
   yyparse();
   STable::CTableVisitor visitor;
   visitor.ParseProgram(program.get());
   /*try {
      visitor.FillTable(program.get());
      std::unique_ptr<STable::CTable> symbolTable(visitor.GetTable());
      TypeChecker::CTypeChecker checker;
      checker.Check(program.get(), symbolTable.get());
   }
   catch(DeclarationException e) {}
*/
  return 0;
}
