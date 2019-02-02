#include<stdio.h>
int main()
{
	FILE *fp1,*fp2;
	char ch;
	
	fp1=fopen("Cprog.c","r");
	fp2=fopen("Cprog1.c","w");
	
	ch=getc(fp1);
	while(ch!=EOF)
	{
		if(ch=='#')
		{
			while(ch!='\n')
			{
				ch=getc(fp1);
			}
		}
		else
			putc(ch, fp2);
		ch=getc(fp1);
	}
	
	fclose(fp1);
	fclose(fp2);
	
	fp1=fopen("Cprog1.c","r");
	ch=getc(fp1);
	while(ch!=EOF)
	{
		printf("%c",ch);
		ch=getc(fp1);
	}
	fclose(fp1);
}
