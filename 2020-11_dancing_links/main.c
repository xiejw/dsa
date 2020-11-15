#include <stdio.h>

#include "dancing_links.h"

#define SIZE  9
#define DEBUG 1

// -----------------------------------------------------------------------------
// Prototypes.
// -----------------------------------------------------------------------------
static void printProblem(int* problem);
static void searchOptions(int* problem);

int main() {
  int problem[SIZE * SIZE] = {
      // clang-format off
      0, 0, 3,  0, 1, 0,  0, 0, 0,
      4, 1, 5,  0, 0, 0,  0, 9, 0,
      2, 0, 6,  5, 0, 0,  3, 0, 0,

      5, 0, 0,  0, 8, 0,  0, 0, 9,
      0, 7, 0,  9, 0, 0,  0, 3, 2,
      0, 3, 8,  0, 0, 4,  0, 6, 0,

      0, 0, 0,  2, 6, 0,  4, 0, 3,
      0, 0, 0,  3, 0, 0,  0, 0, 8,
      3, 2, 0,  0, 0, 7,  9, 5, 0,
      // clang-format on
  };

  printProblem(problem);
  searchOptions(problem);
  return 0;
}

// -----------------------------------------------------------------------------
// Helper methods.
// -----------------------------------------------------------------------------

void printProblem(int* problem) {
  // header
  printf("+-----+-----+-----+\n");
  for (int x = 0; x < SIZE; x++) {
    int offset = x * SIZE;
    printf("|");
    for (int y = 0; y < SIZE; y++) {
      int num = problem[offset + y];
      if (num == 0)
        printf(" ");
      else
        printf("%d", problem[offset + y]);

      if ((y + 1) % 3 != 0)
        printf(" ");
      else
        printf("|");
    }
    printf("\n");
    if ((x + 1) % 3 == 0) printf("+-----+-----+-----+\n");
  }
}

#define POS(x, y) ((x)*SIZE + (y))

void searchOptions(int* problem) {
  int total = 0;
  if (DEBUG) printf("total 10 options:\n");

  for (int x = 0; x < SIZE; x++) {
    int offset = x * SIZE;

    for (int y = 0; y < SIZE; y++) {
      if (problem[offset + y] > 0) continue;  // prefilled.

      int box_x = (x / 3) * 3;
      int box_y = (y / 3) * 3;

      for (int k = 1; k <= SIZE; k++) {
        // search row
        for (int j = 0; j < SIZE; j++) {
          if (problem[j + offset] == k) {
            goto not_a_option;
          }
        }
        // search column
        for (int j = 0; j < SIZE; j++) {
          if (problem[POS(j, y)] == k) {
            goto not_a_option;
          }
        }

        // search box. static unroll
        if (problem[POS(box_x, box_y)] == k ||
            problem[POS(box_x, box_y + 1)] == k ||
            problem[POS(box_x, box_y + 2)] == k ||
            problem[POS(box_x + 1, box_y)] == k ||
            problem[POS(box_x + 1, box_y + 1)] == k ||
            problem[POS(box_x + 1, box_y + 2)] == k ||
            problem[POS(box_x + 2, box_y)] == k ||
            problem[POS(box_x + 2, box_y + 1)] == k ||
            problem[POS(box_x + 2, box_y + 2)] == k) {
          goto not_a_option;
        }

        total++;
        if (DEBUG && total < 10) {
          printf("  x %d, y %d, k %d\n", x, y, k);
        }
      not_a_option:
        (void)0;
      }
    }
  }
  if (DEBUG) printf("in total %d options\n", total);
}
