#include "tree/visitors/SymbolTableVisitor.h"
#include "tokens.h"
#include "tree/SymbolTable/table.h"

extern CProgram *program;

int main(void) {
    yyparse();
    STable::CTableVisitor visitor;
    visitor.ParseProgram(program);
}
