#ifndef DANCING_LINKS_
#define DANCING_LINKS_

// problem specific.
typedef struct {
  int x, y, k;
  int idx;  // k << 8 + x << 4 + y
} option;

typedef struct {
  int idx;
} sdk_data;

struct dlnodet;

typedef void (*dlHeaderNodeFreeFn)(void*);

// general.
typedef struct {
  int                llink;
  int                rlink;
  void*              data;
  dlHeaderNodeFreeFn free_fn;

  struct dlnodet* vheader;
} dlheadt;

// prototype
extern dlheadt* dlCreateHeaderNode(void* user_data, dlHeaderNodeFreeFn free_fn);
extern void     dlFreeHeaderNode(dlheadt* node);

typedef struct dlnodet {
  union {
    int len;
    int top;
  };
  int ulink;
  int dlink;
} dlnodet;

#endif
