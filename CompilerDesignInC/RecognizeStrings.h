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