#include<stdio.h>
int glno=1;
int main()
{
	FILE *fp1,*fp2;
	
	int l;
	char ch;
	
	fp1=fopen("file1.txt","r");
	ch=getc(fp1);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=getc(fp1);
	}
	fclose(fp1);
	fp1=fopen("file1.txt","r");
	fp2=fopen("file2.txt","w");
	
	printf("Enter the Line number: ");
	scanf("%d", &l);
	
	ch=getc(fp1);
	while(ch!=EOF)
	{
		if(ch=='\n')
			glno++;
		if(glno!=l)
			putc(ch, fp2);
		ch=getc(fp1);
	}
	
	fclose(fp1);
	fclose(fp2);
	
	fp1=fopen("file2.txt","r");
	ch=getc(fp1);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=getc(fp1);
	}
	fclose(fp1);
	return 0;
}
