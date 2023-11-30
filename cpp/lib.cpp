#include <string>

#if __has_include(<sys/utsname.h>)
#include <sys/utsname.h>
#endif

#ifdef DEBUG
#include <iostream>
#endif

extern "C" bool is_wsl() {

#if __has_include(<sys/utsname.h>)
  struct utsname buf;
  if (uname(&buf) != 0)
    return false;

  std::string sysname(buf.sysname);
  std::string release(buf.release);

#ifdef DEBUG
  std::cout << "sysname: " << sysname << "   release: " << release << "\n";
#endif

  return sysname == "Linux" &&
   (release.ends_with("microsoft-standard-WSL") ||
    release.ends_with("-Microsoft")); // WSLv1


#else
  return false;
#endif
}
