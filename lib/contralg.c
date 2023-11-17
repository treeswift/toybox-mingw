/**
 * Ad-hoc additions to Toybox for x-compilation with MinGW.
 * This file provides simple, OS-unaware algorithms.
 * Public domain.
 */

#include "toys.h"

#ifdef PROVIDE_MGW_STR

char* stpcpy(char* dest, const char* src) {
  const size_t len = strlen(src);
  return strcpy(dest, src) + len;
}

char* strndup(const char *src, size_t atmost) {
  char* trg = malloc(atmost + 1); // '\0'
  if(trg) {
    strncpy(trg, src, atmost);
  }
  return trg;
}

/**
 * The below implementations are O(Nsz*Hsz), which is good enough for tiny needles and medium-sized haystacks.
 * They follow the "simple implementation first" principle of ToyBox.
 */

char *strcasestr(const char *haystack, const char *needle) {
  while(*haystack) {
    if(!strcasecmp(haystack, needle)) {
      return haystack;
    }
    ++haystack;
  }
  return (char*)0;
}

void *memmem(const void *haystack, size_t haystack_sz, const void *needle, size_t needle_sz) {
  if(needle_sz <= haystack_sz) {
    const char* chay_stack = (const char*)haystack;
    const char* cend_stack = chay_stack + haystack_sz - needle_sz;
    do{
      if(!memcmp(chay_stack, needle, needle_sz)) {
        return chay_stack;
      }
    }
    while(chay_stack++ != cend_stack);
  }
  return NULL;
}

#endif // PROVIDE_MGW_STR
