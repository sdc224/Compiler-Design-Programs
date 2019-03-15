%{
	#include <stdio.h>
	int flag = 1;
	char stack_of_brackets[10];
	int top = -1;
%}
letter [a-zA-Z]
digit [0-9]
operators [+-*/%=]
increment "++"
decrement "--"
%%
"["	{stack_of_brackets[++top] = '[';}
"{"	{stack_of_brackets[++top] = '{';}
"("	{stack_of_brackets[++top] = '(';}
"]"	{
		if (stack_of_brackets[top] == ']')
			top--;
		else
			flag = 0;
	}

"}"	{
		if (stack_of_brackets[top] == '}')
			top--;
		else
			flag = 0;
	}
															
")"	{
		if (stack_of_brackets[top] == ')')
			top--;
		else
			flag = 0;
	}
.	{}
%%
int main(void)
{
	yyin = fopen("program_with_brackets.c", "r");
	yylex();
	
	if (flag)
		printf("Brackets are correct\n");
	else
		printf("Brackets are not matched\n");
		
	return 0;
}
