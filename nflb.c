#define _GNU_SOURCE
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/* pointer to intercepted function */
static int (*real_open64)(const char *pathname, int flags, ...) = NULL;
FILE* logfile;

/* function executed when the .so is loaded */
static void _nflb_init() __attribute__((constructor));
void _nflb_init() {
  real_open64 = dlsym(RTLD_NEXT, "open64");

  char* filename = getenv("NFLB_FILE");
  if (filename != NULL) {
    logfile = fdopen(real_open64(filename, O_WRONLY|O_SYNC), "w");
  } else {
    logfile = stdout;
  }
}

/* append created files to the list */
int open64(const char *pathname, int flags, ...) {
  va_list args;
  va_start(args, flags);

  mode_t mode = va_arg(args, mode_t);

  if (flags & O_CREAT) {
    fprintf(logfile, "%s\n", pathname);
  }

  real_open64(pathname, flags, mode);
  va_end(args);
}

/* EOF */
