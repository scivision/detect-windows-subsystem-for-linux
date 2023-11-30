#include "is_wsl.h"

#include <stdio.h>

int main(void) {
  int wsl = is_wsl();
  printf("WSL: %d\n", wsl);
  return 0;
}
