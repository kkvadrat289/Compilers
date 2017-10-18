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
%token  PRIVATE
%token	STATICVOIDMAIN
%token	STRING
%token	INT
%token  INTEGER
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
%token	<nameId> ID

%token	COMMENT

%token	L_BRACKET
%token	R_BRACKET
%token	L_ROUND
%token  R_ROUND
%token 	L_SQUARE
%token 	R_SQUARE

%token	SEMICOLON

%token 	MINUS
%token 	PLUS
%token 	PERCENT
%token 	DIVIDE
%token 	EQUALS

%token 	COMMA
%token 	DOT
%token 	STAR
%token 	LESS
%token 	BANG
%token	AND
%token  OR
%token	<intVal>	INTEGER_VAL
%token 	<intVal>	BOOL_VAL
%token  END 0

%type <nameId> id

%left OR
%left AND
%left MINUS
%left PLUS
%left PERCENT
%left STAR
%left LESS
%left DOT
%left L_SQUARE
%right BANG

%%
goal  : main_class END  {printf("goal");}
      | main_class class_s END  {printf("goal");}
      ;

main_class  : CLASS id L_BRACKET
              PUBLIC STATICVOIDMAIN L_ROUND STRING L_SQUARE R_SQUARE id R_ROUND
              L_BRACKET statement_s R_BRACKET
              R_BRACKET {printf("main_class");}
            ;

class_s : class_s class
        | class {printf("class");}
        ;

class   : CLASS id L_BRACKET R_BRACKET
        | CLASS id L_BRACKET var_s R_BRACKET
        | CLASS id L_BRACKET method_s R_BRACKET
        | CLASS id L_BRACKET var_s method_s R_BRACKET
        | CLASS id EXTENDS L_BRACKET R_BRACKET
        | CLASS id EXTENDS L_BRACKET var_s R_BRACKET
        | CLASS id EXTENDS L_BRACKET method_s R_BRACKET
        | CLASS id EXTENDS L_BRACKET var_s method_s R_BRACKET
        ;

var_s    : var_s var
        | var {printf("var");}
        ;

var     : type id SEMICOLON
        ;

method_s : method_s method
        | method  {printf("method");}
        ;

method	:	modifier type id L_ROUND arg_s R_ROUND
          L_BRACKET var_s statement_s RETURN exp SEMICOLON R_BRACKET
        | modifier type id L_ROUND arg_s R_ROUND
        L_BRACKET var_s RETURN exp SEMICOLON R_BRACKET
        | modifier type id L_ROUND arg_s R_ROUND
        L_BRACKET statement_s RETURN exp SEMICOLON R_BRACKET
        | modifier type id L_ROUND arg_s R_ROUND
        L_BRACKET RETURN exp SEMICOLON R_BRACKET
        ;

arg_s    : %empty
        | arg_s COMMA type id  {printf("args");}
        | type id {printf("arg");}
        ;

modifier: PUBLIC  {printf("public");}
    | PRIVATE {printf("private");}
    ;

type	:	INT L_SQUARE R_SQUARE  {printf("int[]");}
		|	BOOLEAN {printf("boolean");}
		|	INT {printf("int");}
		|	id  {printf("id");}
		;

statement_s:	statement_s statement  {printf("statements");}
		|	statement {printf("statement");}
		;

statement:	L_BRACKET statement_s R_BRACKET
		|	IF L_ROUND exp R_ROUND statement ELSE statement
		|	WHILE L_ROUND exp R_ROUND statement
		|	SYSTEMOUTPRINTLN L_ROUND exp R_ROUND SEMICOLON
		|	id EQUALS exp SEMICOLON
		|	id L_SQUARE exp R_SQUARE EQUALS exp SEMICOLON
		;

exp_s:	exp_s COMMA exp  {printf("expressions");}
			|	exp  {printf("expression");}
			;

exp : exp AND exp
		|	exp LESS exp
		|	exp PLUS exp
		|	exp MINUS exp
		|	exp STAR exp
		|	exp PERCENT exp
		|	exp OR exp
		|	exp L_SQUARE exp R_SQUARE
		| exp DOT LENGTH
    | exp DOT id L_ROUND R_ROUND
		| exp DOT id L_ROUND exp_s R_ROUND
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

id 	:	ID 	{printf("ID");} ;
%%
