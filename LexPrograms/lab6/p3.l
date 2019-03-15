%{
	#include <stdio.h>
	#include <string.h>
	int max_length = 0;
	char max_lengthed_string[100];
%}

letter	[a-zA-Z]
digit	[0-9]
special	[~!@#$%^&*_]
%%
({letter}|{digit}|{special})*	{if (max_length < yyleng){	max_length = yyleng;	strcpy(max_lengthed_string, yytext);}}
%%
int main(void)
{
	yyin = fopen("abc.txt", "r");
	yylex();
	printf("String which is of max length is %s\n", max_lengthed_string);
	printf("Max length is: %d\n", max_length);
	return 0;
}
