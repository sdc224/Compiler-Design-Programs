#include <stdio.h>
#include "SymbolTable.h"
#include "RecognizeStrings.h"

int main(void)
{
	FILE *fp;
	errno_t err;
	char string[100];

	if ((err = fopen_s(&fp, "abc.txt", "r")) != 0)
	{
		perror("File was not opened\n");
	}

	else
	{
		init_table();

		while (fgets(string, sizeof string, fp) != NULL)
		{
			install_entries_into_table(string);
		}
	}

	display_symbol_table();

	return 0;
}