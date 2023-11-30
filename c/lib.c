#include "is_wsl.h"

#include <string.h>

#ifdef DEBUG
#include <stdio.h>  // printf
#endif

#ifdef HAVE_UTSNAME_H
#include <sys/utsname.h>
#endif

static bool str_ends_with(const char *s, const char *suffix) {
  /* https://stackoverflow.com/a/41652727 */
    size_t slen = strlen(s);
    size_t suffix_len = strlen(suffix);

    return suffix_len <= slen && !strcmp(s + slen - suffix_len, suffix);
}

bool is_wsl(void) {
#ifdef HAVE_UTSNAME_H
  struct utsname buf;
  if (uname(&buf) != 0)
    return false;

#ifdef DEBUG
    printf("sysname: %s   release: %s \n", buf.sysname, buf.release);
#endif

  return strcmp(buf.sysname, "Linux") == 0 &&
    (str_ends_with(buf.release, "microsoft-standard-WSL") ||
     str_ends_with(buf.release, "-Microsoft"));
#else
  return false;
#endif
}
