#include "common.h"

void *smalloc(size_t size)
{
	char *p;

	p = (char *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(p == MAP_FAILED) 
		p = NULL;
	return (void *)p;
}

void *make_shared_mem(size_t size)
{
	void *p;

	p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, -1, 0);
	if( p == MAP_FAILED)
		err_sys("Mmap error");
	memset(p, 0, size);

	return p;
}

void *Malloc(size_t size) 
{
    void *p;

    if ((p  = malloc(size)) == NULL)
	err_sys("Malloc error");
    return p;
}

void *Realloc(void *ptr, size_t size) 
{
    void *p;

    if ((p  = realloc(ptr, size)) == NULL)
	err_sys("Realloc error");
    return p;
}

void *Calloc(size_t nmemb, size_t size) 
{
    void *p;

    if ((p = calloc(nmemb, size)) == NULL)
	err_sys("Calloc error");
    return p;
}

void Free(void *ptr) 
{
    free(ptr);
}
