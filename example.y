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
%token	L_BRACKET
%token	R_BRACKET
%token	L_PARENTHESIS
%token	R_PARENTHESIS
%token	SEMICOLON
%token 	MINUS
%token 	PLUS
%token 	PERCENT
%token 	DIVIDE
%token 	COMMA
%token 	DOT
%token 	EQUALS
%token 	STAR
%token 	L_BRACE
%token 	R_BRACE
%token 	LESS
%token 	BANG	
%token	AND
%token	<intVal>	INTEGER_VAL
%token 	<intVal>	BOOL_VAL

%union {
	int intVal;
	char* nameId;
}

%type <nameId> id

%%
method	:	PUBLIC type id 
		|	PRIVATE

type	:	INT L_BRACE R_BRACE
		|	BOOLEAN
		|	INT
		|	id
		;

statements:	statements statement
		|	statement
		;

statement:	LEFT_BRACKET statements R_BRACKET
		|	IF L_PARENTHESIS exp R_PARENTHESIS statement ELSE statement 
		|	WHILE L_PARENTHESIS exp R_PARENTHESIS statement
		|	SYSTEMOUTPRINTLN L_PARENTHESIS exp R_PARENTHESIS SEMICOLON
		|	id EQUALS exp SEMICOLON
		|	id L_BRACE exp R_BRACE EQUALS exp SEMICOLON
		;

expressions:	expressions COMMA exp
			|	exp
			;

exp 	: 	exp AND exp
		|	exp LESS exp
		|	exp PLUS exp
		|	exp MINUS exp
		|	exp STAR exp
		|	exp PERCENT exp
		|	exp OR exp
		|	exp L_BRACE exp R_BRACE
		| 	exp DOT LENGTH
		| 	exp DOT id L_PARENTHESIS expressions R_PARENTHESIS
		| 	INTEGER
		| 	TRUE
		|	FALSE
		| 	id
		| 	THIS
		| 	NEW INT L_BRACE exp R_BRACE
		| 	NEW id L_PARENTHESIS R_PARENTHESIS
		| 	BANG exp
		| 	L_PARENTHESIS exp R_PARENTHESIS
		;

id 	:	ID 	;


%%