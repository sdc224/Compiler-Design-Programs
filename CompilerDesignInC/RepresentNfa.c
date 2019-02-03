#include <stdio.h>

/**
 * \brief MAX_STATES maximum no of states
 */
#define MAX_STATES 10
/**
 * \brief for setting a no for TRAP
 */
#define TRAP_STATE (-999)
/**
 * \brief Setting a value for whether it is defined or not
 */
#define NOT_DEFINED (-1)
/**
 * \brief 999 for getting FINAL State
 */
#define FINAL_STATE 999
/**
 * \brief No of symbols used in this programs
 */
#define SYMBOLS 3

// Utility Functions
int index_of(const int arr[], const int element)
{
	for (int i = 0; i < MAX_STATES; i++)
	{
		if (arr[i] == element)
			return i;
	}

	return NOT_DEFINED;
}

void sort_array(int arr[], int n)
{
	int swapped = 0;

	for (int i = 0; i < n - 1; i++)
	{
		swapped = 0;

		for (int j = 0; j < n - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				const int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
		}

		if (swapped == 0)
			break;
	}
}

int remove_duplicates(int arr[], const int n)
{
	if (n == 0 || n == 1)
		return n;

	int j = 0;

	for (int i = 0; i < n - 1; i++)
		if (arr[i] != arr[i + 1])
			arr[j++] = arr[i];

	arr[j++] = arr[n - 1];

	return j;
}
// End of Utility Functions

int main(void)
{
	int i, j, k;
	int no_of_states;
	int no_of_relations = 0;	

	/*// First, we are taking all the states as trap, to start our process
	// It also helps to remove garbage values	
	for (i = 0; i < MAX_STATES; i++)
		final_states[i] = TRAP_STATE;*/

	// Taking all the user inputs
	printf("Enter no of states: ");
	scanf_s("%d", &no_of_states);
	
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
	
	Again Garbage Collection and TRAP STATES
	for (i = 0; i < MAX_STATES; i++)
		for (j = 0; j < SYMBOLS; j++)
			for (k = 0; k < MAX_STATES; k++)
				matrix[i][j][k] = NOT_DEFINED;
	*/

	// Assuming that the first dimension indicating the states
	// second dimension indicating the symbols or edges
	// third dimension indicates the max no of relations defined for that state
	int matrix[MAX_STATES][SYMBOLS][MAX_STATES];

	printf("We are assuming that the symbols of this NFA are \'a\' and \'b\' and \'E\'\n");
	printf("Here \'E\' is for epsilon (lambda NFA)\n");

	// Taking an array of symbols to get different edges for different symbols
	// We are assuming that edges are all of integer types
	int array_of_symbols[SYMBOLS];

	// this part is not user input able right now as we are omitting user input in case of symbols
	// We are hard coding this part right now	
	for (i = 0; i < SYMBOLS; i++)
	{
		// Assume 2 for epsilon
		array_of_symbols[i] = i;
	}

	int array_of_relations[MAX_STATES];

	// Now taking the user input for creating the table
	for (i = 0; i < no_of_states; i++)
	{		
		for (j = 0; j < SYMBOLS; j++)
		{
			printf("Enter no of relations from the state %d for the symbol %d (Enter -1 for no relations): ", i, array_of_symbols[j]);
			scanf_s("%d", &no_of_relations);
			if (j == 2)
				array_of_relations[i] = no_of_relations;
			
			if (no_of_relations != -1)
			{
				for (k = 0; k < no_of_relations; k++)
				{
					printf("Enter relation from the state %d for the symbol %d: ", i, array_of_symbols[j]);
					scanf_s("%d", &matrix[i][j][k]);
				}
			}
		}
	}

	// For setting the end of array_of_relations
	array_of_relations[i] = TRAP_STATE;

	// This array is used for getting the epsilon closure
	// First dimension is for getting state no
	// Second dimension is used for getting no of relations defined to that particular state
	int epsilon_closure[MAX_STATES][MAX_STATES];

	// Garbage Collection
	for (i = 0; i < MAX_STATES; i++)
	{
		for (j = 0; j < MAX_STATES; j++)
		{
			epsilon_closure[i][j] = NOT_DEFINED;
		}
	}

	// Here i is state no
	// For creating the epsilon closures for the states where Epsilon state is given as -1 (user input)
	for (i = 0; array_of_relations[i] != TRAP_STATE; i++)
	{
		if (array_of_relations[i] == -1)
		{
			epsilon_closure[i][0] = i;
			epsilon_closure[i][1] = NOT_DEFINED;
		}
		else
		{
			int flag = 0;
			k = 0;

			for (j = 0; j < array_of_relations[i]; j++)
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
	for (i = 0; i < no_of_states; i++)
	{
		k = index_of(epsilon_closure[i], NOT_DEFINED);
		j = 0;

		while(epsilon_closure[i][j] != NOT_DEFINED && j < no_of_states)
		{
			if (epsilon_closure[i][j] != i)
			{
				const int k1 = index_of(epsilon_closure[epsilon_closure[i][j]], -1);
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
	for (i = 0; i < no_of_states; i++)
	{		
		size[i] = index_of(epsilon_closure[i], NOT_DEFINED);
		sort_array(epsilon_closure[i], size[i]);
		size[i] = remove_duplicates(epsilon_closure[i], size[i]);
	}

	// The Output of Epsilon Closures	
	printf("Epsilon Closures....\n");
	for (i = 0; i < no_of_states; i++)
	{
		printf("Epsilon Closure for state %d is : {", i);
		for (j = 0; j < size[i]; j++)
		{
			printf("%d", epsilon_closure[i][j]);

			if (j != size[i] - 1)
				printf(", ");
		}

		printf("}\n");
	}
}