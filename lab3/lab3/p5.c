#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char delim[] = " ;\n\t,";
	char *keywords[] = { "int", "char", "float", "for", "if", "else", "switch", "case" };
	FILE *fp1, *fp2;
	char str[1000];
	int i = 0;
	
	fp1 = fopen("p1.c", "r");
	//fp2 = fopen("tokenize.c", "w");
	
	char ch = fgetc(fp1);
	
	while (ch != EOF)
	{
		str[i++] = ch;
		ch = fgetc(fp1);
	}
	
	str[i] = '\0';
	
	char *token;
	
	token = strtok(str, delim);
	
	printf("Keywords are: \n");
	
	while (token != NULL)
	{
		for (i = 0; i < 8; i++)
		{
			if (strcmp(keywords[i], token) == 0)
				printf("%s\n", token);
		}
		
		token = strtok(NULL, delim);
	}
	
	fclose(fp1);
	//fclose(fp2);
	
	return 0;
}
