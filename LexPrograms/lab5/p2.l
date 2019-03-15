%{
	#include <stdio.h>
	int no_of_identifiers = 0;
	int no_of_constants = 0;
%}

let_with_undrscr [a-zA-Z_]
dig [0-9]
%%
{let_with_undrscr}({let_with_undrscr}|{dig})*	{no_of_identifiers++;	ECHO;	printf("\n");}
\-?{dig}+(\.{dig}+(\E[+-])?{dig}+)?	{no_of_constants++;	ECHO;	printf("\n");}
%%
int main(void)
{
	yyin = fopen("program_with_identifiers.c", "r");
	printf("Identifiers and constants are...\n");
	yylex();
	printf("No of identifiers = %d\n", no_of_identifiers);
	printf("No of constants = %d\n", no_of_constants);
	return 0;
}
