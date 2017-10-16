%{
#include <stdio.h>
extern int yylex();
void yyerror(char *s) {
      fprintf (stderr, "%s\n", s);
    }

%}

%union {
	int intVal;
	char* nameId;
}

%locations

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
%token	L_ROUND
%token  R_ROUND
%token	SEMICOLON
%token 	MINUS
%token 	PLUS
%token 	PERCENT
%token 	DIVIDE
%token 	COMMA
%token 	DOT
%token 	EQUALS
%token 	STAR
%token 	L_SQUARE
%token 	R_SQUARE
%token 	LESS
%token 	BANG
%token	AND
%token END 0
%token	<intVal>	INTEGER_VAL
%token 	<intVal>	BOOL_VAL

%type <nameId> id

%%
goal  : main_class END
      | main_class class_s END
      ;

main_class  : CLASS id L_BRACKET
              PUBLIC STATICVOIDMAIN L_ROUND STRING L_SQUARE R_SQUARE id R_ROUND
              L_BRACKET statement_s R_BRACKET
              R_BRACKET
            ;

class_s : class_s class_s
        | class
        ;

class   : CLASS id L_BRACKET R_BRACKET
        | CLASS id L_BRACKET var_s R_BRACKET
        | CLASS id L_BRACKET method_s R_BRACKET
        | CLASS id L_BRACKET var_s method_s R_BRACKET
        | CLASS id EXTENDS L_BRACKET R_BRACKET
        | CLASS id EXTENDS L_BRACKET var_s R_BRACKET
        | CLASS id EXTENDS L_BRACKET method_s R_BRACKET
        | CLASS id EXTENDS L_BRACKET vars method_s R_BRACKET
        ;

var_s    : var_s var
        | var
        ;

var     : type id SEMICOLON
        ;

method_s : method_s method
        | method
        ;

method	:	modifier type id L_ROUND args R_ROUND
          L_BRACKET var_s statements RETURN exp SEMICOLON R_BRACKET
        | modifier type id L_ROUND args R_ROUND
        L_BRACKET var_s RETURN exp SEMICOLON R_BRACKET
        | modifier type id L_ROUND args R_ROUND
        L_BRACKET statement_s RETURN exp SEMICOLON R_BRACKET
        | modifier type id L_ROUND args R_ROUND
        L_BRACKET RETURN exp SEMICOLON R_BRACKET
        ;

arg_s    : %empty
        | args COMMA type id
        | type id
        ;

modifier: PUBLIC
    | PRIVATE
    ;

type	:	INT L_SQUARE R_SQUARE
		|	BOOLEAN
		|	INT
		|	id
		;

statement_s:	statement_s statement
		|	statement
		;

statement:	L_BRACKET statement_s R_BRACKET
		|	IF L_ROUND exp R_ROUND statement ELSE statement
		|	WHILE L_ROUND exp R_ROUND statement
		|	SYSTEMOUTPRINTLN L_ROUND exp R_ROUND SEMICOLON
		|	id EQUALS exp SEMICOLON
		|	id L_BRACE exp R_BRACE EQUALS exp SEMICOLON
		;

exp_s:	exp_s COMMA exp
			|	exp
			;

exp 	: 	exp AND exp
		|	exp LESS exp
		|	exp PLUS exp
		|	exp MINUS exp
		|	exp STAR exp
		|	exp PERCENT exp
		|	exp OR exp
		|	exp L_SQUARE exp R_SQUARE
		| exp DOT LENGTH
		| exp DOT id L_ROUND expression_s R_ROUND
		| INTEGER
		| TRUE
		|	FALSE
		| id
		| THIS
		| NEW INT L_SQUARE exp R_SQUARE
		| NEW id L_ROUND R_ROUND
		| BANG exp
		| L_ROUND exp R_ROUND
		;

id 	:	ID 	;
%%
