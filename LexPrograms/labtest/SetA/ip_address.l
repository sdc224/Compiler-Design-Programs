%{
	#include <stdio.h>
	#include <string.h>
	#include <arpa/inet.h>
	int no_of_ip = 0;
%}
d	[0-9]
%%
^({d}?{d}?{d}"."{d}?{d}?{d}"."{d}?{d}?{d}"."{d}?{d}?{d})$	{
																if (inet_addr(yytext) != -1)
																{
																	no_of_ip++;
																	printf("%s\n", yytext);
																}
																else if (strcmp(yytext, "255.255.255.255") == 0)
																{
																	no_of_ip++;
																	printf("%s\n", yytext);
																}
															}
.	{}
%%
int main(void)
{
	yyin = fopen("ip.txt", "r");
	yylex();
	printf("Total no of IP addresses: %d\n", no_of_ip);
	return 0;
}
