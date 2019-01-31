#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
	char ch[50],s,st[10];
	//char *ptr[10];
	gets(ch);
	int l=strlen(ch);
	ch[l]=' ';
	ch[l+1]='\0';
	int i=-1,state=0,z=-1;
	s=ch[++i];
	printf("The identifiers are: \n");
	while(s!='\0')
	{
		st[++z]=s;
		//printf("%c  %s\n",s,st);
		switch(state)
		{
			case 0: if(isalpha(s) || s=='_')
						state=1;
					else
						state=2;
					break;
			case 1: if(isalnum(s) || s=='_')
						state=1;
					else if(s==' ')
					{
						st[z]='\0';
						printf("%s\n",st);
						z=-1;
						s='.';
						state=0;
					}
					else
						state=2;
					break;
			case 2: if(s==' ')
					{
						z=-1;
						s='.';
						state=0;
					}
					else
						state=2;
					break;
		}
		if(s!=' ')
			s=ch[++i];
	}
}
