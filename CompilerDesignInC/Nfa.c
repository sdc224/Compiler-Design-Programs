#include "Nfa.h"
#include "ArrayOfIntegers.h"
#include <stdio.h>

void fill_symbols()
{
	// this part is not user input able right now as we are omitting user input in case of symbols
	// We are hard coding this part right now	
	for (int i = 0; i < SYMBOLS; i++)
	{
		// Assume 2 for epsilon
		array_of_symbols[i] = i;
	}
}

void garbage_collection()
{
	// Garbage Collection
	for (int i = 0; i < MAX_STATES; i++)
	{
		for (int j = 0; j < MAX_STATES; j++)
		{
			epsilon_closure[i][j] = NOT_DEFINED;
		}
	}
	
	//Again Garbage Collection and TRAP STATES
	for (int i = 0; i < MAX_STATES; i++)
		for (int j = 0; j < SYMBOLS; j++)
			for (int k = 0; k < MAX_STATES; k++)
				matrix[i][j][k] = NOT_DEFINED;

	// Not required part or unused part of the program
	/*
	printf("Enter no of final states: ");
	scanf_s("%d", &no_of_final_state);

	printf("Enter index(State no) of final states: ");
	for (i = 0; i < no_of_final_state; i++)
	{
		int index;
		scanf_s("%d", &index);
		final_states[index] = FINAL_STATE;
	}
	*/
}

void get_nfa_from_user()
{
	int i;

	garbage_collection();

	/*// First, we are taking all the states as trap, to start our process
	// It also helps to remove garbage values	
	for (i = 0; i < MAX_STATES; i++)
		final_states[i] = TRAP_STATE;*/
	
	printf("We are assuming that the symbols of this NFA are \'a\' and \'b\' and \'E\'\n");
	printf("Here \'E\' is for epsilon (lambda NFA)\n");

	// Taking all the user inputs
	printf("Enter no of states: ");
	scanf_s("%d", &no_of_states);

	fill_symbols();

	// Now taking the user input for creating the table
	for (i = 0; i < no_of_states; i++)
	{		
		for (int j = 0; j < SYMBOLS; j++)
		{
			printf("Enter no of relations from the state %d for the symbol %d (Enter -1 for no relations): ", i, array_of_symbols[j]);
			scanf_s("%d", &no_of_relations);
			if (j == 2)
				array_of_relations[i] = no_of_relations;
			
			if (no_of_relations != -1)
			{
				for (int k = 0; k < no_of_relations; k++)
				{
					printf("Enter relation from the state %d for the symbol %d: ", i, array_of_symbols[j]);
					scanf_s("%d", &matrix[i][j][k]);
				}
			}
			else
				matrix[i][j][0] = TRAP_STATE;
		}
	}

	// For setting the end of array_of_relations
	array_of_relations[i] = TRAP_STATE;	
}

void display_nfa()
{
	printf("\n\nDisplaying the NFA Table.......\n\n");
	
	printf("\tSTATE\t|");

	for (int i = 0; i < SYMBOLS; i++)
	{
		printf("\t%d\t|", array_of_symbols[i]);
	}

	printf("\n");
	printf("-----------------------------------------------------------------------\n");
	
	for (int i = 0; i < no_of_states; i++)
	{
		printf("\t%d\t|", i);

		for (int j = 0; j < SYMBOLS; j++)
		{
			for (int k = 0; matrix[i][j][k] != NOT_DEFINED; k++)
			{
				if (matrix[i][j][k] == TRAP_STATE)
					printf("\t-");
				else
				{
					if (k == 0)
						printf("\t\b{%d", matrix[i][j][k]);
					else
						printf("%d", matrix[i][j][k]);

					if (matrix[i][j][k + 1] != NOT_DEFINED)
						printf(", ");
					else
						printf("}");
				}
			}

			printf("\t|");
		}

		printf("\n");
	}

	printf("-----------------------------------------------------------------------\n\n");	
}

void print_epsilon_closure()
{
	// Here i is state no
	// For creating the epsilon closures for the states where Epsilon state is given as -1 (user input)
	for (int i = 0; array_of_relations[i] != TRAP_STATE; i++)
	{
		if (array_of_relations[i] == -1)
		{
			epsilon_closure[i][0] = i;
			epsilon_closure[i][1] = NOT_DEFINED;
		}
		else
		{
			int flag = 0;
			int k = 0;

			for (int j = 0; j < array_of_relations[i]; j++)
			{
				if (matrix[i][2][j] == i)
				{
					flag = 1;
					epsilon_closure[i][k++] = i;
				}
				else
				{
					epsilon_closure[i][k++] = matrix[i][2][j];
				}
			}

			if (flag != 1)
				epsilon_closure[i][k++] = i;
		}
	}

	// For creating the epsilon closure for state having other state as their epsilon transitions
	for (int i = 0; i < no_of_states; i++)
	{
		int k = index_of(epsilon_closure[i], MAX_STATES, NOT_DEFINED);
		int j = 0;

		while(epsilon_closure[i][j] != NOT_DEFINED && j < no_of_states)
		{
			if (epsilon_closure[i][j] != i)
			{
				const int k1 = index_of(epsilon_closure[epsilon_closure[i][j]], MAX_STATES, -1);
				for (int l = 0; l < k1; l++)
				{
					epsilon_closure[i][k++] = epsilon_closure[epsilon_closure[i][j]][l];
				}
			}
			j++;
		}
	}	

	// For storing the size of all states (their relations)
	int size[MAX_STATES];

	// Sorting and removing duplicate elements
	for (int i = 0; i < no_of_states; i++)
	{		
		size[i] = index_of(epsilon_closure[i], MAX_STATES, NOT_DEFINED);
		sort(epsilon_closure[i], size[i]);
		size[i] = remove_duplicates_from_sorted_array(epsilon_closure[i], size[i]);
	}

	// The Output of Epsilon Closures	
	printf("Epsilon Closures....\n");
	for (int i = 0; i < no_of_states; i++)
	{
		printf("Epsilon Closure for state %d is : {", i);
		for (int j = 0; j < size[i]; j++)
		{
			printf("%d", epsilon_closure[i][j]);

			if (j != size[i] - 1)
				printf(", ");
		}

		printf("}\n");
	}
}