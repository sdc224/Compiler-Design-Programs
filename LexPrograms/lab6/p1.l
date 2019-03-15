%{
	#include <stdio.h>
	int no_of_printf = 0, no_of_scanf = 0;
%}

%%
"printf"	{fprintf(yyout, "%s", "writef");	no_of_printf++;}
"scanf"		{fprintf(yyout, "%s", "readf");		no_of_scanf++;}
%%
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: ./a.out <Input FileName> <Output FileName>\n");
		exit(-1);
	}
	
	yyin = fopen(argv[1], "r");
	yyout = fopen(argv[2], "w");
	
	yylex();
	
	printf("No of printf: %d\n", no_of_printf);
	printf("No of scanf: %d\n", no_of_scanf);
	
	return 0;
}
