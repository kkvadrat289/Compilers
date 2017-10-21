%{
#include <stdio.h>
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

extern int yylex();
void yyerror(char *s) {
      printf (RED "%s\n" RESET, s);
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
goal  : main_class END           {printf("goal only\n");}
      | main_class class_s END   {printf("goal\n");}
      ;

main_class  : CLASS id L_BRACKET
              PUBLIC STATICVOIDMAIN L_ROUND STRING L_SQUARE R_SQUARE id R_ROUND
              L_BRACKET statement_s R_BRACKET
              R_BRACKET   {printf("main_class\n");}
            ;

class_s : class_s class   {printf("classes\n");}
        | class           {printf("classes\n");}
        ;

class   : CLASS id L_BRACKET R_BRACKET                         {printf("class (%s)\n", $2 );}
        | CLASS id L_BRACKET var_s R_BRACKET                   {printf("class (%s) vars\n", $2 );}
        | CLASS id L_BRACKET method_s R_BRACKET                {printf("class (%s) methods\n", $2 );}
        | CLASS id L_BRACKET var_s method_s R_BRACKET          {printf("class (%s) vars methods\n", $2);}
        | CLASS id EXTENDS L_BRACKET R_BRACKET                 {printf("class ext (%s)\n", $2 );}
        | CLASS id EXTENDS L_BRACKET var_s R_BRACKET           {printf("class ext (%s) vars\n", $2 );}
        | CLASS id EXTENDS L_BRACKET method_s R_BRACKET        {printf("class ext (%s) methods\n", $2 );}
        | CLASS id EXTENDS L_BRACKET var_s method_s R_BRACKET  {printf("class ext(%s) vars methods\n", $2);}
        ;

var_s    : var_s var  {printf("vars_vars\n");}
        | var         {printf("vars_var\n");}
        ;

var     : type id SEMICOLON  {printf("var\n");}
        ;

method_s : method_s method   {printf("methods 1\n");}
        | method             {printf("methods 2\n");}
        ;

method	:	modifier type id L_ROUND arg_s R_ROUND
          L_BRACKET var_s statement_s RETURN exp SEMICOLON R_BRACKET   {printf("method 1 (%s)\n", $3);}
        | modifier type id L_ROUND arg_s R_ROUND
        L_BRACKET var_s RETURN exp SEMICOLON R_BRACKET                 {printf("method 2 (%s)\n", $3);}
        | modifier type id L_ROUND arg_s R_ROUND
        L_BRACKET statement_s RETURN exp SEMICOLON R_BRACKET           {printf("method 3 (%s)\n", $3);}
        | modifier type id L_ROUND arg_s R_ROUND
        L_BRACKET RETURN exp SEMICOLON R_BRACKET                       {printf("method 4 (%s)\n", $3);}
        ;

arg_s    : %empty              {printf("args empty\n" );}
        | arg_s COMMA type id  {printf("args 2\n");}
        | type id              {printf("args 3\n");}
        ;

modifier: PUBLIC {printf("public\n");}
    | PRIVATE    {printf("private\n");}
    ;

type	:	INT L_SQUARE R_SQUARE  {printf("int[]\n");}
		|	BOOLEAN                  {printf("boolean\n");}
		|	INT                      {printf("int\n");}
		|	id                       {printf("id\n");}
		;

statement_s:	statement_s statement  {printf("statements 1\n");}
		|	statement                      {printf("statements 2\n");}
		;

statement:	L_BRACKET statement_s R_BRACKET            {printf("statement 1\n");}
		|	IF L_ROUND exp R_ROUND statement ELSE statement  {printf("statement 2 if\n");}
		|	WHILE L_ROUND exp R_ROUND statement              {printf("statement 3 while\n");}
		|	SYSTEMOUTPRINTLN L_ROUND exp R_ROUND SEMICOLON   {printf("statement 4 sys out print\n");}
		|	id EQUALS exp SEMICOLON                          {printf("statement 5 =\n");}
		|	id L_SQUARE exp R_SQUARE EQUALS exp SEMICOLON    {printf("statement 6 id[]=\n");}
		;

exp_s:	exp_s COMMA exp  {printf("expressions 1\n");}
			|	exp              {printf("expression 2\n");}
			;

exp : exp AND exp                       {printf("and\n");}
		|	exp LESS exp                      {printf("less\n");}
		|	exp PLUS exp                      {printf("PLUS\n");}
		|	exp MINUS exp                     {printf("MINUS\n");}
		|	exp STAR exp                      {printf("*\n");}
		|	exp PERCENT exp                   {printf("PERCENT\n");}
		|	exp OR exp                        {printf("or\n");}
		|	exp L_SQUARE exp R_SQUARE         {printf("[ ]\n");}
		| exp DOT LENGTH                    {printf("LENGTH\n");}
    | exp DOT id L_ROUND R_ROUND        {printf("%s()\n", $3);/*call method*/}
		| exp DOT id L_ROUND exp_s R_ROUND  {printf("%s()\n", $3);/*call method*/}
		| INTEGER                           {printf("INTEGER\n");}
		| TRUE                              {printf("true\n");}
		|	FALSE                             {printf("false\n");}
		| id                                {printf("id\n");}
		| THIS                              {printf("THIS\n");}
		| NEW INT L_SQUARE exp R_SQUARE     {printf("new int [exp]\n");}
		| NEW id L_ROUND R_ROUND            {printf("new (%s) ()\n", $2);}
		| BANG exp                          {printf("!exp\n");}
		| L_ROUND exp R_ROUND               {printf("(exp)\n");}
		;

id 	:	ID                             {printf("ID");} ;
%%

int main () { yydebug=0; return yyparse(); }
