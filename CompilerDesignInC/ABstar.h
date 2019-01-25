#pragma once

/**
 * \brief Get string length
 */
#define STRING_LENGTH(string, length) \
	{\
		char *p;\
		for(p = string; *p; p++, length++);\
	}
/**
 * \brief TRAP is -1, TRAP state
 */
#define TRAP -1
/**
 * \brief FINAL is 999, FINAL state
 */
#define FINAL 999

/**
 * \brief a function ro check whether the string is recognizable by the machine
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

