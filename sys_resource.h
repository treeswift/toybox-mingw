#ifndef _SYS_RESOURCE_H_
#define _SYS_RESOURCE_H_

#include <stdint.h>

/* __BEGIN_DECLS */
#ifdef __cplusplus
extern "C" {
#endif

#define PRIO_MIN        (-20)
#define PRIO_MAX        20

#define PRIO_PROCESS    0
#define PRIO_PGRP       1
#define PRIO_USER       2

#define RLIMIT_CPU      0               /* cpu time in milliseconds */
#define RLIMIT_FSIZE    1               /* maximum file size */
#define RLIMIT_DATA     2               /* data size */
#define RLIMIT_STACK    3               /* stack size */
#define RLIMIT_CORE     4               /* core file size */
#define RLIMIT_RSS      5               /* resident set size */
#define RLIMIT_MEMLOCK  6               /* locked-in-memory address space */
#define RLIMIT_NPROC    7               /* number of processes */
#define RLIMIT_NOFILE   8               /* number of open files */

#define RLIM_NLIMITS    9               /* number of resource limits */

typedef int id_t;

typedef uint64_t rlim_t;

struct rlimit {
    rlim_t  rlim_cur, rlim_max;
};

#define RLIM_INFINITY   (((rlim_t)1 << 63) - 1)

inline int getpriority(int pid, id_t who) {
    return PRIO_PROCESS;
}
inline int getrlimit(int uid, struct rlimit * lim) {
    return lim->rlim_cur = lim->rlim_max = RLIM_INFINITY, 0;
}

/* int getrusage(int uid, struct rusage *); */

inline int setpriority(int pid, id_t who, int prio) {
    return 0; /* success */
}
inline int setrlimit(int uid, const struct rlimit * lim) {
    return 0; /* success */
}

/* __END_DECLS */
#ifdef __cplusplus
}
#endif

#endif