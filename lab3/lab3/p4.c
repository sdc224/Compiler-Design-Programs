#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	FILE *fp1, *fp2;
	char ch;
	int i, n = -1;
	
	fp1 = fopen("p1.c", "r");
	fp2 = fopen("removal_whitespace.c", "w");
	
	if (fp1 == NULL)
	{
		printf("File does not exist");
		exit(-1);
	}
	
	int line = 1;
	char *str;
	
	ch = fgetc(fp1);
		
	while(ch != EOF)
	{			
		if (ch != ' ' && ch != '\n' && ch != '\t')
			putc(ch, fp2);
			
		ch = fgetc(fp1);
	}
	
	fclose(fp1);	
	fclose(fp2);	
	
	fp1 = fopen("removal_whitespace.c", "r");
	
	ch = fgetc(fp1);
	
	while (ch != EOF)
	{
		printf("%c", ch);
		
		ch = fgetc(fp1);
	}
	
	fclose(fp1);
	
	return 0;
}
