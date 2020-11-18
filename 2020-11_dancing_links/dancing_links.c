#include "dancing_links.h"

#include <stdlib.h>

dlheadt* dlCreateHeaderNode(void* user_data, dlHeaderNodeFreeFn free_fn) {
  dlheadt* p = malloc(sizeof(dlheadt));
  p->data    = user_data;
  p->free_fn = free_fn;
  return p;
}

void dlFreeHeaderNode(dlheadt* node) {
  node->free_fn(node->data);
  free(node);
}
