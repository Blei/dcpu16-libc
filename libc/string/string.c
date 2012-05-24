#include <stddef.h>
#include <string.h>

void *memset(void *dst, int pat, size_t n) {
  int *dst2 = (int*) dst;
  size_t i;
  for (i = 0; i < n; ++i) {
    dst2[i] = pat;
  }
  return dst;
}

size_t strlen(const char *str) {
  size_t n = 0;
  while (*str != '\0') {
    ++n;
    ++str;
  }
  return n;
}
