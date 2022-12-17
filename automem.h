#ifndef AUTOMEM_H
#define AUTOMEM_H

#include <stddef.h>

void *malloc_secure(size_t byte);
void *calloc_secure(size_t byte);
void *reaalloc_secure(size_t byte);
void *creaalloc_secure(size_t byte);
void free_secure(void *p);
void memclear();
#endif

#ifndef SECURE_MODE_OFF
#define malloc malloc_secure
#define calloc calloc_secure
#define realloc realloc_secure
#define free free_secure
#endif


