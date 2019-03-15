#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENDMARKER '#'

int position = 0;

// String for parse
char w[100];
char l;

void error()
{
	printf("String rejected\n");
	exit(-1);
}

char nextchar()
{
	return w[position++]; 
}

void match(char t)
{
	if (l == t)
		l = nextchar();
	else
		error();
}

void Term()
{
	if (l == 'b')
	{
		match('b');
		
		if (l == 'n')
		{
			match('n');
			Term();
		}
		else
			error();
	}
	else
		return;
}

void Expr()
{
	if (l == 'n')
	{
		match('n');
		Term();
	}
	else
		error();
}

int main(void)
{	
	printf("Enter string to parse: ");
	scanf("%[^\n]", w);
	
	int len = strlen(w);
	w[len] = '#';
	
	l = nextchar();
	Expr();
	
	if (l == ENDMARKER)
		printf("String accepted\n");
	else
		error();
		
	return 0;
}
