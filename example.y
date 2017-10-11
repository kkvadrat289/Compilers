%{
#include <stdio.h>
extern int yylex();
void yyerror(char *s) {
      fprintf (stderr, "%s\n", s);
    }

%}

%token	CLASS
%token  VAR
%token	EXTENDS
%token	PUBLIC
%token	STATICVOIDMAIN
%token	STRING
%token	INT
%token	BOOLEAN
%token	IF
%token	ELSE
%token 	WHILE
%token	SYSTEMOUTPRINTLN
%token	LENGTH
%token	TRUE
%token	FALSE
%token	NEW
%token	THIS
%token	RETURN
%token	DIGIT
%token	LETER
%token	ID
%token	NUMBER
%token	COMMENT
%token	LEFT_BRACKET
%token	RIGHT_BRACKET
%token	LEFT_PARENTHESIS
%token	RIGHT_PARENTHESIS
%token	SEMICOLON
%token 	MINUS
%token 	PLUS
%token 	PERCENT
%token 	DIVIDE
%token 	COMMA
%token 	DOT
%token 	EQUALS
%token 	STAR
%token 	LEFT_BRACE
%token 	RIGHT_BRACE
%token 	LESS
%token 	BANG	
%token	AND
%token	

%union {
	int intVal;
	char* nameId;
}

%type <nameId> id

%%

exp 	: 	exp AND exp
		|	exp LESS exp
		|	exp PLUS exp
		|	exp MINUS exp
		|	exp STAR exp
		|	exp PERCENT exp
		|	exp OR exp
		|	exp LEFT_BRACE exp RIGHT_BRACE
		| 	exp DOT LENGTH
		| 	exp DOT ID LEFT_PARENTHESIS ( exp ( COMMA exp )* )? RIGHT_PARENTHESIS
		| NUMBER
		| TRUE
		| FALSE
		| id
		| THIS
		| NEW INT LEFT_BRACE exp RIGHT_BRACE
		| NEW id LEFT_PARENTHESIS RIGHT_PARENTHESIS
		| BANG exp
		| LEFT_PARENTHESIS exp RIGHT_PARENTHESIS
		;

id 	:	ID 	;


%%