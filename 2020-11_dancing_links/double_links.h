#ifndef DOUBLE_LINKS_
#define DOUBLE_LINKS_

typedef void (*dlNodeFreeFn)(void*);

typedef struct {
  int total_size;
  int used;
} dlInfot;

typedef struct {
  int          llink;
  int          rlink;
  void*        data;  // store user's data or dlInfot in header.
  dlNodeFreeFn free_fn;
} dlNodet;

// prototype
extern dlNodet* dlCreate(int total_size);
extern void     dlFree(dlNodet* h);
extern int      dlCreateNode(dlNodet* h, void* data, dlNodeFreeFn free_fn);
extern void     dlHideNode(dlNodet* h, int node_id);

#endif
