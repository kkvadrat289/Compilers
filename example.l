%{
#include <stdio.h>
#define YY_USER_ACTION printLocation();
static int line_number = 1;
static int column_number = 1;
void printLocation();
%}

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
[0-9] printf("DIGIT");
[a-zA-Z_] printf("LETER");
{LETER}({DIGIT}|{LETER})* printf("ID");
[1-9]{DIGIT}* printf("INT");
"//".* printf("COMMENT");
%%

void printLocation(){
	
}
