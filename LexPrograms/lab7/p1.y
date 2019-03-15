%{
	#include <stdio.h>
	#include "lex.yy.c"
%}
%token A B NL

%%
S: E NL	{printf("Valid String\n");	exit(0);}
E: A E B
 |
 ;
%%

int yyerror(char *s)
{
	printf("Invalid string\n");
	exit(0);
}

int main(void)
{
	printf("Enter the expression\n");
	yyparse();
	return 0;
}
