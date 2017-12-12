
#include "tree/visitors/PrettyPrinter.h"
#include "tokens.h"

extern CProgram *program;

int main(void) {
    yyparse();
    CPrettyprinter *printer = new CPrettyprinter("./graph.gv");
    program->accept(printer);
    delete printer;
}
