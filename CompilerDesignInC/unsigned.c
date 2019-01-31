#include<stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
	char ch[50],s;
	// Input:
	gets(ch);
	
	int l=strlen(ch);
	// Appending space after string(used for terminating):
	ch[l]=' ';
	ch[l+1]='\0';
	
	int i=-1,state=0;
	s=ch[++i];
	
	// State 999 is final state and -1 is a trap state
	while(s!='\0')
	{
		switch(state)
		{
			case 0: if(isdigit(s))
						state=1;
					else
						state=-1;
					break;
			case 1: if(isdigit(s))
						state=1;
					else if(s=='.')
						state=2;
					else if(s=='E' || s=='e')
						state=4;
					else if(s==' ')
						state=999;
					else
						state=-1;
					break;
			case 2: if(isdigit(s))
						state=3;
					else
						state=-1;
					break;
			case 3: if(isdigit(s))
						state=3;
					else if(s=='E' || s=='e')
						state=4;
					else if(s==' ')
						state=999;
					else
						state=-1;
					break;
			case 4: if(s=='+' || s=='-')
						state=5;
					else if(isdigit(s))
						state=6;
					else
						state=-1;
					break;
			case 5: if(isdigit(s))
						state=6;
					else
						state=-1;
					break;
			case 6: if(isdigit(s))
						state=6;
					else if(s==' ')
						state=999;
					else
						state=-1;
					break;
		}
		s=ch[++i];
	}
	if(state==999)
		printf("Valid Integer");
	else
		printf("Not Valid Integer");
}
