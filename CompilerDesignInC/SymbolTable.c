#include "SymbolTable.h"
#include "RecognizeStrings.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void init_table()
{
	//int j;

	symbol.total_rows_in_table = 0;
	symbol.no_of_keywords = 0;
	symbol.no_of_identifiers = 0;
	symbol.no_of_address = 0;
	symbol.no_of_operators = 0;
	symbol.no_of_unsigned = 0;

	//for (int i = 0; i < MAX_NO_OF_ELEMENTS_IN_TABLE; i++)
	//{
		/*for (j = 0; j < 10; j++)
			symbol.keywords[i][j] = sprintf_s(symbol.keywords[i], sizeof symbol.keywords[i], "%d", NOT_DEFINED);*/

		/*for (j = 0; j < 20; j++)
			symbol.identifiers[i][j] = sprintf_s(symbol.identifiers[i], sizeof symbol.identifiers[i], "%d", NOT_DEFINED);*/

		/*for (j = 0; j < 8; j++)
			symbol.address[i][j] = NOT_DEFINED;*/

		/*for (j = 0; j < 5; j++)
			symbol.operators[i][j] = sprintf_s(symbol.operators[i], sizeof symbol.operators[i], "%d", NOT_DEFINED);*/

		/*for (j = 0; j < 16; j++)
			symbol.unsigned_no[i][j] = NOT_DEFINED;*/
	//}
}

void copy_table(symbol_table to_be_copied)
{
	int j;

	symbol.total_rows_in_table = to_be_copied.total_rows_in_table;
	symbol.no_of_keywords = to_be_copied.no_of_keywords;
	symbol.no_of_identifiers = to_be_copied.no_of_identifiers;
	symbol.no_of_address = to_be_copied.no_of_address;
	symbol.no_of_operators = to_be_copied.no_of_operators;
	symbol.no_of_unsigned = to_be_copied.no_of_unsigned;

	for (int i = 0; i < MAX_NO_OF_ELEMENTS_IN_TABLE; i++)
	{
		for (j = 0; to_be_copied.keywords[i][j] != '\0'; j++)
			symbol.keywords[i][j] = to_be_copied.keywords[i][j];

		for (j = 0; to_be_copied.identifiers[i][j] != '\0'; j++)
			symbol.identifiers[i][j] = to_be_copied.identifiers[i][j];

		for (j = 0; to_be_copied.address[i][j] != NOT_DEFINED; j++)
			symbol.address[i][j] = to_be_copied.address[i][j];

		/*for (j = 0; to_be_copied.operators[i][j] != '\0'; j++)
			symbol.operators[i][j] = to_be_copied.operators[i][j];*/

		/*for (j = 0; to_be_copied.unsigned_no[i][j] != '\0'; j++)
			symbol.unsigned_no[i][j] = to_be_copied.unsigned_no[i][j];*/
	}
}

int install_keyword(const char* string)
{
	// strcpy_s(copy, sizeof copy, string);
	// strcat_s(copy, sizeof copy, " ");
	
	/*if (recognize_keywords(string))
	{
		
	}*/

	for (int i = 0; i < symbol.no_of_keywords; i++)
	{
		if (strcmp(symbol.keywords[i], string) == 0)
			return 0;
	}

	for (int i = 0; string[i] != '\0'; i++)
	{
		symbol.keywords[symbol.no_of_keywords][i] = string[i];
	}

	symbol.no_of_keywords++;
	symbol.total_rows_in_table++;

	/*for (int i = 0; copy[i] != '\0' ; i++)
				copy[i] = '\0';*/
	
	return 1;
}

int install_identifier(char* string)
{
	/*char copy[10];
	int state = NOT_DEFINED;
	strcpy_s(copy, sizeof copy, string);
	strcat_s(copy, sizeof copy, " ");*/

	/*if (!recognize_keywords(copy))
	{
		if (recognize_identifier(copy))
		{
			for (int i = 0; string[i] != '\0'; i++)
			{
				symbol.identifiers[symbol.no_of_identifiers++][i] = string[i];
				symbol.total_rows_in_table++;				
			}

			state = 1;
		}
	}*/

	for (int i = 0; i < symbol.no_of_identifiers; i++)
	{
		if (strcmp(symbol.identifiers[i], string) == 0)
			return 0;
	}

	for (int i = 0; string[i] != '\0'; i++)
	{
		symbol.identifiers[symbol.no_of_identifiers][i] = string[i];
	}

	install_address(string);
	symbol.no_of_identifiers++;
	symbol.total_rows_in_table++;

	/*for (int i = 0; copy[i] != '\0' ; i++)
				copy[i] = '\0';*/

	return 1;
}

int install_address(char* string)
{
	const int add = (int) malloc(string[0]);
	
	sprintf_s(symbol.address[symbol.no_of_address++], 16, "%d", add);

	return 1;
}

int install_operators(operators op_code)
{
	/*char *op_symbol = to_symbol(op_code);
	char *string = to_string(op_code);*/
	
	for (int i = 0; i < symbol.no_of_operators; i++)
	{		
		if (symbol.oper[i] == op_code)
			return 0;
	}

	symbol.oper[symbol.no_of_operators++] = op_code;	
	symbol.total_rows_in_table++;
	
	return 1;
}

int install_unsigned_no(float number)
{
	for (int i = 0; i < symbol.no_of_unsigned; i++)
		if (symbol.unsigned_no[i] == number)
			return 0;

	symbol.unsigned_no[symbol.no_of_unsigned++] = number;
	symbol.total_rows_in_table++;

	return 1;
}

int install_entries_into_table(char* string)
{
	int state = 1;
	const char delimiter[] = " ;\n\t,(){}";
	char *next_token;
	operators op_code;

	char* token = strtok_s(string, delimiter, &next_token);

	while (token)
	{
		char copy[100];
		strcpy_s(copy, sizeof copy, token);
		strcat_s(copy, sizeof copy, " ");
		
		if (recognize_keywords(copy))
		{
			install_keyword(token);
		}
		else if (recognize_identifier(copy))
		{
			install_identifier(token);
			// install_address(token);
		}
		else if ((op_code = recognize_operators(copy)))
		{
			install_operators(op_code);
		}

		else if (recognize_unsigned_no(copy))
		{
			float number = 0;
			sscanf_s(token, "%f", &number);
			install_unsigned_no(number);
		}

		for (int i = 0; copy[i] != '\0' ; i++)
			copy[i] = '\0';

		token = strtok_s(NULL, delimiter, &next_token);
	}

	return state;
}

void display_symbol_table()
{
	int j = 1;

	//printf("%d %d %d %d\n", symbol.no_of_keywords, symbol.no_of_identifiers, symbol.no_of_address, symbol.total_rows_in_table);
	
	printf("\tSerial No\t|\tName\t|\tType\t\t|\tAddress\n");
	printf("    ------------------------------------------------------------------------------\n");

	for (int i = 0; i < symbol.no_of_keywords; i++)
		printf("%13d%22s\t\tKeywords\t\t   -\n", j++, symbol.keywords[i]);
		
	for (int i = 0; i < symbol.no_of_identifiers; i++)
		printf("%13d%22s\t\tIdentifiers%20s\n", j++, symbol.identifiers[i], symbol.address[i]);

	for (int i = 0; i < symbol.no_of_operators; i++)
		printf("%13d%22s%22s\t\t   -\n", j++, to_symbol(symbol.oper[i]), to_string(symbol.oper[i]));

	for (int i = 0; i < symbol.no_of_unsigned; i++)
		printf("%13d%22f\t\tUnsigned Number\t\t   -\n", j++, symbol.unsigned_no[i]);

	printf("\n");
	
	/*
	printf("Addresses are...\n");
	for (int i = 0; i < symbol.no_of_address; i++)
		printf("%s ", symbol.address[i]);*/
	printf("\n");
}