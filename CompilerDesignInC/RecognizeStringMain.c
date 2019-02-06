#include <stdio.h>  /* defines FILENAME_MAX */
//#define WINDOWS  /* uncomment this line to use it for windows.*/
//#ifdef WINDOWS
//#include <direct.h>
//#define GetCurrentDir _getcwd
//#else
//#include <unistd.h>
//#define GetCurrentDir getcwd
//#endif
#include "RecognizeStrings.h"
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char str[100];
	const char delimiter[] = " ;\n\t,";
	char *next_token;

	// To know current directory
	// char buff[FILENAME_MAX];
	// GetCurrentDir( buff, FILENAME_MAX );
	// printf("Current working dir: %s\n", buff);

	// For Question 2 & 3
	/*printf("Enter the string: ");
	
	// not using it due to append of \n at last
	// fgets(str, 100, stdin);

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

	recognize_keywords_identifiers(str);*/

	// For Question 5	
	FILE *fp;
	errno_t err;

	if ((err = fopen_s(&fp, "abc.txt", "r")) != 0)
	{
		perror("File was not opened\n");
	}
	else
	{
		int line = 0;

		while (fgets(str, sizeof str, fp) != NULL)
		{
			line++;

			char* token = strtok_s(str, delimiter, &next_token);

			while (token)
			{	
				char copy[100];
				strcpy_s(copy, sizeof copy, token);
				strcat_s(copy, sizeof copy, " ");
				
				if (recognize_keywords(copy) == 0)
				{
					if (recognize_identifier(copy))
					{
						printf("%s Identifier found at line %d\n", token, line);
					}
				}

				for (int i = 0; copy[i] != '\0' ; i++)
					copy[i] = '\0';

				token = strtok_s(NULL, delimiter, &next_token);
			}
		}		
	}

	fclose(fp);
	
	return 0;
}
