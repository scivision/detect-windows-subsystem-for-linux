# Check if running in Windows Subsystem for Linux

[![cmake](https://github.com/scivision/detect-windows-subsystem-for-linux/actions/workflows/cmake.yml/badge.svg)](https://github.com/scivision/detect-windows-subsystem-for-linux/actions/workflows/cmake.yml)

These examples for [C](./c/), [C++](./cpp), [Fortran](./fortran/), and Python show how to detect if a program is running under Windows Subsystem for Linux (WSL).

There is one header file "is_wsl.h" that works for C and C++ under [include/](./include/).

The Python example has a function "wsl_available()" that checks if WSL is available and working on the computer.

## Build C, C++, Fortran examples

```sh
cmake -Bbuild
cmake --build build
```

Optionally, run the examples:

```sh
ctest --test-dir build
```

## Heuristic

The method is to check the kernel name string to see if it contains:

* "-Microsoft " (WSLv1)
* "microsoft-standard-WSL" (WSLv2)

## Human check

Manually see relevant info:

```pwsh
# from Windows PowerShell or Command Prompt
wsl.exe -l -v
```

from WSL Terminal:

```sh
uname -a
```

## CI Notes

Our [GitHub Workflow](.github/workflows/cmake.yml)
gives an example of WSLv1 on GitHub Actions.

There is
[not currently a way](https://github.com/actions/runner-images/issues/5760)
to run WSLv2 directly on GitHub Actions or AppVeyor.
One can run
[WSLv2 in CI using an image](https://github.com/ubuntu/wsl-actions-example/blob/main/.github/workflows/test_wsl.yaml)
or a custom
[GitHub Action](https://github.com/Vampire/setup-wsl).
