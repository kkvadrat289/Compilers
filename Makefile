NODES_DIR = Nodes
TABLE_OBJ = table1.o table2.o table_visitor.o
PARSER_OBJ = parser.o lex.o solution.o

all: graph table checker

parser: parser.o lex.o solution.o visitor.o table.o
	g++ -g -Wno-write-strings -o solution.o visitor.o  $(PARSER_OBJ) -lfl

parser.o:  example.yy
	bison -dt --verbose example.yy && mv example.tab.hh tokens.h && mv example.tab.cc parser.cpp && g++ -g -c --std=c++14 parser.cpp -Wno-write-strings -o parser.o

lex.o: example.lex
	flex++ example.lex && g++ -g -c lex.yy.cc -Wno-write-strings -o lex.o

solution.o: tree/AllProblemsSolution.cpp
	g++ -g -c tree/AllProblemsSolution.cpp -o solution.o

visitor.o: tree/visitors/PrettyPrinter.cpp
	g++ -g -c tree/visitors/PrettyPrinter.cpp -o visitor.o -std=c++14

graph:	$(PARSER_OBJ) visitor.o graph.o
	g++ -g $(PARSER_OBJ) visitor.o graph.o -o graph -lfl

graph.o:	AST.cpp
	g++ -g -c AST.cpp -o graph.o -std=c++14

table:  $(PARSER_OBJ)  visitor.o table.o table1.o table2.o
	g++ -g $(PARSER_OBJ) visitor.o table.o table1.o table2.o -lfl -std=c++14 -Wno-write-strings -o table

table.o:	table1.o
	g++ -g -c table.cpp -o table.o -std=c++14

table1.o:	tree/SymbolTable/table.cpp
	g++ -g -c tree/SymbolTable/table.cpp -o table1.o

table2.o:	tree/visitors/SymbolTableVisitor.cpp
	g++ -g -c tree/visitors/SymbolTableVisitor.cpp -o table2.o

checker:  $(PARSER_OBJ)  visitor.o checker.o table1.o table2.o checker2.o
		g++ -g $(PARSER_OBJ) visitor.o checker.o table1.o table2.o checker2.o -lfl -std=c++14 -Wno-write-strings -o checker

checker.o:	table1.o
	g++ -g -c checker.cpp -o checker.o -std=c++14

checker2.o:	tree/visitors/TypeCheckVisitor.cpp
	g++ -g -c tree/visitors/TypeCheckVisitor.cpp -o checker2.o

clean:
	rm solution.o $(PARSER_OBJ) $(TABLE_OBJ) visitor.o parser.cpp tokens.h visitor.o graph.o table
