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

  return sysname == "Linux" && release.contains("microsoft-standard-WSL");
#else
  return false;
#endif
}
