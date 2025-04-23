#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define Y_CACHE_BITS 20 // 1 MB

uint64_t *ack_cache;

uint64_t A(uint64_t x, uint64_t y) {
  if (x == 0)
    return y + 1;

  assert(y < (1 << Y_CACHE_BITS));
  size_t i = (x << Y_CACHE_BITS) + y;
  if (ack_cache[i] != 0)
    return ack_cache[i];

  uint64_t result;
  if (y == 0)
    result = A(x - 1, 1);
  else
    result = A(x - 1, A(x, y - 1));
  ack_cache[i] = result;

  return result;
}

int main(void) {
  size_t X = 4, Y = 10;

  ack_cache = calloc(1 << (3 + Y_CACHE_BITS), sizeof(uint64_t));

  for (size_t x = 0; x <= X; x++) {
    for (size_t y = 0; y <= Y; y++) {
      uint64_t z = A(x, y);
      printf("A(%lu,%lu) = %lu\t", x, y, z);
      fflush(stdout);
    }
    printf("\n");
  }
  return 0;
}
