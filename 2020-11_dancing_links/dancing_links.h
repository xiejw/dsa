#ifndef DANCING_LINKS_
#define DANCING_LINKS_

typedef struct {
  int id;
  union {
    int len;
    int top;
  };
  int ulink;
  int dlink;
} dancingNodet;

#endif
