#ifndef  MEM_H_
#define  MEM_H_

extern void *smalloc(size_t size);
extern void *make_shared_mem(size_t size);
extern void *Malloc(size_t size);
extern void *Realloc(void *ptr, size_t size);
extern void *Calloc(size_t nmemb, size_t size) ;
extern void Free(void *ptr);
 
#endif
