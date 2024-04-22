#include "is_wsl.h"

#include <string.h>
#include <stdbool.h>

#ifndef __has_include
#define __has_include(x) 0
#endif

#if __has_include(<sys/utsname.h>)
#include <sys/utsname.h>
#endif


static bool str_ends_with(const char *s, const char *suffix) {
  /* https://stackoverflow.com/a/41652727 */
    size_t slen = strlen(s);
    size_t suffix_len = strlen(suffix);

    return suffix_len <= slen && !strcmp(s + slen - suffix_len, suffix);
}


int is_wsl(void) {

#if __has_include(<sys/utsname.h>)
  struct utsname buf;
  if (uname(&buf) != 0)
    return 0;

  if (strcmp(buf.sysname, "Linux") != 0)
    return 0;
  if (str_ends_with(buf.release, "microsoft-standard-WSL2"))
    return 2;
  if (str_ends_with(buf.release, "-Microsoft"))
    return 1;
#endif

  return -1;
}
