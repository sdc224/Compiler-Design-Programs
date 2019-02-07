#include "RecognizeStrings.h"
#include "AddString.h"
#include <ctype.h>
#include <stdio.h>

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
 * \return if the string is a keyword, returns 1, else 0
 */
int recognize_keywords(char *string)
{
	int length = 0, i = 0, state = 0, k = 0;	
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
				}
				else
					state = TRAP;

				break;
				
			case 4:
				if (recognize_other_types(string[i]))
				{
					state = FINAL;
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

/**
 * \brief a function to check whether the string is identifier
 * \param string string input for checking/recognizing with DFA
 * \return if the string is an identifier, returns 1, else 0
 */
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
				else
					state = TRAP;

				break;

			case 1:
				if (isalpha(string[i]) || isdigit(string[i]))
					state = FINAL;

				else if (string[i] == '_' && i < length)
					state = FINAL;

				break;

			case FINAL:
				if (!isalpha(string[i]) && !isdigit(string[i]) && !recognize_other_types(string[i]))
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

/**
 * \brief a function to check whether the string is identifier or keyword
 * \param string string input for checking/recognizing with DFA
 */
void recognize_keywords_identifiers(char *string)
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
}

char *to_symbol(operators e)
{
	switch (e)
	{
		case less_than: return "<";
		case greater_than: return ">";
		case less_than_equal_to: return "<=";
		case greater_than_equal_to: return ">=";
		case equal_to: return "==";
		case not_equal_to: return "!=";
		case assign: return "=";
		case plus: return "+";
		case minus: return "-";
		case multiply: return "*";
		case divide: return "/";
		case modulus: return "%";
		case increment: return "++";
		case decrement: return "--";
		case ampersand: return "&";
		case xor: return "^";
		case or: return "|";
		case complement: return "~";
		case logical_or: return "||";
		case logical_and: return "&&";
		case not: return "!";
		case unrecognized: return "unrecognized";
		default: return "unknown";
	}
}

char* to_string(operators e)
{
	switch (e)
	{
	case less_than: return "less_than";
	case greater_than: return "greater_than";
	case less_than_equal_to: return "less_than_equal_to";
	case greater_than_equal_to: return "greater_than_equal_to";
	case equal_to: return "equal_to";
	case not_equal_to: return "not_equal_to";
	case assign: return "assign";
	case plus: return "plus";
	case minus: return "minus";
	case multiply: return "multiply";
	case divide: return "divide";
	case modulus: return "modulus";
	case increment: return "increment";
	case decrement: return "decrement";
	case ampersand: return "ampersand";
	case xor: return "xor";
	case or: return "or";
	case complement: return "complement";
	case logical_or: return "logical_or";
	case logical_and: return "logical_and";
	case not: return "not";
	case unrecognized: return "unrecognized";
	default: return "unknown";
	}
}

operators recognize_operators(char *string)
{
	int state = 0, i = 0;

	while (*(string + i))
	{
		switch (state)
		{
			case TRAP:
				state = TRAP;
				break;
			
			case 0:
				if (string[i] == '<')
					state = 1;
				else if (string[i] == '>')
					state = 3;
				else if (string[i] == '=')
					state = 5;
				else if (string[i] == '!')
					state = 7;
				else if (string[i] == '+')
					state = 9;
				else if (string[i] == '-')
					state = 11;
				else if (string[i] == '*')
					state = 13;
				else if (string[i] == '/')
					state = 15;
				else if (string[i] == '%')
					state = 17;
				else if (string[i] == '&')
					state = 19;
				else if (string[i] == '^')
					state = 21;
				else if (string[i] == '|')
					state = 23;
				else if (string[i] == '~')
					state = 25;

				break;

			case 1:
				if (string[i] == '=')
					state = 2;
				else if (isalpha(string[i]) || isdigit(string[i]) || string[i] == ' ')
					state = less_than;
				else
					state = TRAP;
				break;

			case 2:
				if (string[i] == ' ' || isalnum(string[i]))
					state = less_than_equal_to;
				else
					state = TRAP;
				break;

			case 3:
				if (string[i] == ' ' || isalnum(string[i]))
					state = greater_than;
				else if (string[i] == '=')
					state = 4;
				else
					state = TRAP;
				break;

			case 4:
				if (string[i] == ' ' || isalnum(string[i]))
					state = greater_than_equal_to;
				else
					state =TRAP;
				break;

			case 5:
				if (string[i] == ' ' || isalnum(string[i]))
					state = assign;
				else if (string[i] == '=')
					state = 6;
				else
					state = TRAP;
				break;

			case 6:
				if (string[i] == ' ' || isalnum(string[i]))
					state = equal_to;
				else
					state = TRAP;
				break;

			case 7:
				if (string[i] == ' ' || isalnum(string[i]))
					state = not;
				else if (string[i] == '=')
					state = 8;
				else
					state = TRAP;
				break;

			case 8:
				if (string[i] == ' ' || isalnum(string[i]))
					state = not_equal_to;
				else
					state = TRAP;
				break;

			case 9:
				if (string[i] == ' ' || isalnum(string[i]))
					state = plus;
				else if (string[i] == '+')
					state = 10;
				else
					state = TRAP;
				break;

			case 10:
				if (string[i] == ' ' || isalnum(string[i]))
					state = increment;
				else
					state = TRAP;
				break;

			case 11:
				if (string[i] == ' ' || isalnum(string[i]))
					state = minus;
				else if (string[i] == '-')
					state = 12;
				else
					state = TRAP;
				break;

			case 12:
				if (string[i] == ' ' || isalnum(string[i]))
					state = decrement;
				else
					state = TRAP;
				break;

			case 13:
				if (string[i] == ' ' || isalnum(string[i]))
					state = multiply;
				else
					state = TRAP;
				break;

			case 14:
				break;

			case 15:
				if (string[i] == ' ' || isalnum(string[i]))
					state = divide;
				else
					state = TRAP;
				break;

			case 16:
				break;

			case 17:
				if (string[i] == ' ' || isalnum(string[i]))
					state = modulus;
				else
					state = TRAP;
				break;

			case 18:
				break;

			case 19:
				if (string[i] == ' ' || isalnum(string[i]))
					state = ampersand;
				else if (string[i] == '&')
					state = 20;
				else
					state = TRAP;
				break;

			case 20:
				if (string[i] == ' ' || isalnum(string[i]))
					state = logical_and;
				else
					state = TRAP;
				break;

			case 21:
				if (string[i] == ' ' || isalnum(string[i]))
					state = xor;
				else
					state = TRAP;
				break;

			case 22:
				break;

			case 23:
				if (string[i] == ' ' || isalnum(string[i]))
					state = or;
				else if (string[i] == '|')
					state = 24;
				else
					state = TRAP;
				break;

			case 24:			
				if (string[i] == ' ' || isalnum(string[i]))
					state = logical_or;
				else
					state = TRAP;	
				break;

			case 25:
				if (string[i] == ' ' || isalnum(string[i]))
					state = complement;
				else
					state = TRAP;
				break;

			case 26:
				break;

			default:
				break;
		}

		i++;
	}

	return state == TRAP ? unrecognized : state;
}

int recognize_unsigned_no(char *string)
{
	int l = 0;
	STRING_LENGTH(string, l);
	
	int i=-1,state=0;
	char s = string[++i];
	
	// State 999 is final state and -1 is a trap state
	while(s!='\0')
	{
		switch(state)
		{
			case 0: 
				if(isdigit(s))
					state=1;
				else
					state=TRAP;
				break;

			case 1: 
				if(isdigit(s))
					state=1;
				else if(s=='.')
					state=2;
				else if(s=='E' || s=='e')
					state=4;
				else if(s==' ')
					state=FINAL;
				else
					state=TRAP;
				break;

			case 2: 
				if(isdigit(s))
					state=3;
				else
					state=TRAP;
				break;

			case 3: 
				if(isdigit(s))
					state=3;
				else if(s=='E' || s=='e')
					state=4;
				else if(s==' ')
					state=FINAL;
				else
					state=TRAP;
				break;

			case 4: 
				if(s=='+' || s=='-')
					state=5;
				else if(isdigit(s))
					state=6;
				else
					state=TRAP;
				break;

			case 5: 
				if(isdigit(s))
					state=6;
				else
					state=TRAP;
				break;

			case 6: 
				if(isdigit(s))
					state=6;
				else if(s==' ')
					state=FINAL;
				else
					state=TRAP;
				break;

			default:
				break;
		}

		s=string[++i];
	}

	return state == FINAL ? 1 : 0;
}