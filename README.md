# Check if running in Windows Subsystem for Linux

These examples for [C](./c/), [C++](./cpp), [Fortran](./fortran/), and Python show how to detect if a program is running under Windows Subsystem for Linux (WSL).

There is one header file "is_wsl.h" that works for C and C++ under [include/](./include/).

The Python example has a function "wsl_available()" that checks if WSL is available and working on the computer.

## Build C, C++, Fortran examples

```sh
cmake -Bbuild
cmake --build build
```
