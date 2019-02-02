
int main(void)
{
	FILE *fp1, *fp2;
	char ch;
	int i, n;
	
	fp1 = fopen("a.txt", "r");
	fp2 = fopen("c.txt", "w");
	
	if (fp1 == NULL)
	{
		printf("File does not exist");
		exit(-1);
	}
	
	printf("Enter line no you want to delete: ");
	scanf("%d", &n);
	
	int line = 1;
	char *str;
	
	ch = fgetc(fp1);
		
	while(ch != EOF)
	{		
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
	fp1 = fopen("c.txt", "r");
	
	ch = fgetc(fp1);
	
	while (ch != EOF)
	{
		printf("%c", ch);
		
		ch = fgetc(fp1);
	}
	
	fclose(fp1);
	
	return 0;
}
