#include "similarity_matrix.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef similarity_matrix_similarity_calculator_h
#define similarity_matrix_similarity_calculator_h

void initialize(char* polymerase, char* sequence);
void calculate_similarity();
void pretty_print();

// Instance Variables
char* _polymerase;
char* _sequence;
long _column_numbers;
int** _similarity_matrix;
long _row_numbers;
pthread_t* _threads;
pthread_cond_t* _signal_conds;
pthread_mutex_t _mutex;

// Methods
struct SimilarityMatrix* create_similarity_matrix();
void initialize_similarity_matrix();
void* calculate_neighbors_values_in_row(void* arg);
void initialize_first_row();
void initialize_first_column();
int calculate_for_gap_in_polymerase(long row_index, long column_index);
int calculate_for_gap_in_sequence(long row_index, long column_index);
int calculate_for_match_or_mismatch(long row_index, long column_index);
int max(int numbers[]);
int length(int* arr);

#endif
