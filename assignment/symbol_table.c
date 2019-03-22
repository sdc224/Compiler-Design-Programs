#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<ctype.h>

#define STRING_LENGTH(string, length) \
	{\
		char *p;\
		for(p = string; *p; p++, (length)++);\
	}
#define TRAP (-1)
#define FINAL 999
#define MAX_NO_OF_ELEMENTS_IN_TABLE 10

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

typedef struct symbol_table
{
	int total_rows_in_table;
	char keywords[MAX_NO_OF_ELEMENTS_IN_TABLE][10];
	int no_of_keywords;
	char identifiers[MAX_NO_OF_ELEMENTS_IN_TABLE][20];
	int no_of_identifiers;
	operators oper[MAX_NO_OF_ELEMENTS_IN_TABLE];
	int no_of_operators;
	float unsigned_no[MAX_NO_OF_ELEMENTS_IN_TABLE];
	int no_of_unsigned;

}symbol_table;

symbol_table symbol;

int recognize_other_types(const char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '<' || ch == '>' || ch == '=' || ch ==
	       '(' || ch == ')' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == ',' || ch == ' ' || ch == ':' ||
	       ch == ';' || ch == '\n' ? 1 : 0;
}

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

void init_table()
{
	symbol.total_rows_in_table = 0;
	symbol.no_of_keywords = 0;
	symbol.no_of_identifiers = 0;
	symbol.no_of_operators = 0;
	symbol.no_of_unsigned = 0;
}

void copy_table(symbol_table to_be_copied)
{
	int j;

	symbol.total_rows_in_table = to_be_copied.total_rows_in_table;
	symbol.no_of_keywords = to_be_copied.no_of_keywords;
	symbol.no_of_identifiers = to_be_copied.no_of_identifiers;
	symbol.no_of_unsigned = to_be_copied.no_of_unsigned;

	for (int i = 0; i < MAX_NO_OF_ELEMENTS_IN_TABLE; i++)
	{
		for (j = 0; to_be_copied.keywords[i][j] != '\0'; j++)
			symbol.keywords[i][j] = to_be_copied.keywords[i][j];

		for (j = 0; to_be_copied.identifiers[i][j] != '\0'; j++)
			symbol.identifiers[i][j] = to_be_copied.identifiers[i][j];
	}
}

int install_keyword(const char* string)
{
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
	
	return 1;
}

int install_identifier(char* string)
{
	for (int i = 0; i < symbol.no_of_identifiers; i++)
	{
		if (strcmp(symbol.identifiers[i], string) == 0)
			return 0;
	}

	for (int i = 0; string[i] != '\0'; i++)
	{
		symbol.identifiers[symbol.no_of_identifiers][i] = string[i];
	}

	symbol.no_of_identifiers++;
	symbol.total_rows_in_table++;

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

void install_entries_into_table(char* string)
{
	const char delimiter[] = " ;\n\t,(){}";

	char* token = strtok(string, delimiter);

	operators op_code;

	while (token)
	{
		char copy[100];
		strcpy(copy, token);
		strcat(copy, " ");
		
		if (recognize_keywords(copy))
		{
			install_keyword(token);
		}
		else if ((op_code = recognize_operators(copy)))
		{
			install_operators(op_code);

			for (int i = 1; copy[i] != '\0' ; i++)
			{
				if (recognize_other_types(copy[i]))
				{
					char additional_string[50];

					int k = 0;

					for (int j = i; copy[j] != '\0'; j++)
						additional_string[k++] = copy[j];

					if ((op_code = recognize_operators(additional_string)))
					{
						install_operators(op_code);
					}
				}
			}
		}
		else if (recognize_identifier(copy))
		{
			install_identifier(token);
		}
		else if (recognize_unsigned_no(copy))
		{
			float number = 0;
			sscanf(token, "%f", &number);
			install_unsigned_no(number);
		}

		for (int i = 0; copy[i] != '\0' ; i++)
			copy[i] = '\0';

		token = strtok(NULL, delimiter);
	}
}

void display_symbol_table()
{
	int j = 1;
	
	printf("\tSerial No\t|\tName\t|\tType\n");
	printf("    ------------------------------------------------------------------------------\n");

	for (int i = 0; i < symbol.no_of_keywords; i++)
		printf("%13d%22s\t\tKeywords\t\t   -\n", j++, symbol.keywords[i]);

	for (int i = 0; i < symbol.no_of_identifiers; i++)
		printf("%13d%22s\t\tIdentifiers\t\t   -\n", j++, symbol.identifiers[i]);

	for (int i = 0; i < symbol.no_of_unsigned; i++)
		printf("%13d%22f\t\tUnsigned Number\t\t   -\n", j++, symbol.unsigned_no[i]);

	printf("\n");    
	printf("\n");
}

int main(void)
{
	FILE *fp;
	char string[100];

	if ((fp = fopen("abc.txt", "r")) == NULL)
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