#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "dancing_links.h"
#include "double_links.h"

#define SIZE  9
#define DEBUG 1

// -----------------------------------------------------------------------------
// Prototypes.
// -----------------------------------------------------------------------------
static void printProblem(int* problem);
static int  searchOptions(int* problem);
static void getItemId(int i, int j, int k, int* p, int* r, int* c, int* b);
// static void debugDoubleLinks();
//
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
  int options_count = searchOptions(problem);

  {
    dlNodet* top_row = dlCreate(4 * SIZE * SIZE);
    for (int i = 0; i < 4 * SIZE * SIZE; i++) {
      dlCreateNode(top_row, NULL, NULL);
    }

    // hides all items in table already.
    int hidden_items_count = 0;
    int p, r, c, b;
    for (int x = 0; x < SIZE; x++) {
      int offset = x * SIZE;
      for (int y = 0; y < SIZE; y++) {
        int k = problem[offset + y];
        if (k == 0) continue;

        getItemId(x, y, k, &p, &r, &c, &b);
        dlHideNode(top_row, p);
        dlHideNode(top_row, r);
        dlHideNode(top_row, c);
        dlHideNode(top_row, b);
        hidden_items_count += 4;
      }
    }

    int item_count = 4 * SIZE * SIZE - hidden_items_count;

    if (DEBUG) {
      int count = 0;
      p         = 0;
      while (1) {
        p = (top_row + p)->rlink;
        if (p == 0) {
          break;
        }
        count++;
      }
      assert(item_count == count);
      printf("total items before searching: %d\n", count);
    }

    // header
    // all items
    // first spacer
    // 1 spacers + 4 items for each option.
    dancingNodet* opt_row =
        malloc((1 + item_count + 1 + ((1 + 4) * options_count)) *
               sizeof(dancingNodet));
    int opt_count = 0;

    opt_row[0].id = 0;  // unused.
    opt_count++;

    {
      p = 0;
      while (1) {
        p = (top_row + p)->rlink;
        if (p == 0) {
          break;
        }
        int opt_id          = opt_count;  // 1-based.
        top_row[p].id       = opt_id;
        dancingNodet* opt_p = opt_row + opt_id;
        opt_p->len          = 0;
        opt_p->id           = opt_id;  // self
        opt_p->ulink        = opt_id;  // self
        opt_p->dlink        = opt_id;  // self
        opt_count++;
      }
    }

    // first spacer.

    int spacer_count   = 0;
    int last_spacer_id = opt_count;

    {
      // ulink unused, rlink will be set later.
      dancingNodet* opt_p = opt_row + last_spacer_id;
      opt_p->id           = last_spacer_id;
      opt_p->top          = 0;
      opt_count++;
      spacer_count++;
    }

    free(opt_row);
    dlFree(top_row);
  }

  // debugDoubleLinks();

  return 0;
}

// -----------------------------------------------------------------------------
// Helper methods.
// -----------------------------------------------------------------------------

// Prints the Soduku Problem on screen.
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

// Seach all options that on (x,y) the digit k is allowed to be put there.
int searchOptions(int* problem) {
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
  return total;
}

// p{i,j}, r{i,k} c{j,k} b{x,k}  x=3 * floor(i/3) + floor(j/3)
//
// 1-based
void getItemId(int i, int j, int k, int* p, int* r, int* c, int* b) {
  int x      = 3 * (i / 3) + (j / 3);
  int offset = 0;

  k = k - 1;  // k is 1 based.

  *p = i * SIZE + j + offset + 1;  // item id is 1 based.
  offset += SIZE * SIZE;

  *r = i * SIZE + k + offset + 1;  // item id is 1 based.
  offset += SIZE * SIZE;

  *c = j * SIZE + k + offset + 1;  // item id is 1 based.
  offset += SIZE * SIZE;

  *b = x * SIZE + k + offset + 1;  // item id is 1 based.
}

// Debugging only
void debugDoubleLinks() {
  dlNodet* h = dlCreate(8);

#define PRINT_HEADER(h) printf("header l %d r %d\n", h->llink, h->rlink)
#define PRINT_NODE(h, id)                                             \
  printf("%6d l %d r %d  %s\n", id, (h + id)->llink, (h + id)->rlink, \
         (h + id)->data);

  int id1 = dlCreateNode(h, "a", DL_NO_FREE);
  assert(id1 == 1);
  PRINT_HEADER(h);
  PRINT_NODE(h, 1);

  int id2 = dlCreateNode(h, "b", DL_NO_FREE);
  assert(id2 == 2);
  PRINT_HEADER(h);
  PRINT_NODE(h, 1);
  PRINT_NODE(h, 2);

  int id3 = dlCreateNode(h, "c", DL_NO_FREE);
  assert(id3 == 3);
  PRINT_HEADER(h);
  PRINT_NODE(h, 1);
  PRINT_NODE(h, 2);
  PRINT_NODE(h, 3);

  dlHideNode(h, 2);
  PRINT_HEADER(h);
  PRINT_NODE(h, 1);
  PRINT_NODE(h, 2);
  PRINT_NODE(h, 3);

  dlFree(h);
}
