#include "double_links.h"

#include <assert.h>
#include <stdlib.h>

static inline dlInfot* dlInfoNode(dlNodet* h) { return ((dlInfot*)h->data); }

dlNodet* dlCreate(int total_size) {
  dlInfot* info    = malloc(sizeof(dlInfot));
  info->total_size = total_size;
  info->used       = 0;

  dlNodet* p = malloc((total_size + 1) * sizeof(dlNodet));
  p->llink   = 0;
  p->rlink   = 0;
  p->data    = info;
  p->free_fn = NULL;
  return p;
}

void dlFree(dlNodet* h) {
  int used = dlInfoNode(h)->used;

  dlNodet* node = h + 1;
  for (int i = 1; i <= used; i++) {
    node->free_fn(node->data);
    node++;
  }

  free(h->data);  // info node in header.
  free(h);
}

int dlCreateNode(dlNodet* h, void* user_data, dlNodeFreeFn free_fn) {
  dlInfot* info       = dlInfoNode(h);
  int      total_size = info->total_size;
  int      next_slot  = ++(info->used);
  assert(next_slot <= total_size);

  dlNodet* p = h + next_slot;
  p->data    = user_data;
  p->free_fn = free_fn;

  // linked into the double link;
  int last_node_id          = h->llink;
  (h + last_node_id)->rlink = next_slot;
  p->llink                  = last_node_id;
  p->rlink                  = 0;  // header index
  h->llink                  = next_slot;
  return next_slot;
}

void dlHideNode(dlNodet* h, int node_id) {
  dlNodet* p     = h + node_id;
  int      l     = p->llink;
  int      r     = p->rlink;
  (h + l)->rlink = r;
  (h + r)->llink = l;
}
