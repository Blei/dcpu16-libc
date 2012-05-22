#include <stddef.h>
extern void *memset(void *dst, int pat, size_t n) {
  int *dst2 = (int*) dst;
  size_t i;
  for (i = 0; i < n; ++i) {
    dst2[i] = pat;
  }
  return dst;
}
