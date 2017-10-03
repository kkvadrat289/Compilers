%{
#include <stdio.h>
#define YY_USER_ACTION updateLocation();
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
static int line_number = 1;
static int column_number = 1;
struct yylloc{
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} yylloc;
void updateLocation();
%}

%option noyywrap

DIGIT [0-9]
LETER [a-zA-Z_]
id {LETER}({DIGIT}|{LETER})*
IntegerLiteral [1-9]{DIGIT}*|0

%%
"class" printf("CLASS");
"var" printf("VAR");
"extends" printf("EXTENDS");
"public" printf("PUBLIC");
"static void main" printf("STATICVOIDMAIN");
"String" printf("STRING");
"int" printf("INT");
"boolean" printf("BOOLEAN");
"if" printf("IF");
"else" printf("ELSE");
"while" printf("WHILE");
"System.out.println" printf("SYSTEMOUTPRINTLN");
"length" printf("LENGTH");
"true" printf("TRUE");
"false" printf("FALSE");
"new" printf("NEW");
"this" printf("THIS");
"return" printf("RETURN");
{DIGIT} printf("DIGIT");
[a-zA-Z_] printf("LETER");
{LETER}({DIGIT}|{LETER})* printf("ID(%s)", yytext);
[1-9]{DIGIT}* printf("INT");
"//".* printf("COMMENT");
[ \t]+ printf("");
\n printf("");
"{" printf("LEFT BRACKET");
"}" printf("RIGHT BRACKET");
"(" printf("LEFT PARENTHESIS");
")" printf("RIGHT PARENTHESIS");
";" printf("SEMICOLON");
"-" printf("MINUS");
"+" printf("PLUS");
"%" printf("PERCENT");
"/" printf("DIVIDE");
"," printf("COMMA");
"." printf("DOT"); 
"=" printf("EQUALS");
"*" printf("STAR");
"\[" printf("LEFT BRACE");
"\]" printf("RIGHT BRACE");
"<" printf("LESS");
"!" printf("BANG");
"&" printf("AMPERSAND");
. printf(ANSI_COLOR_BLUE "ERRROOOOOOOOORRRR(%s)" ANSI_COLOR_RESET, yytext);
%%

void updateLocation(){
	printf(" ");
	yylloc.first_line = line_number;
	yylloc.first_column = column_number;

	for( int i = 0; i < yyleng; i++ ) {
		if( yytext[i] == '\n' ) {
			line_number++;
			column_number = 1;
		} else {
			column_number++;
		}
	}

	yylloc.last_line = line_number;
	yylloc.last_column = column_number;

	
	printf("[%d %d]", line_number, column_number);
}
