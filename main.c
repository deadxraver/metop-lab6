#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RAND_SEED time(NULL)
#define POPULATION_SIZE 5   /* длина маршрута */
#define POPULATION_NUMBER 4 /* количество маршрутов */
#define ITERATIONS 1
#define MUTATION_PROB 0.01 /* вероятность мутации */

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

static size_t* copy(size_t* arr, size_t sz) {
  size_t* new_arr = (size_t*)malloc(sizeof(size_t) * sz);
  for (size_t i = 0; i < sz; ++i) {
    i[new_arr] = i[arr];
  }
  return new_arr;
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
      free_or_taken[temp] = 1;
      population[i] = temp + 1;
    }
  }
  return population;
}

static void print_route(size_t* route, size_t sz, size_t first_index, size_t second_index) {
  for (size_t i = 0; i < sz; ++i) {
    if (i + 1 == first_index) {
      printf("|");
    }
    printf("%zu", i[route]);
    if (i + 1 == second_index) {
      printf("|");
    } else
      printf(" ");
  }
  printf("\n");
}

int main() {
  srand(RAND_SEED);
  size_t* routes[POPULATION_NUMBER];
  printf("Начальные маршруты:\n");
  for (size_t i = 0; i < POPULATION_NUMBER; ++i) {
    routes[i] = generate_route();
    print_route(routes[i], POPULATION_SIZE, 0, 0);
  }
  for (size_t i = 0; i < ITERATIONS; ++i) {
    size_t first_row = (size_t)(random() % POPULATION_NUMBER);
    size_t second_row = first_row;
    while (first_row == second_row) {
      second_row = (size_t)(random() % POPULATION_NUMBER);
    }
    size_t third_row = (size_t)(random() % POPULATION_NUMBER);
    size_t fourth_row = third_row;
    while (third_row == fourth_row) {
      fourth_row = (size_t)(random() % POPULATION_NUMBER);
    }
    printf(
        "%zu. Скрещиваем (%zu) & (%zu) и (%zu) & (%zu):\n",
        i + 1,
        first_row + 1,
        second_row + 1,
        third_row + 1,
        fourth_row + 1
    );
    // тут генерируем детей от первой пары
    size_t first_index = (size_t)(random() % (POPULATION_SIZE - 1) + 1);
    size_t second_index = (size_t)(random() % (POPULATION_SIZE - first_index) + first_index);
    print_route(routes[first_row], POPULATION_SIZE, first_index, second_index);
    print_route(routes[second_row], POPULATION_SIZE, first_index, second_index);
    size_t* new_first = copy(routes[first_row], POPULATION_SIZE);
    size_t* new_second = copy(routes[second_row], POPULATION_SIZE);
    replace_section(new_first, new_second, first_index, second_index);
    // а тут от второй пары
    size_t third_index = (size_t)(random() % (POPULATION_SIZE - 1) + 1);
    size_t fourth_index = (size_t)(random() % (POPULATION_SIZE - third_index) + third_index);
    print_route(routes[third_row], POPULATION_SIZE, third_index, fourth_index);
    print_route(routes[fourth_row], POPULATION_SIZE, third_index, fourth_index);
    size_t* new_third = copy(routes[third_row], POPULATION_SIZE);
    size_t* new_fourth = copy(routes[fourth_row], POPULATION_SIZE);
    replace_section(new_third, new_fourth, third_index, fourth_index);
    for (size_t j = 0; j < POPULATION_NUMBER; ++j) {
      // чистим маршруты, они будут заменены на новые
      free(j[routes]);
    }
    printf("Полученные маршруты:\n");
  }
  // free everything
  for (size_t i = 0; i < POPULATION_NUMBER; ++i) {
    free(routes[i]);
  }
  return 0;
}
