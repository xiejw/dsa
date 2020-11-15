#ifndef DANCING_LINKS_
#define DANCING_LINKS_

// problem specific.
typedef struct {
  int x, y, k;
} option;

// general.
typedef struct {
  union {
    int len;
    int top;
  };
  int llink;
  int rlink;
  int ulink;
  int dlink;
} dlnodet;

#endif
