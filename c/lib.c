#include "is_wsl.h"

#include <string.h>

#ifdef HAVE_UTSNAME_H
#include <sys/utsname.h>
#endif


bool is_wsl(void) {
#ifdef HAVE_UTSNAME_H
  struct utsname buf;
  if (uname(&buf) != 0)
    return false;

  return strcmp(buf.sysname, "Linux") == 0 &&
    (strstr(buf.release, "microsoft-standard-WSL") != NULL ||
     strstr(buf.release, "-Microsoft ") != NULL);
#else
  return false;
#endif
}
