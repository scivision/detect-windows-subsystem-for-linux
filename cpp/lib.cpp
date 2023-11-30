#include <string>

#if __has_include(<sys/utsname.h>)
#include <sys/utsname.h>
#endif

extern "C" bool is_wsl() {

#if __has_include(<sys/utsname.h>)
  struct utsname buf;
  if (uname(&buf) != 0)
    return false;

  std::string sysname(buf.sysname);
  std::string release(buf.release);

  return sysname == "Linux" &&
#ifdef __cpp_lib_string_contains
  (release.contains("microsoft-standard-WSL") ||
    release.contains("-Microsoft ")); // WSLv1
#else
  (release.find("microsoft-standard-WSL") != std::string::npos ||
    release.find("-Microsoft ") != std::string::npos); // WSLv1
#endif

#else
  return false;
#endif
}
