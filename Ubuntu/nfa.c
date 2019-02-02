#include <stdio.h>

/**
 * \brief MAX_STATES maximum no of states
 */
//#define MAX_STATES 10
#define TRAP_STATE (-999)
#define NOT_DEFINED (-1)
//#define FINAL_STATE 999
//#define SYMBOLS 3

/*typedef struct nfa
{
	int a[10];
	int b[10];
	int epsilon[10];
}nfa;*/

int main(void)
{
	int i, j, k, l;

	int no_of_states, no_of_final_state, no_of_symbols;
	int no_of_relations = 0;
	//int final_states[MAX_STATES];

	// First, we are taking all the states as trap, to start our process
	// It also helps to remove garbage values

	/*for (i = 0; i < MAX_STATES; i++)
		final_states[i] = TRAP_STATE;*/

	// Taking all the user inputs

	printf("Enter no of states: ");
	scanf("%d", &no_of_states);
	
	printf("Enter no of symbols: ");
	scanf("%d", &no_of_symbols);

	/*printf("Enter no of final states: ");
	scanf("%d", &no_of_final_state);

	printf("Enter index(State no) of final states: ");
	for (i = 0; i < no_of_final_state; i++)
	{
		int index;
		scanf("%d", &index);
		final_states[index] = FINAL_STATE;
	}*/

	// Assuming that the first dimension indicating the states
	// second dimension indicating the symbols or edges
	// third dimension indicates the max no of relations defined for that state
	int matrix[no_of_states][no_of_symbols][no_of_states];

	//printf("We are assuming that the symbols of this NFA are \'a\' and \'b\' and \'E\'\n");
	

	// Again Garbage Collection and TRAP STATES
	for (i = 0; i < no_of_states; i++)
		for (j = 0; j < no_of_symbols; j++)
			for (k = 0; k < no_of_symbols; k++)
				matrix[i][j][k] = NOT_DEFINED;

	// taking an array of symbols to get different edges for different symbols
	// We are assuming that edges are all of integer types
	char array_of_symbols[no_of_symbols];

	// this part is not user input able right now as we are omitting user input in case of symbols
	// We are hard coding this part right now	
	printf("Here \'E\' is for epsilon (lambda NFA)\n");
	for (i = 0; i < no_of_symbols; i++)
	{
		// Assume 2 for epsilon
		printf("Enter the symbol no. %d: ",i+1);
		scanf(" %c",&array_of_symbols[i]);		
	}

	// Now taking the user input for creating the table
	for (i = 0; i < no_of_states; i++)
	{
		
		
		for (j = 0; j < no_of_symbols; j++)
		{
			printf("Enter no of relations from the state %d for the symbol %c (Enter -1 for no relations): ", i, array_of_symbols[j]);
			scanf("%d", &no_of_relations);
			
			if (no_of_relations != -1)
			{
				for (k = 0; k < no_of_relations; k++)
				{
					printf("Enter relation from the state %d for the symbol %c: ", i, array_of_symbols[j]);
					scanf("%d", &matrix[i][j][k]);
				}
			}
		}
	}
	while(1)
	{
	struct state
	{
		int inc,status;
	}st[no_of_states];
 	for(i=0;i<no_of_states;i++)
 	{
 		st[i].inc=0;
 		st[i].status=0;
 	}
 	
 	void push(int name)
 	{
 		st[name].inc=1;
 	}
 	void pop(int name)
 	{
 		st[name].status=1;
	}
	
	int lambda_state,x;
	
	printf("\nEnter the state for which Lambda Closure is to be found: ");
	scanf("%d", &lambda_state);
	
	i=lambda_state;
	push(lambda_state);
	while(i<no_of_states)
	{
		if(st[i].inc==1 && st[i].status==0)
		{
			pop(i);
			k=0;
			while(matrix[i][2][k]!=-1)
			{
				if(st[matrix[i][2][k]].status==0)
					push(matrix[i][2][k]);
				k++;
			}
			i=0;
		}
		else
			i++;
	}
	
	printf("The Lambda Closure is: ");
	for(i=0;i<no_of_states;i++)
	{
		if(st[i].inc==1)
			printf("%d, ",i);
	}
	}
}
