/**
 * Ad-hoc additions to Toybox for x-compilation with MinGW.
 * This file provides simple, OS-unaware algorithms.
 * Public domain.
 */

#include "toys.h"

#ifdef PROVIDE_MGW_SYS

#include <windows.h>

int mkdir(const char* path, mode_t mode) {
  return -((*mkdir_prime)(path) || chmod(path, mode));
}

/* TODO getppid -> silverware */

/* FIXME there is an elegant Windows hack */
/* MOREINFO candidate for libsysroot? */
int chroot(const char* path) { return -1; }

#endif // PROVIDE_MGW_SYS
