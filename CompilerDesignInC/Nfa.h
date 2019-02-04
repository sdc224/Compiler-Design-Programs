#pragma once

/**
 * \brief MAX_STATES maximum no of states
 */
#define MAX_STATES 10
/**
 * \brief for setting a number for TRAP
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

// Global variables to use it in the whole program

// To store no of states, which is an user input
int no_of_states;

// To store total no of relations, it is also an user input
int no_of_relations;

// Assuming that the first dimension indicating the states
// second dimension indicating the symbols or edges
// third dimension indicates the max no of relations defined for that state
int matrix[MAX_STATES][SYMBOLS][MAX_STATES];

// Taking an array of symbols to get different edges for different symbols
// We are assuming that edges are all of integer types
int array_of_symbols[10];

// Define the array of relations, it is used for getting epsilon closures
// To store no of relations from any state for the symbol Epsilon
int array_of_relations[10];

// This array is used for getting the epsilon closure
// First dimension is for getting state no
// Second dimension is used for getting no of relations defined to that particular state
int epsilon_closure[10][10];

// End of global variables

extern void fill_symbols();
extern void garbage_collection();
extern void get_nfa_from_user();
extern void display_nfa();
extern void print_epsilon_closure();