%{
#include <stdio.h>
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
%token 	AMPERSAND


%%
RULE1: 	CLASS 				{printf("CLASS");}
	|	VAR					{printf("VAR");}
	;
/*
RULE3:	EXTENDS				{printf("EXTENDS");};
RULE4:	PUBLIC				{printf("PUBLIC");};
RULE5:	STATICVOIDMAIN		{printf("STATICVOIDMAIN");};
RULE6:	STRING				{printf("STRING");};
RULE7:	INT					{printf("INT");};
RULE8:	BOOLEAN				{printf("BOOLEAN");};
RULE9:	IF					{printf("IF");};
RULE10:	ELSE				{printf("ELSE");};
RULE11:	WHILE				{printf("WHILE");};
RULE12:	SYSTEMOUTPRINTLN	{printf("SYSTEMOUTPRINTLN");};
RULE13:	LENGTH				{printf("LENGTH");};
RULE14:	TRUE				{printf("TRUE");};
RULE15:	FALSE				{printf("FALSE");};
RULE16:	NEW					{printf("NEW");};
RULE17:	THIS				{printf("THIS");};
RULE18:	RETURN				{printf("RETURN");};
RULE19:	DIGIT				{printf("DIGIT");};
RULE20:	LETER				{printf("LETER");};
RULE21:	ID					{printf("ID");};
RULE22:	NUMBER				{printf("NUMBER");};
RULE23:	COMMENT				{printf("COMMENT");};
RULE24:	LEFT_BRACKET		{printf("LEFT_BRACKET");};
RULE25:	RIGHT_BRACKET		{printf("RIGHT_BRACKET");};
RULE26:	LEFT_PARENTHESIS	{printf("LEFT_PARENTHESIS");};
RULE27:	RIGHT_PARENTHESIS	{printf("RIGHT_PARENTHESIS");};
RULE28:	SEMICOLON			{printf("SEMICOLON");};
RULE29:	MINUS				{printf("MINUS");};
RULE30:	PLUS				{printf("PLUS");};
RULE31:	PERCENT				{printf("PERCENT");};
RULE32:	DIVIDE				{printf("DIVIDE");};
RULE33:	COMMA				{printf("COMMA");};
RULE34:	DOT					{printf("DOT");};
RULE35:	EQUALS				{printf("EQUALS");};
RULE36:	STAR				{printf("STAR");};
RULE37:	LEFT_BRACE			{printf("LEFT_BRACE");};
RULE38:	RIGHT_BRACE 		{printf("RIGHT_BRACE");};
RULE39:	LESS				{printf("LESS");};
RULE40:	BANG				{printf("BANG");};
RULE41:	AMPERSAND			{printf("AMPERSAND");};
*/

%%