#include "tree/visitors/SymbolTableVisitor.h"
#include "tokens.h"
#include "tree/SymbolTable/table.h"

extern CProgram *program;

int main(void) {
    try{
        yyparse();
        STable::CTableVisitor visitor;
        visitor.ParseProgram(program);
    }
    catch (DeclarationException e){
        std::cout << e.what() << std::endl;
    }
}
