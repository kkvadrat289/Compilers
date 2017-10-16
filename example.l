%{
#include <stdio.h>
#include "example.tab.h"

#define YY_USER_ACTION updateLocation();

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
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
"class" 					return CLASS;
"var" 						return VAR;
"extends" 					return EXTENDS;
"public" 					return PUBLIC;
"static void main" 			return STATICVOIDMAIN;
"String" 					return STRING;
"int" 						return INT;
"boolean" 					return BOOLEAN;
"if" 						return IF;
"else" 						return ELSE;
"while" 					return WHILE;
"System.out.println" 		return SYSTEMOUTPRINTLN;
"length" 					return LENGTH;
"true" 						return TRUE;
"false" 					return FALSE;
"new" 						return NEW;
"this" 						return THIS;
"return" 					return RETURN;

[a-zA-Z_] 					return LETER;
{LETER}({DIGIT}|{LETER})* 	return ID;
[1-9]{DIGIT}* 				return NUMBER;
"//".* 						return COMMENT;
[ \t\n]+ 					;

"{" 						return L_BRACKET;
"}" 						return R_BRACKET;
"(" 						return L_ROUND;
")" 						return R_ROUND;
"\[" 						return L_SQUARE;
"\]" 						return R_SQUARE

";" 						return SEMICOLON;

"-" 						return MINUS;
"+" 						return PLUS;
"%" 						return PERCENT;
"/" 						return DIVIDE;
"=" 						return EQUALS;

"," 						return COMMA;
"." 						return DOT;
"*" 						return STAR;
"<" 						return LESS;
"!" 						return BANG;

"&&" 						return AND;
"||"						return OR;

. 							printf(ANSI_COLOR_BLUE "EROR(%s)" ANSI_COLOR_RESET, yytext);


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
	//printf(ANSI_COLOR_GREEN "[%d,%d]" ANSI_COLOR_RESET, line_number, column_number);
}
