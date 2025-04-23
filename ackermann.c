#include <stdint.h>
#include <stdio.h>

uint64_t A(uint64_t x, uint64_t y) {
  if (x == 0)
    return y + 1;
  else if (y == 0)
    return A(x - 1, 1);
  else
    return A(x - 1, A(x, y - 1));
}

int main(void) {
  for (uint64_t x = 0; x <= 4; x++) {
    for (uint64_t y = 0; y <= 10; y++) {
      uint64_t z = A(x, y);
      printf("A(%lu,%lu) = %lu\t", x, y, z);
      fflush(stdout);
    }
    printf("\n");
  }
  return 0;
}
