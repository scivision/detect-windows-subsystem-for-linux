#include "is_wsl.h"

#include <iostream>

int main() {
  bool wsl = is_wsl();
  std::cout << "WSL: " << wsl << "\n";
  return 0;
}
