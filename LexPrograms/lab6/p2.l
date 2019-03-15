%{
	#include <stdio.h>
	#include <string.h>
	int no_of_printf = 0, no_of_scanf = 0;
	char *find, *replace;
%}

%%
[a-zA-Z]+	{if (strcmp(yytext, find) == 0)	{fprintf(yyout, "%s", replace);	no_of_printf++;} else fprintf(yyout, "%s", yytext);}
%%
int main(int argc, char **argv)
{
	if (argc != 5)
	{
		printf("Usage: ./a.out <Input FileName> <Output FileName> <Input Pattern> <Output Pattern>\n");
		exit(-1);
	}
	
	yyin = fopen(argv[1], "r");
	yyout = fopen(argv[2], "w");
	
	find = argv[3];
	replace = argv[4];
	
	yylex();
	
	printf("No of printf: %d\n", no_of_printf);
	printf("No of scanf: %d\n", no_of_scanf);
	
	return 0;
}
