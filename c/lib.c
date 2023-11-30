#include "is_wsl.h"

#include <string.h>

#ifdef DEBUG
#include <stdio.h>  // printf
#endif

#ifdef HAVE_UTSNAME_H
#include <sys/utsname.h>
#endif


bool is_wsl(void) {
#ifdef HAVE_UTSNAME_H
  struct utsname buf;
  if (uname(&buf) != 0)
    return false;

#ifdef DEBUG
    printf("sysname: %s   release: %s \n", buf.sysname, buf.release);
#endif

  return strcmp(buf.sysname, "Linux") == 0 &&
    (strstr(buf.release, "microsoft-standard-WSL") != NULL ||
     strstr(buf.release, "-Microsoft ") != NULL);
#else
  return false;
#endif
}
