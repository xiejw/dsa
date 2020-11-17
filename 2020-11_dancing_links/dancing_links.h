#ifndef DANCING_LINKS_
#define DANCING_LINKS_

// problem specific.
typedef struct {
  int x, y, k;
} option;

struct dlnodet;

// general.
typedef struct {
  int             llink;
  int             rlink;
  struct dlnodet* vheader;
} headt;

typedef struct dlnodet {
  union {
    int len;
    int top;
  };
  int ulink;
  int dlink;
} dlnodet;

#endif
