all: parser

parser: parser.o lex.o solution.o visitor.o
	g++ -g -Wno-write-strings -o parser solution.o visitor.o lex.o parser.o -lfl

parser.o:  example.yy
	bison -dt --verbose example.yy && mv example.tab.hh tokens.h && mv example.tab.cc parser.cpp && g++ -g -c --std=c++14 parser.cpp -Wno-write-strings -o parser.o

lex.o: example.lex
	flex++ example.lex && g++ -g -c lex.yy.cc -Wno-write-strings -o lex.o

solution.o: tree/AllProblemsSolution.cpp
	g++ -g -c tree/AllProblemsSolution.cpp -o solution.o

visitor.o: tree/PrettyPrinter.cpp
	g++ -g -c tree/PrettyPrinter.cpp -o visitor.o

clean:
	rm solution.o lex.o visitor.o parser.o parser parser.cpp tokens.h
