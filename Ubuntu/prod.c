#include<stdio.h>

int main()
{
	FILE *fp;
	fp=fopen("cfg.txt","r");
	
	char variables[10],terminals[20],*prod[10],ch,ch1,str[10];
	int p=-1,q=-1,r=-1,s=-1,i=0,f;
	
	printf("\nProductions:\n");
	ch=getc(fp);
	
	while(ch!=EOF)
	{
		if(ch>='A' && ch<='Z')
		{
			f=0,i=0;
			while(i<=p)
			{
				if(variables[i]==ch)
				{
					f=1;
					break;
				}
				i++;
			}
			if(f==0)
				variables[++p]=ch;
		}
		else if(ch=='-')
		{
			ch1=getc(fp);
			if(ch1=='>')
			{
				ch=getc(fp);
				while(ch!='\n')
				{
					if(!(ch>='A' && ch<='Z'))
					{
						int f=0;
						i=0;
						while(i<=q)
						{
							if(terminals[i]==ch)
							{
								f=1;
								break;
							}
							i++;
						}
						if(f==0)	
							terminals[++q]=ch;
					}
					str[++s]=ch;
					ch=getc(fp);
				}
				str[++s]='\0';
				printf("%s\n",str);
				//prod[++r]=str;
				s=-1;
			}
		}
		ch=getc(fp);
	}
	printf("\nVariables: \n");
	for(i=0;i<=p;i++)
		printf("%c, ",variables[i]);
	
	printf("\nTerminals: \n");
	for(i=0;i<=q;i++)
		printf("%c, ",terminals[i]);
	
	/*printf("\nProductions: \n");
	for(i=0;i<=r;i++)
		printf("%s, ",prod[i]);*/
	
}
