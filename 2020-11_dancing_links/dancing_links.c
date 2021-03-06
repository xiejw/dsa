#include "dancing_links.h"

#include <assert.h>
#include <stdlib.h>

dlTopRowNodet* dlCreateTopRow(int total_size) {
  dlTopRowInfot* ph = malloc(sizeof(dlTopRowInfot));
  ph->total_size    = total_size;
  ph->used          = 0;

  dlTopRowNodet* p = malloc((total_size + 1) * sizeof(dlTopRowNodet));
  p->llink         = 0;
  p->rlink         = 0;
  p->data          = ph;
  p->free_fn       = NULL;
  return p;
}

void dlFreeTopRow(dlTopRowNodet* header) {
  int used = ((dlTopRowInfot*)header->data)->used;

  dlTopRowNodet* node = header + 1;
  for (int i = 1; i <= used; i++) {
    node->free_fn(node->data);
    node++;
  }

  free(header->data);
  free(header);
}

int dlTopRowCreateNode(dlTopRowNodet* header, void* user_data,
                       dlTopRowNodeFreeFn free_fn) {
  dlTopRowInfot* info = header->data;

  int total_size = info->total_size;
  int next_slot  = ++(info->used);
  assert(next_slot <= total_size);

  dlTopRowNodet* p = header + next_slot;
  p->data          = user_data;
  p->free_fn       = free_fn;
  p->vheader       = NULL;

  // linked into the double link;
  int last_node_id               = header->llink;
  (header + last_node_id)->rlink = next_slot;
  p->llink                       = last_node_id;
  p->rlink                       = 0;  // header;
  header->llink                  = next_slot;
  return next_slot;
}

void dlTopRowHideNode(dlTopRowNodet* header, int node_id) {
  dlTopRowNodet* p    = header + node_id;
  int            l    = p->llink;
  int            r    = p->rlink;
  (header + l)->rlink = r;
  (header + r)->llink = l;
}
