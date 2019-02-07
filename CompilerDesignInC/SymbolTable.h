#pragma once

#include "RecognizeStrings.h"

#define MAX_NO_OF_ELEMENTS_IN_TABLE 10

typedef struct symbol_table
{
	char keywords[MAX_NO_OF_ELEMENTS_IN_TABLE][10];
	int no_of_keywords;
	char identifiers[MAX_NO_OF_ELEMENTS_IN_TABLE][20];
	int address_of_identifiers[MAX_NO_OF_ELEMENTS_IN_TABLE][8];
	int no_of_identifiers;
	char operators[MAX_NO_OF_ELEMENTS_IN_TABLE][5];
	int no_of_operators;
	char unsigned_no[MAX_NO_OF_ELEMENTS_IN_TABLE][16];
}symbol_table;
