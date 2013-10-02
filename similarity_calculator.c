#include "similarity_calculator.h"

#define MIN_VALUE 0
#define WILD_CARD '?'

void initialize(char* polymerase, char* sequence) {
  _polymerase = polymerase;
  _sequence = sequence;
  _column_numbers = strlen(_sequence) + 1;
  _row_numbers = strlen(_polymerase) + 1;
}

void calculate_similarity() {
  initialize_similarity_matrix();

  int i;
  struct SimilarityMatrix* sim_matrix = create_similarity_matrix();
  for (i = 1; i < _row_numbers; i++) {
    sim_matrix->row_index = i;
    calculate_neighbors_values_in_row((void*)sim_matrix);
  }
}

struct SimilarityMatrix* create_similarity_matrix() {
  struct SimilarityMatrix* sim_matrix = malloc(sizeof(struct SimilarityMatrix));
  sim_matrix->matrix = _similarity_matrix;
  sim_matrix->row_numbers = _row_numbers;
  sim_matrix->column_numbers = _column_numbers;

  return sim_matrix;
}

void* calculate_neighbors_values_in_row(void* arg) {
  int neighbor_values[4];
  neighbor_values[3] = MIN_VALUE;
  struct SimilarityMatrix* similarity_matrix = arg;
  int j;
  for (j = 1; j < similarity_matrix->column_numbers; j++) {
    while (similarity_matrix->matrix[similarity_matrix->row_index][j - 1] == -1 || 
        similarity_matrix->matrix[similarity_matrix->row_index - 1][j] == -1 ||
        similarity_matrix->matrix[similarity_matrix->row_index - 1][j - 1] == -1) {
      printf("Waiting!\n");
    }


    neighbor_values[0] = calculate_for_gap_in_polymerase(
        similarity_matrix->row_index, j);
    neighbor_values[1] = calculate_for_gap_in_sequence(
        similarity_matrix->row_index, j);
    neighbor_values[2] = calculate_for_match_or_mismatch(
        similarity_matrix->row_index, j);

    similarity_matrix->matrix[similarity_matrix->row_index][j] = 
      max(neighbor_values);
  }
} 

void pretty_print() {
  int row_numbers = strlen(_polymerase) + 1;
  int column_numbers = strlen(_sequence) + 1;
  int i, j;
  for (i = 0; i < row_numbers; i++) {
    for (j = 0; j < column_numbers; j++)
      printf("%d ", _similarity_matrix[i][j]);
    printf("\n");
  }
}

void initialize_similarity_matrix() {
  _similarity_matrix = (int**) malloc(_row_numbers * sizeof(int*));
  long i;
  for (i = 0; i < _row_numbers; i++)
    _similarity_matrix[i] = (int*) malloc(_column_numbers * sizeof(int));

  initialize_first_row();
  initialize_first_column();

  long j;
  for (i = 1; i < _row_numbers; i++)
    for (j = 1; j < _column_numbers; j++)
      _similarity_matrix[i][i] = -1;
}

void initialize_first_row() {
  int i;
  for (i = 0; i < _column_numbers; i++)
    _similarity_matrix[0][i] = 0;
}

void initialize_first_column() {
  int i;
  for (i = 0; i < _row_numbers; i++)
    _similarity_matrix[i][0] = 0;
}

int calculate_for_gap_in_polymerase(long row_index, long column_index) {
  return _similarity_matrix[row_index][column_index - 1] - 2;
}

int calculate_for_gap_in_sequence(long row_index, long column_index) {
  return _similarity_matrix[row_index - 1][column_index] - 2;
}

int calculate_for_match_or_mismatch(long row_index, long column_index) {
  if (_polymerase[row_index - 1] == _sequence[column_index - 1] ||
      _polymerase[row_index - 1] == WILD_CARD || _sequence[column_index - 1] == WILD_CARD)
    return _similarity_matrix[row_index - 1][column_index - 1] + 1;

  return _similarity_matrix[row_index - 1][column_index - 1] - 1;
}

int max(int numbers[]) {
  int max = MIN_VALUE;
  int i;
  for (i = 0; i < length(numbers); i++) {
    if (numbers[i] > max)
      max = numbers[i];
  }
  return max;
}

int length(int* arr) {
  int count = 0;
  while (*arr != 0) {
    ++count;
    ++arr;
  }
  return count;
}
