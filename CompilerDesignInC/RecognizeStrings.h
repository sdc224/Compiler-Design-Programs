#pragma once
#include <ctype.h>
#include "AddString.h"
#include <stdio.h>
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
int recognize_ab_star(char string[])
{
	int length = -1, i = 0, state = 0;
	STRING_LENGTH(string, length);	

	while (*(string + i))
	{
		switch (state)
		{
			case TRAP:
				break;
			
			case 0:
				if (*(string + i) == 'a')
				{
					state = 1;

					if(i == length - 1)
						state = FINAL;
				}

				break;

			case 1:
				if (*(string + i) == 'b')
					state = FINAL;
				else
					state = TRAP;

				break;

			case FINAL:
				if(*(string + i) == 'a')
					state = TRAP;

				break;
			
			default:
				state = TRAP;
				break;
		}

		i++;
	}

	return state == FINAL ? 1 : 0;
}

/**
 * \brief a function to check whether the string is keyword
 * \param string string input for checking/recognizing with DFA
 * \param keywords to collect all the keywords
 * \return if the string is a keyword, returns 1, else 0
 */
int recognize_keywords(char *string)
{
	int length = 0, i = 0, state = 0, k = 0;	
	char* keywords[10];	
	STRING_LENGTH(string, length);

	while (*(string + i))
	{
		switch(state)
		{
			case TRAP:
				break;
			
			case 0:				
				if (string[i] == 'i')
					state = 1;

				else if (string[i] == 'c')
					state = 5;
					
				else if (string[i] == 'f')
					state = 9;
					
				else if (string[i] == 'e')
					state = 16;
			
				break;
			
			case 1:
				if (string[i] == 'f')
					state = 4;
					
				else if (string[i] == 'n')
					state = 2;
				
				break;
			
			case 2:
				if (string[i] == 't')
					state = 3;
					
				break;

			case 3:
				if (recognize_other_types(string[i]))
				{
					state = FINAL;
					keywords[k++] = "int";
				}
				else
					state = TRAP;

				break;
				
			case 4:
				if (recognize_other_types(string[i]))
				{
					state = FINAL;
					keywords[k++] = "if";
				}
				else
					state = TRAP;
					
				break;
				
			case 5:
				if (string[i] == 'h')
					state = 6;
					
				break;
				
			case 6:
				if (string[i] == 'a')
					state = 7;
					
				break;
			
			case 7:
				if (string[i] == 'r')
					state = 8;
					
				break;

			case 8:
				if (recognize_other_types(string[i]))
				{
					state = FINAL;
					keywords[k++] = "char";
				}
				else
					state = TRAP;

				break;
				
			case 9:
				if (string[i] == 'o')
					state = 14;
					
				else if (string[i] == 'l')
					state = 10;
					
				break;

			case 10:
				if (string[i] == 'o')
					state = 11;

				break;

			case 11:
				if (string[i] == 'a')
					state = 12;

				break;

			case 12:
				if (string[i] == 't')
					state = 13;

				break;

			case 13:
				if (recognize_other_types(string[i]))
				{
					state = FINAL;
					keywords[k++] = "float";
				}
				else
					state = TRAP;

				break;

			case 14:
				if (string[i] == 'r')
					state = 15;

				break;

			case 15:
				if (recognize_other_types(string[i]))
				{
					state = FINAL;
					keywords[k++] = "for";
				}
				else
					state = TRAP;

				break;

			case 16:
				if (string[i] == 'l')
					state = 17;

				break;

			case 17:
				if (string[i] == 's')
					state = 18;

				break;

			case 18:
				if (string[i] == 'e')
					state = 19;

				break;

			case 19:
				if (recognize_other_types(string[i]))
				{
					state = FINAL;
					keywords[k++] = "else";
				}
				else
					state = TRAP;

				break;

			case FINAL:
				if (string[i] != '\0')
					state = TRAP;

				break;
				
			default:
				state = TRAP;
				break;
		}
		
		i++;
	}
	
	return state == FINAL ? 1 : 0;		
}

int recognize_identifier(char *string)
{
	int length = 0, i = 0, state = 0;
	STRING_LENGTH(string, length);

	while (*(string + i))
	{
		switch (state)
		{
			case TRAP:
				break;
			
			case 0:
				if (string[i] == '_')
				{
					if (i == length - 2)
						state = TRAP;
					else
						state = 1;
				}
				else if (isalpha(string[i]))
				{
					if (i == length - 2)
						state = FINAL;
					else
						state = 1;
				}

				break;

			case 1:
				if (isalpha(string[i]))
					state = FINAL;

				else if (string[i] == '_' && i < length)
					state = FINAL;

				break;

			case FINAL:
				if (!isalpha(string[i]) && !recognize_other_types(string[i]))
				{
					if (string[i] == '_')
						state = 1;
					else
						state = TRAP;
				}
				else
					state = FINAL;

				break;

			default:
				state = TRAP;
				break;
		}

		i++;
	}

	return state == 999 ? 1 : 0;
}

int recognize_keywords_identifiers(char string[])
{
	char optional_string[100];

	int i = 0, j = 0, k = 0, length = 0;

	STRING_LENGTH(string, length);

	while (j <= length && i <= j)
	{		
		if (!recognize_other_types(string[j]) || isdigit(string[j]))
			j++;

		if (recognize_other_types(string[j] && j + 1 == length))
			break;

		if (recognize_other_types(string[j]) && i != j || j == length && i != j)
		{
			for (int l = i; l <= j; l++)
				optional_string[k++] = string[l];

			optional_string[k++] = '\0';

			if (recognize_keywords(optional_string))
				printf("Keyword = %s\n", optional_string);

			else if (recognize_identifier(optional_string))
				printf("Identifier = %s\n", optional_string);

			else
				printf("%s is a wrong string input\n", optional_string);

			k = 0;
			j++;
			i = j;	
		}
	}

	return 0;
}