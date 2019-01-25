#include "RecognizeStrings.h"
#include <string.h>

int main(void)
{
	char str[100];	
	printf("%s", __FILE__);

	printf("Enter the string: ");
	
	//not using it due to append of \n at last
	//fgets(str, 100, stdin);

	if (fgets(str, sizeof str, stdin) != NULL) 
	{
		size_t len = strlen(str);
		if (len > 0 && str[len - 1] == '\n') 
		{
			str[--len] = '\0';
		}
	}

	const int length = strlen(str);
	if (str[length] == '\0' && str[length - 1] != ' ')
	{
		str[length] = ' ';
		str[length + 1] = '\0';
	}

	recognize_keywords_identifiers(str);
	
	return 0;
}
