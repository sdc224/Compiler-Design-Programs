#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void E();
void E_();
void T();
void T_();
void F();

void F()
{
	if (l == '(')
	{
		match('(');
		E();
		if (l == ')')
			match(')');
		else
			error();
	}
	else
	{
		if (l == 'a')
			match('a');
		else
			error();
	}
}

void T_()
{
	if (l == '*')
	{
		match('*');
		F();
		T_();
	}
	else
		return;
}

void T()
{
	F();
	T_();
}

void E_()
{
	if (l == '+')
	{
		match('+');
		T();
		E_();
	}
	else
		return;
}

void E()
{
	T();
	E_();
}

int main(void)
{	
	printf("Enter string to parse: ");
	scanf("%[^\n]", w);
	
	int len = strlen(w);
	w[len] = '#';
	
	l = nextchar();
	E();
	
	if (l == ENDMARKER)
		printf("String accepted\n");
	else
		error();
		
	return 0;
}
