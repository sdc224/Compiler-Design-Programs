#include<stdio.h>
#include<string.h>

int main()
{
	char delim[]=" ;,\n\t";
	char str[]="int a;int b,c;";
	
	char *token;
	token=strtok(str,delim);
	
	while(token!=NULL)
	{
		printf("%s\n",token);
		token=strtok(NULL,delim);
	}
	int i=0;
	while(i<12)
	{
		printf("%c",str[i]);
		i++;
	}
	return 0;
}
