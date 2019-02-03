#include<stdio.h>
int main()
{
	FILE *fp1,*fp2;
	char ch,ch1;
	
	fp1=fopen("Cprog.c","r");
	fp2=fopen("Cprog1.c","w");
	
	ch=getc(fp1);
	while(ch!=EOF)
	{
		if(ch!=' ' && ch!='\n' && ch!='\t')
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
