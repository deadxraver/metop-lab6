#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_SEED time(NULL)
#define POPULATION_SIZE 5

static size_t matrix[5][5] = {
    {0,  2,  7, 2, 8},
    {2,  0, 10, 3, 1},
    {7, 10,  0, 2, 6},
    {2,  3,  2, 0, 4},
    {8,  1,  6, 4, 0}
};

static void replace_section(size_t* row1, size_t* row2, size_t start, size_t finish) {
  for (size_t i = start; i <= finish; ++i) {
    int temp = i[row1];
    i[row1] = i[row2];
    i[row2] = temp;
  }
}

static int count_route_length(size_t* route, size_t length) {
  int result = matrix[route[0]][route[length - 1]];
  for (size_t i = 0; i < length - 1; ++i) {
    result += matrix[route[i]][route[i + 1]];
  }
  return result;
}

static size_t* generate_route() {
  bool free_or_taken[POPULATION_SIZE] = {0};
  size_t* population = (size_t*)malloc(sizeof(size_t) * POPULATION_SIZE);
  for (size_t i = 0; i < POPULATION_SIZE; ++i) {
    size_t temp = (size_t)(random() % POPULATION_SIZE);
    if (free_or_taken[temp])
      --i;
    else {
      free_or_taken[i] = 1;
      population[i] = temp + 1;
    }
  }
  return population;
}

static void print_route(size_t* route, size_t sz, size_t first_index, size_t second_index) {
  for (size_t i = 0; i < sz; ++i) {
    bool printed_sth = 0;
    if (i + 1 == first_index) {
      printf("|");
      printed_sth = 1;
    }
    printf("%zu", i[route]);
    if (i + 1 == second_index) {
      printf("|");
      printed_sth = 1;
    }
    if (!printed_sth)
      printf(" ");
  }
}

int main() {
  srand(RAND_SEED);
  return 0;
}
