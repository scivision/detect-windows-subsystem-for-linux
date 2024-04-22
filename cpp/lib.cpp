#include <string>

#if __has_include(<sys/utsname.h>)
#include <sys/utsname.h>
#endif

#ifdef DEBUG
#include <iostream>
#endif

#include "is_wsl.h"


int is_wsl() {

#if __has_include(<sys/utsname.h>)
  struct utsname buf;
  if (uname(&buf) != 0)
    return -1;

  std::string_view sysname(buf.sysname);
  std::string_view release(buf.release);

#ifdef DEBUG
  std::cout << "sysname: " << sysname << "   release: " << release << "   machine: " << buf.machine << "\n";
#endif

  if (sysname != "Linux")
    return 0;

#ifdef __cpp_lib_starts_ends_with
  if (release.ends_with("microsoft-standard-WSL2"))
    return 2;
  if (release.ends_with("-Microsoft"))
    return 1;
#else
  if (release.find("microsoft-standard-WSL2") != std::string::npos)
    return 2;
  if (release.find("-Microsoft") != std::string::npos)
    return 1;
#endif

  return 0;
#endif

  return -1;
}
