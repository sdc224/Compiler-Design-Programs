%{
	#include <stdio.h>
	int single_line_comments = 0;
	int multi_line_comments = 0;
	int total_comments = 0;
%}
let [a-zA-Z]
dig [0-9]
spc " "
tab \t
nl	\n
%%
"/*".+"*/"	{single_line_comments++; printf(" ");}

"/*"({let}|{dig}|{spc}|{tab}|{nl}|\;|\{|\}|\"|\"|\(|\))*"*/"	{multi_line_comments++; printf(" ");}

"//".+\n	{single_line_comments++; printf(" ");}
%%
int main(void)
{
	yyin = fopen("program_with_comments.c", "r");
	printf("Program without comments...\n");
	yylex();
	printf("Comment Lines... Single: %d\n", single_line_comments);
	printf("Comment Lines... Multi Line Comments: %d\n", multi_line_comments);
	return 0;
}
