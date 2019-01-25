#include "ABstar.h"
#include <stdio.h>

int main(void)
{
	char str[100];

	printf("Enter the string: ");
	fgets(str, 100, stdin);
	
	if (recognize_ab_star(str))
		printf("\nString is valid\n");
	else
		printf("\nString is not valid\n");
	
	return 0;
}
