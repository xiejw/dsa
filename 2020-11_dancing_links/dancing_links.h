#ifndef DANCING_LINKS_
#define DANCING_LINKS_

// problem specific.
typedef struct {
  int x, y;  // 0-based coordinate.
  int k;     // 1-based digit.
  int idx;   // k << 8 + x << 4 + y
} optiont;

typedef struct {
  int idx;
} sdkDatat;

// general.

struct dlNodet;
typedef void (*dlTopRowNodeFreeFn)(void*);

typedef struct {
  int total_size;
  int used;
} dlTopRowInfot;

typedef struct {
  int   llink;
  int   rlink;
  void* data;  // store user's data for normal node or dlheadinfot for header.
  dlTopRowNodeFreeFn free_fn;

  struct dlNodet* vheader;
} dlTopRowNodet;

// prototype
extern dlTopRowNodet* dlCreateTopRow(int total_size);
extern void           dlFreeTopRow(dlTopRowNodet* header);
extern dlTopRowNodet* dlTopRowCreateNode(dlTopRowNodet* header, void* user_data,
                                         dlTopRowNodeFreeFn free_fn);

typedef struct dlNodet {
  union {
    int len;
    int top;
  };
  int ulink;
  int dlink;
} dlNodet;

#endif
