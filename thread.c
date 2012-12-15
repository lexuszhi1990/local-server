#include "common.h"


void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp, 
        void * (*routine)(void *), void *argp) 
{
    int rc;

    if ((rc = pthread_create(tidp, attrp, routine, argp)) != 0)
        err_sys( "Pthread_create error");
}

void Pthread_cancel(pthread_t tid) 
{
    int rc;

    if ((rc = pthread_cancel(tid)) != 0)
        err_sys( "Pthread_cancel error");
}

void Pthread_join(pthread_t tid, void **thread_return)
{
    int rc;

    if ((rc = pthread_join(tid, thread_return)) != 0)
        err_sys( "Pthread_join error");
}

/* $begin detach */
void Pthread_detach(pthread_t tid) 
{
    int rc;

    if ((rc = pthread_detach(tid)) != 0)
        err_sys( "Pthread_detach error");
}
/* $end detach */

void Pthread_exit(void *retval) 
{
    pthread_exit(retval);
}

pthread_t Pthread_self(void) 
{
    return pthread_self();
}

void Pthread_once(pthread_once_t *once_control, void (*init_function)()) 
{
    pthread_once(once_control, init_function);
}


/*******************************
 * Wrappers for Posix semaphores
 *******************************/

void Sem_init(sem_t *sem, int pshared, unsigned int value) 
{
    if (sem_init(sem, pshared, value) < 0)
        err_sys("Sem_init error");
}

void Sem_wait(sem_t *sem) 
{
    if (sem_wait(sem) < 0)
        err_sys("P error");
}

void Sem_post(sem_t *sem) 
{
    if (sem_post(sem) < 0)
        err_sys("V error");
}

void Sem_destroy(sem_t *sem) 
{  
    if(sem_destroy(sem) < 0)
        err_sys("Sem destroy err");
}

/*********************************
 * pthread_metux_lock
 *
 * ******************************/
void Pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr)
{
  int res ;
  if ((res = pthread_mutex_init(mutex, mutexattr)) < 0) {
    err_sys("failed to init mutex..."); 
  }
}


void Pthread_mutex_lock(pthread_mutex_t *mutex)
{
  int res ;
  if ((res = pthread_mutex_lock(mutex)) < 0) {
    err_sys("failed to init mutex..."); 
  }
}

void Pthread_mutex_unlock(pthread_mutex_t *mutex)
{
  int res ;
  if ((res = pthread_mutex_unlock(mutex)) < 0) {
    err_sys("failed to unlock mutex..."); 
  }
}

void Pthread_mutex_trylock(pthread_mutex_t *mutex)
{
  int res ;
  if ((res = pthread_mutex_trylock(mutex)) < 0) {
    err_sys("failed to trylock mutex..."); 
  }
}


void Pthread_mutex_destroy(pthread_mutex_t *mutex)
{
  int res ;
  if ((res = pthread_mutex_destroy(mutex)) < 0) {
    err_sys("failed to destroy mutex..."); 
  }
}
