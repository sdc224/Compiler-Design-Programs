#pragma once

/**
 * \brief Maximum no elements in a symbol table
 */
#define MAX_NO_OF_ELEMENTS_IN_TABLE 10
/**
 * \brief It is not defined, value is -1
 */
#define NOT_DEFINED (-1)

/**
 * \brief Data Structure for Symbol Table
 */
typedef struct symbol_table
{
	int total_rows_in_table;
	char keywords[MAX_NO_OF_ELEMENTS_IN_TABLE][10];
	int no_of_keywords;
	char identifiers[MAX_NO_OF_ELEMENTS_IN_TABLE][20];
	int no_of_identifiers;
	char address[MAX_NO_OF_ELEMENTS_IN_TABLE][16];
	int no_of_address;
	char operators[MAX_NO_OF_ELEMENTS_IN_TABLE][5];
	int no_of_operators;
	char unsigned_no[MAX_NO_OF_ELEMENTS_IN_TABLE][16];
	int no_of_unsigned;

}symbol_table;

/**
 * \brief Global Symbol Table, will be used for storing as well as fetching data
 */
symbol_table symbol;

extern void init_table();
extern void copy_table(symbol_table to_be_copied);
extern int install_keyword(const char *string);
extern int install_identifier(const char *string);
extern int install_address(char *string);
extern int install_operators(char *string);
extern int install_unsigned_no(char *string);
extern int install_entries_into_table(char *string);
extern void display_symbol_table();