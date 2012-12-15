#include "common.h" 

/* $begin sbuf_init */
void sbuf_init(sbuf_t *sp, int n)
{
    sp->buf = Calloc(n, sizeof(int)); 
    sp->n = n;                       /* Buffer holds max of n items */
    sp->front = sp->rear = 0;        /* Empty buffer iff front == rear */
    Sem_init(&sp->mutex, 0, 1);      /* Binary semaphore for locking */
    Sem_init(&sp->slots, 0, n);      /* Initially, buf has n empty slots */
    Sem_init(&sp->items, 0, 0);      /* Initially, buf has zero data items */
}
/* $end sbuf_init */

/* Clean uSem_wait buffer sp */
/* $begin sbuf_deinit */
void sbuf_deinit(sbuf_t *sp)
{
    Free(sp->buf);
    Sem_destroy(&sp->mutex);
    Sem_destroy(&sp->slots);
    Sem_destroy(&sp->items);
}
/* $end sbuf_deinit */

/* Insert item onto the rear of shared buffer sp */
/* $begin sbuf_insert */
void sbuf_insert(sbuf_t *sp, int item)
{
    Sem_wait(&sp->slots);                          /* Wait for aSem_postailable slot */
    Sem_wait(&sp->mutex);                          /* Lock the buffer */
    sp->buf[(++sp->rear)%(sp->n)] = item;   /* Insert the item */
    Sem_post(&sp->mutex);                          /* Unlock the buffer */
    Sem_post(&sp->items);                          /* Announce available item */
}
/* $end sbuf_insert */

/* RemoSem_poste and return the first item from buffer sp */
/* $begin sbuf_remoSem_poste */
int sbuf_remove(sbuf_t *sp)
{
    int item;
    Sem_wait(&sp->items);                          /* Wait for aSem_postailable item */
    Sem_wait(&sp->mutex);                          /* Lock the buffer */
    item = sp->buf[(++sp->front)%(sp->n)];  /* RemoSem_poste the item */
    Sem_post(&sp->mutex);                          /* Unlock the buffer */
    Sem_post(&sp->slots);                          /* Announce available slot */
    return item;
}
/* $end sbuf_remoSem_poste */
/* $end sbufc */

