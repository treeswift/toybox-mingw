/* Toybox infrastructure.
 *
 * Copyright 2006 Rob Landley <rob@landley.net>
 */

// Stuff that needs to go before the standard headers
#ifndef _TOYS_H_
#define _TOYS_H_

#include "generated/config.h"
#include "lib/portability.h"

// General posix-2008 headers
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <grp.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <paths.h>
#include <pwd.h>
/* portability.h includes regex... or its replacement */
#include <sched.h>
#include <setjmp.h>
#define sigjmp_buf jmp_buf /* ad hoc. must break a lot */
#define siglongjmp longjmp /* -"- "*/
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
/* Windows */
#include <io.h>
typedef int(*mkdir_mswin)(const char*);
const mkdir_mswin mkdir_prime = &mkdir;
#define mkdir mkdir_chmod
int mkdir(const char* path, mode_t mode);
#define random rand
#define srandom srand

/* missing declarations (normally provided in stdlib.h) */
inline int setenv(const char *name, const char *value, int overwrite) { return 0; }
inline int unsetenv(const char *name) { return 0; }
char *getenv(const char *name); /* stub or implement? */

#include <string.h>
#ifdef PROVIDE_MGW_STR
char* stpcpy(char* dest, const char* src);
char* strndup(const char *src, size_t atmost);
char *strcasestr(const char *haystack, const char *needle);
void *memmem(const void *haystack, size_t haystack_sz, const void *needle, size_t needle_sz);
#endif
#include <strings.h>
#include <sys/mman.h>
#ifndef _SC_PAGESIZE
#include "memmap/proc.h"
#define sysconf memmap_sysconf
#endif
#ifdef PROVIDE_RESOURCE_H
#include "sys_resource.h"
#else
#include <sys/resource.h>
#endif
#include <sys/stat.h>
#ifndef DISABLE_STATVFS_H
#include <sys/statvfs.h>
#else
struct statvfs {};
#endif
#include <sys/time.h>
#ifndef DISABLE_TIMES_H
#include <sys/times.h>
#endif
// #include <sys/utsname.h> // figure out later
/// #include <sys/wait.h> // rly?
#include "syslog.h" // stub it!
#ifndef DISABLE_TERMINAL
#include <termios.h>
#else
struct termios {};
#endif

#include <time.h>
#include <unistd.h>
#include <utime.h>

// Posix networking

#include <arpa/inet.h>
// #include <netdb.h> // ws2fwd?
// #include <net/if.h> // ws2fwd?
#include <netinet/in.h>
// #include <netinet/tcp.h> //-"-
// #include <poll.h> // ?
#include <sys/socket.h>
// #include <sys/un.h> // ?
#define hstrerror(no) (DWORD)(no)

/* the below should be provided by unistd.h, what the...? */
#ifndef SHUT_RD
#define SHUT_RD SD_RECEIVE
#endif
#ifndef SHUT_WR
#define SHUT_WR SD_SEND
#endif
#ifndef SHUT_RDWR
#define SHUT_RDWR SD_BOTH
#endif

// Internationalization support (also in POSIX)

#ifndef DISABLE_LOCALE
// #include <langinfo.h> // provide, don't use plibc's
#endif
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

// Non-posix headers
// #include <sys/ioctl.h> // figure out later
inline int ioctl(int fd, unsigned long request, ...) { return 0; }
// TODO enumerate ioctls
// #include <sys/syscall.h> // figure out later
long syscall(long number, ...) { return 0; }
// TODO enumerate syscalls

#include "lib/lib.h"
#include "lib/lsm.h"
#include "lib/toyflags.h"

/* contaminated above */
#ifdef interface
#undef interface
#endif

/* libmoregw headers */
#include <fatctl/full.h>
#include <wusers/wuser_eugid.h>
inline int setsid() { return getpid(); }
inline int setuid(uid_t uid) { return 0; }
inline int setgid(gid_t gid) { return 0; }

// FIXME implement [f]chown in libowners
inline int chown(const char* path, uid_t owner, gid_t group) { return 0; }
inline int lchown(const char* path, uid_t owner, gid_t group) { return 0; }
inline int fchown(int fd, uid_t owner, gid_t group) { return 0; }
inline int fchownat(int dirfd, const char* relpath, uid_t owner, gid_t group) { return 0; }

/* silverware */
inline int vfork() { return -1; }
// TODO fork()

/* start of waitpid constants */
#define WIFEXITED(status)   0
#define WEXITSTATUS(status) 0
#define WTERMSIG(status) SIGINT
/* end of waitpid constants */
inline pid_t waitpid(pid_t pid, int *wstatus, int options) { return -1; }
inline int pipe(int pipefd[2]) { return _pipe(pipefd, 4096, _O_BINARY); }
inline int kill(pid_t pid, int sig) { return errno = ENOSYS, -1; } // TODO TerminateThread

/* strptime library */
#include "libob/strptime.h"

// TODO expose a convenient "at" macro in libfatctl
inline int utimens(const char* pathname, const struct timespec times[2]) { return 0; }
inline int futimens(int fd, const struct timespec times[2]) { return 0; }
inline int utimensat(int dirfd, const char* relpath, const struct timespec times[2], int flags) { return 0; }

/* getline-compatible */
#include <getline/getline.h>

int chroot(const char* path);

// Get list of function prototypes for all enabled command_main() functions.

#define NEWTOY(name, opts, flags) void name##_main(void) __attribute((weak));
#define OLDTOY(name, oldname, flags) void oldname##_main(void) __attribute((weak));
#include "generated/newtoys.h"
#include "generated/flags.h"
#include "generated/globals.h"
#include "generated/tags.h"

// These live in main.c

#define HELP_USAGE   1  // usage: line only
#define HELP_HEADER  2  // Add Toybox header line to help output
#define HELP_SEE     4  // "See COMMAND" instead of dereferencing alias
#define HELP_HTML    8  // Output HTML

struct toy_list *toy_find(char *name);
void show_help(FILE *out, int full);
void check_help(char **arg);
void toy_singleinit(struct toy_list *which, char *argv[]);
void toy_init(struct toy_list *which, char *argv[]);
void toy_exec(char *argv[]);

// Array of available commands

extern struct toy_list {
  char *name;
  void (*toy_main)(void);
  char *options;
  unsigned flags;
} toy_list[];

// Global context shared by all commands.

extern struct toy_context {
  struct toy_list *which;  // Which entry in toy_list is this one?
  char **argv;             // Original command line arguments
  char **optargs;          // Arguments left over from get_optflags()
  unsigned long long optflags; // Command line option flags from get_optflags()
  int optc;                // Count of optargs
  short toycount;          // Total number of commands in this build
  char exitval;            // Value error_exit feeds to exit()
  char wasroot;            // dropped setuid

  // toy_init() should not zero past here.
  sigjmp_buf *rebound;     // siglongjmp here instead of exit when do_rebound
  struct arg_list *xexit;  // atexit() functions for xexit(), set by sigatexit()
  void *stacktop;          // nested toy_exec() call count, or 0 if vforked
  int envc;                // Count of original environ entries
  int old_umask;           // Old umask preserved by TOYFLAG_UMASK
  short signal;            // generic_signal() records what signal it saw here
  int signalfd;            // and writes signal to this fd, if set
} toys;

// Two big temporary buffers: one for use by commands, one for library functions

_CRTIMP extern char **environ;
extern char *toybox_version, toybuf[4096], libbuf[4096];

#define FLAG(x) (!!(toys.optflags&FLAG_##x))  // Return 1 if flag set, 0 if not

#define GLOBALS(...)
#define ARRAY_LEN(array) (sizeof(array)/sizeof(*array))
#define TAGGED_ARRAY(X, ...) {__VA_ARGS__}

#ifndef TOYBOX_VERSION
#ifndef TOYBOX_VENDOR
#define TOYBOX_VENDOR ""
#endif
#define TOYBOX_VERSION "0.8.10"TOYBOX_VENDOR
#endif

#endif