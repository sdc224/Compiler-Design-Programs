#include <stdio.h>
#include <string.h>

int main(void)
{
	FILE *fp1;
	
	fp1 = fopen("cfg.txt", "r");
	int i = 0, prod = 1, non_term = 0, term = 0, k = 0;
	char str[100];
		
	char ch = fgetc(fp1);
	
	while (ch != EOF)
	{
		str[i++] = ch;
			
		if (ch >= 65 && ch <= 90)
			non_term++;
			
		if (ch >= 97 && ch <= 122)
			term++;
			
		ch = fgetc(fp1);
	}
	
	printf("No of productions: %d\nNo of non-terminals: %d\nNo of terminals: %d\n", prod, non_term, term);

	return 0;
}
