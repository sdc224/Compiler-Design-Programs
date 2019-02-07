#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	FILE *fp1, *fp2;
	char ch;
	int i, n;
	
	fp1 = fopen("p1.c", "r");
	fp2 = fopen("removed_preprocessor.c", "w");
	
	if (fp1 == NULL)
	{
		printf("File does not exist");
		exit(-1);
	}
	
	int line = 1;
	char *str;
	
	ch = fgetc(fp1);
		
	while (ch != EOF)
	{		
		if (ch == '#')
		{
			line = n;
		}
		
		if (line != n)
		{
			putc(ch, fp2);
		}
		if (ch == '\n')
		{
			line++;
		}
		
		ch = fgetc(fp1);
	}
	
	fclose(fp1);	
	fclose(fp2);
	
	printf("File after removal of the line no %d\n", n);
	fp1 = fopen("removed_preprocessor.c", "r");
	
	ch = fgetc(fp1);
	
	while (ch != EOF)
	{
		printf("%c", ch);
		
		ch = fgetc(fp1);
	}
	
	fclose(fp1);
	
	return 0;
}
