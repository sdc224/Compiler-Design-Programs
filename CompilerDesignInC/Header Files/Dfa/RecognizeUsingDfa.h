#pragma once

/**
 * \brief Get string length
 */
#define STRING_LENGTH(string, length) \
	{\
		char *p;\
		for(p = string; *p; p++, (length)++);\
	}
/**
 * \brief TRAP is -1, TRAP state
 */
#define TRAP (-1)
/**
 * \brief FINAL is 999, FINAL state
 */
#define FINAL 999

typedef enum operators
{
	unrecognized = -1,
	less_than = 50,
	greater_than = 51,
	less_than_equal_to = 52,
	greater_than_equal_to = 53,
	equal_to = 54,
	not_equal_to = 55,
	assign = 56,
	plus = 57,
	minus = 58,
	multiply = 59,
	divide = 60,
	modulus = 61,
	increment = 62,
	decrement = 63,
	ampersand = 64,
	xor = 65,
	or = 66,
	complement = 67,
	logical_or = 68,
	logical_and = 69,
	not = 70,
} operators;

/**
 * \brief a function to check whether the string is recognizable by the machine
 * \param string string input for checking/recognizing with DFA
 * \return if the string is recognizable, returns 1, else 0
 */
extern int recognize_ab_star(char string[]);
/**
 * \brief a function to check whether the string is keyword
 * \param string string input for checking/recognizing with DFA
 * \return if the string is a keyword, returns 1, else 0
 */
extern int recognize_keywords(char *string);
/**
 * \brief a function to check whether the string is identifier
 * \param string string input for checking/recognizing with DFA
 * \return if the string is an identifier, returns 1, else 0
 */
extern int recognize_identifier(char *string);
/**
 * \brief a function to check whether the string is identifier or keyword
 * \param string string input for checking/recognizing with DFA
 */
extern void recognize_keywords_identifiers(char *string);
char* to_symbol(operators e);
char* to_string(operators e);
extern operators recognize_operators(char *string);
extern int recognize_unsigned_no(char *string);