#include <stdint.h>
#include <stdlib.h>

void add(uint32_t* res, uint32_t const* a, uint32_t const* b, size_t n) {
  for (size_t i= 0; i < n; ++i) {
    res[i] = a[i] + b[i];
  }
}
