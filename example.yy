%{
#include <stdio.h>
#include <string.h>

//#include "tree/Visitor.h"
#include "tree/PrettyPrinter.h"

#define RED "\x1b[31m"
#define RESET "\x1b[0m"

extern "C" int yylex();

void yyerror(char *s) {
      printf (RED "%s\n" RESET, s);
    }

CTrue *myTrue = new CTrue();
CPrettyprinter *pp = new CPrettyprinter("./graph.gv");
%}

%union {
	int intVal;
	char* nameId;
  CProgram *program;
  CMain *mainClass;
  CTrue* mytrue;
  CFalse *myfalse;
  CClass *myClass;
  CVariable *variable;
  CVariableSeq *variables;
  IExpression *expression;
  CClassSeq *classSeq;
  CStatementSeq *statementSeq;
  CStatements *statements;
  IStatement *mystatement;
  IExpressionSeq *expressions;
  CId *myId;
  CMethod *myMethod;
  CMethodSeq *methods;
  IType *myType;
  CArgs *args;
  CBasicType *basicType;
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

%token  END 0

%token	<intVal>	INTEGER
%token 	<intVal>	BOOL_VAL
%token	<nameId> ID

%type<myId> id;
%type<program> goal;
%type<mainClass> main_class;
%type<classSeq> class_s;
%type<myClass> class;
%type<statementSeq> statement_s;
%type<mystatement> statement;
%type<expression> exp;
%type<expressions> exp_s;
%type<variable> var;
%type<variables> var_s;
%type<myMethod> method;
%type<methods> method_s;
%type<myType> type;
%type<args> arg_s;

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
goal  : main_class END                                                          {$$ = new CProgram(std::shared_ptr<CMain>($1)); $$->accept(pp); printf("goal only\n");}
      | main_class class_s END                                                  {$$ = new CProgram(std::shared_ptr<CMain>($1), std::shared_ptr<CClassSeq>($2)); $$->accept(pp); printf("goal\n");}
      ;

main_class  : CLASS id L_BRACKET
              PUBLIC STATICVOIDMAIN L_ROUND STRING L_SQUARE R_SQUARE id R_ROUND
              L_BRACKET statement_s R_BRACKET
              R_BRACKET                                                         {$$ = new CMain(std::shared_ptr<CId>($2), std::shared_ptr<CId>($10), std::shared_ptr<CStatementSeq>($13)); printf("main_class\n");}
            ;

class_s : class_s class                                                         {$$ = new CClassSeq(std::shared_ptr<CClassSeq>($1), std::shared_ptr<CClass>($2)); printf("classes\n");}
        | class                                                                 {$$ = new CClassSeq(std::shared_ptr<CClass>($1)); printf("classes\n");}
        ;

class   : CLASS id L_BRACKET R_BRACKET                         {$$ = new CClass(std::shared_ptr<CId>($2), nullptr); printf("class (%s)\n", $2 );}
        | CLASS id L_BRACKET var_s R_BRACKET                   {$$ = new CClass(std::shared_ptr<CId>($2), nullptr, std::shared_ptr<CVariableSeq>($4)); printf("class (%s) vars\n", $2 );}
        | CLASS id L_BRACKET method_s R_BRACKET                {$$ = new CClass(std::shared_ptr<CId>($2), nullptr, std::shared_ptr<CMethodSeq>($4)); printf("class (%s) methods\n", $2 );}
        | CLASS id L_BRACKET var_s method_s R_BRACKET          {$$ = new CClass(std::shared_ptr<CId>($2), nullptr, std::shared_ptr<CVariableSeq>($4), std::shared_ptr<CMethodSeq>($5)); printf("class (%s) vars methods\n", $2);}
        | CLASS id EXTENDS id L_BRACKET R_BRACKET                 {$$ = new CClass(std::shared_ptr<CId>($2), std::shared_ptr<CId>($4)); printf("class ext (%s)\n", $2 );}
        | CLASS id EXTENDS id L_BRACKET var_s R_BRACKET           {$$ = new CClass(std::shared_ptr<CId>($2), std::shared_ptr<CId>($4), std::shared_ptr<CVariableSeq>($6)); printf("class ext (%s) vars\n", $2 );}
        | CLASS id EXTENDS id L_BRACKET method_s R_BRACKET        {$$ = new CClass(std::shared_ptr<CId>($2), std::shared_ptr<CId>($4), std::shared_ptr<CMethodSeq>($6)); printf("class ext (%s) methods\n", $2 );}
        | CLASS id EXTENDS id L_BRACKET var_s method_s R_BRACKET  {$$ = new CClass(std::shared_ptr<CId>($2), std::shared_ptr<CId>($4), std::shared_ptr<CVariableSeq>($6), std::shared_ptr<CMethodSeq>($7)); printf("class ext(%s) vars methods\n", $2);}
        ;

var_s    : var_s var                                           {$$ = new CVariableSeq(std::shared_ptr<CVariableSeq>($1), std::shared_ptr<CVariable>($2)); printf("vars_vars\n");}
        | var                                                  {$$ = new CVariableSeq(std::shared_ptr<CVariable>($1)); printf("vars_var\n");}
        ;

var     : type id SEMICOLON                                    {$$ = new CVariable(std::shared_ptr<IType>($1), std::shared_ptr<CId>($2)); printf("var\n");}
        ;

method_s : method_s method                                     {$$ = new CMethodSeq(std::shared_ptr<CMethodSeq>($1), std::shared_ptr<CMethod>($2)); printf("methods 1\n");}
        | method                                               {$$ = new CMethodSeq(std::shared_ptr<CMethod>($1)); printf("methods 2\n");}
        ;

method	:	modifier type id L_ROUND arg_s R_ROUND
          L_BRACKET var_s statement_s RETURN exp SEMICOLON R_BRACKET   {$$ = new CMethod(std::shared_ptr<IType>($2), std::shared_ptr<CId>($3), std::shared_ptr<CArgs>($5), std::shared_ptr<CVariableSeq>($8), std::shared_ptr<CStatementSeq>($9), std::shared_ptr<IExpression>($11)); printf("method 1 (%s)\n", $3);}
        | modifier type id L_ROUND arg_s R_ROUND
        L_BRACKET var_s RETURN exp SEMICOLON R_BRACKET                 {$$ = new CMethod(std::shared_ptr<IType>($2), std::shared_ptr<CId>($3), std::shared_ptr<CArgs>($5), std::shared_ptr<CVariableSeq>($8), nullptr, std::shared_ptr<IExpression>($10)); printf("method 2 (%s)\n", $3);}
        | modifier type id L_ROUND arg_s R_ROUND
        L_BRACKET statement_s RETURN exp SEMICOLON R_BRACKET           {$$ = new CMethod(std::shared_ptr<IType>($2), std::shared_ptr<CId>($3), std::shared_ptr<CArgs>($5), nullptr, std::shared_ptr<CStatementSeq>($8), std::shared_ptr<IExpression>($10)); printf("method 3 (%s)\n", $3);}
        | modifier type id L_ROUND arg_s R_ROUND
        L_BRACKET RETURN exp SEMICOLON R_BRACKET                       {$$ = new CMethod(std::shared_ptr<IType>($2), std::shared_ptr<CId>($3), std::shared_ptr<CArgs>($5), nullptr, nullptr, std::shared_ptr<IExpression>($9)); printf("method 4 (%s)\n", $3);}
        ;

arg_s    : %empty                      {$$ = new CArgs();}
        | arg_s COMMA type id          {$$ = new CArgs(std::shared_ptr<CArgs>($1), std::shared_ptr<IType>($3), std::shared_ptr<CId>($4)); printf("args 2\n");}
        | type id                      {$$ = new CArgs(std::shared_ptr<IType>($1), std::shared_ptr<CId>($2)); printf("args 3\n");}
        ;

modifier: PUBLIC                       {printf("public\n");}
    | PRIVATE                          {printf("private\n");}
    ;

type	:	INT L_SQUARE R_SQUARE           {$$ = new CBasicType(INT_ARRAY_); printf("int[]\n");}
		|	BOOLEAN                           {$$ = new CBasicType(BOOL_); printf("boolean\n");}
		|	INT                               {$$ = new CBasicType(INT_); printf("int\n");}
		|	id                                {$$ = new CClassType(std::shared_ptr<CId>($1)); printf("id\n");}
		;

statement_s:	statement_s statement      {$$ = new CStatementSeq(std::shared_ptr<CStatementSeq>($1), std::shared_ptr<IStatement>($2)); printf("statements 1\n");}
		|	statement                          {$$ = new CStatementSeq(std::shared_ptr<IStatement>($1)); printf("statements 2\n");}
		;

statement:	L_BRACKET statement_s R_BRACKET            {$$ = new CStatements(std::shared_ptr<CStatementSeq>($2)); printf("statement 1\n");}
		|	IF L_ROUND exp R_ROUND statement ELSE statement  {$$ = new CIf(std::shared_ptr<IExpression>($3), std::shared_ptr<IStatement>($5), std::shared_ptr<IStatement>($7)); printf("statement 2 if\n");}
		|	WHILE L_ROUND exp R_ROUND statement              {$$ = new CWhile(std::shared_ptr<IExpression>($3), std::shared_ptr<IStatement>($5)); printf("statement 3 while\n");}
		|	SYSTEMOUTPRINTLN L_ROUND exp R_ROUND SEMICOLON   {$$ = new CPrintLine(std::shared_ptr<IExpression>($3)); printf("statement 4 sys out print\n");}
		|	id EQUALS exp SEMICOLON                          {$$ = new CAssignStatement(std::shared_ptr<CId>($1), std::shared_ptr<IExpression>($3)); printf("statement 5 =\n");}
		|	id L_SQUARE exp R_SQUARE EQUALS exp SEMICOLON    {$$ = new CRandomAccessAssign(std::shared_ptr<CId>($1), std::shared_ptr<IExpression>($3), std::shared_ptr<IExpression>($6)); printf("statement 6 id[]=\n");}
		;

exp_s:	exp_s COMMA exp  {$$ = new IExpressionSeq(std::shared_ptr<IExpressionSeq>($1), std::shared_ptr<IExpression>($3)); printf("expressions 1\n");}
			|	exp              {$$ = new IExpressionSeq(std::shared_ptr<IExpression>($1)); printf("expression 2\n");}
			;

exp : exp AND exp                       {$$ = new CBinExpression(std::shared_ptr<IExpression>($1), AND_, std::shared_ptr<IExpression>($3)); printf("and\n");}
		|	exp LESS exp                      {$$ = new CBinExpression(std::shared_ptr<IExpression>($1), LESS_, std::shared_ptr<IExpression>($3)); printf("less\n");}
		|	exp PLUS exp                      {$$ = new CBinExpression(std::shared_ptr<IExpression>($1), PLUS_, std::shared_ptr<IExpression>($3)); printf("PLUS\n");}
		|	exp MINUS exp                     {$$ = new CBinExpression(std::shared_ptr<IExpression>($1), MINUS_, std::shared_ptr<IExpression>($3)); printf("MINUS\n");}
		|	exp STAR exp                      {$$ = new CBinExpression(std::shared_ptr<IExpression>($1), TIMES_, std::shared_ptr<IExpression>($3)); printf("*\n");}
		|	exp PERCENT exp                   {$$ = new CBinExpression(std::shared_ptr<IExpression>($1), MOD_, std::shared_ptr<IExpression>($3)); printf("PERCENT\n");}
		|	exp OR exp                        {$$ = new CBinExpression(std::shared_ptr<IExpression>($1), OR_, std::shared_ptr<IExpression>($3)); printf("or\n");}
		|	exp L_SQUARE exp R_SQUARE         {$$ = new CRandomAccess(std::shared_ptr<IExpression>($1), std::shared_ptr<IExpression>($3)); printf("[ ]\n");}
		| exp DOT LENGTH                    {$$ = new CLength(std::shared_ptr<IExpression>($1)); printf("LENGTH\n");}
    | exp DOT id L_ROUND R_ROUND        {$$ = new CCallMethod(std::shared_ptr<IExpression>($1), std::shared_ptr<CId>($3), nullptr); printf("%s()\n", $3);/*call method*/}
		| exp DOT id L_ROUND exp_s R_ROUND  {$$ = new CCallMethod(std::shared_ptr<IExpression>($1), std::shared_ptr<CId>($3), std::shared_ptr<IExpressionSeq>($5)); printf("%s()\n", $3);/*call method*/}
		| INTEGER                           {$$ = new CIntegerExp(yylval.intVal); printf("INTEGER\n");}
		| TRUE                              {$$ = new CTrue(); printf("true\n");}
		|	FALSE                             {$$ = new CFalse(); printf("false\n");}
		| id                                {$$ = $1; printf("id\n");}
		| THIS                              {$$ = new CThis(); printf("THIS\n");}
		| NEW INT L_SQUARE exp R_SQUARE     {$$ = new CNewIntArray(std::shared_ptr<IExpression>($4)); printf("new int [exp]\n");}
		| NEW id L_ROUND R_ROUND            {$$ = new CNewClassObject(std::shared_ptr<CId>($2)); printf("new (%s) ()\n", $2);}
		| BANG exp                          {$$ = new CNotExp(std::shared_ptr<IExpression>($2)); printf("!exp\n");}
		| L_ROUND exp R_ROUND               {$$ = $2; printf("(exp)\n");}
		;

id 	:	ID                             {$$ = new CId(std::string(yylval.nameId)); printf("ID");} ;
%%

int main (void) {
//  yydebug=0;
  yyparse();
  delete pp;
}
