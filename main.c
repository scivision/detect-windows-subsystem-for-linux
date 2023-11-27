#include "is_wsl.h"

#include <stdio.h>

int main(void) {
  printf("WSL: %d\n", is_wsl());
  return 0;
}
