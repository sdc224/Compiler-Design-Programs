#include <stdio.h>

/**
 * \brief MAX_STATES maximum no of states
 */
#define MAX_STATES 10
#define TRAP_STATE (-999)
#define NOT_DEFINED (-1)
#define FINAL_STATE 999
#define SYMBOLS 3

typedef struct nfa
{
	int a[10];
	int b[10];
	int epsilon[10];
}nfa;

int main(void)
{
	int i, j, k;

	int no_of_states, no_of_final_state;
	const int no_of_relations = 0;
	int final_states[MAX_STATES];

	// First, we are taking all the states as trap, to start our process
	// It also helps to remove garbage values

	for (i = 0; i < MAX_STATES; i++)
		final_states[i] = TRAP_STATE;

	// Taking all the user inputs

	printf("Enter no of states: ");
	scanf_s("%d", &no_of_states);

	printf("Enter no of final states: ");
	scanf_s("%d", &no_of_final_state);

	printf("Enter index(State no) of final states: ");
	for (i = 0; i < no_of_final_state; i++)
	{
		int index;
		scanf_s("%d", &index);
		final_states[index] = FINAL_STATE;
	}

	// Assuming that the first dimension indicating the states
	// second dimension indicating the symbols or edges
	// third dimension indicates the max no of relations defined for that state
	int matrix[MAX_STATES][SYMBOLS][MAX_STATES];

	printf("We are assuming that the symbols of this NFA are \'a\' and \'b\' and \'E\'\n");
	printf("Here \'E\' is for epsilon (lambda NFA)\n");

	// Again Garbage Collection and TRAP STATES
	for (i = 0; i < MAX_STATES; i++)
		for (j = 0; j < SYMBOLS; j++)
			for (k = 0; k < MAX_STATES; k++)
				matrix[i][j][k] = NOT_DEFINED;

	// taking an array of symbols to get different edges for different symbols
	// We are assuming that edges are all of integer types
	int array_of_symbols[SYMBOLS];

	// this part is not user input able right now as we are omitting user input in case of symbols
	// We are hard coding this part right now	
	for (i = 0; i < SYMBOLS; i++)
	{
		// Assume 2 for epsilon
		array_of_symbols[i] = i;		
	}

	// Now taking the user input for creating the table
	for (i = 0; i < no_of_states; i++)
	{
		
		
		for (j = 0; j < SYMBOLS; j++)
		{
			printf("Enter no of relations from the state %d for the symbol %d (Enter -1 for no relations): ", i, array_of_symbols[j]);
			scanf_s("%d", no_of_relations);
			
			if (no_of_relations != -1)
			{
				for (k = 0; k < no_of_relations; k++)
				{
					printf("Enter relation from the state %d for the symbol %d: ", i, array_of_symbols[j]);
					scanf_s("%d", matrix[i][j][k]);
				}
			}
		}
	}
}