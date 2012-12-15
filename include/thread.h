#ifndef _THREAD_H_
#define _THREAD_H_

extern void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp, 
		    void * (*routine)(void *), void *argp) ;
extern void Pthread_exit(void *retval) ;
extern void Pthread_cancel(pthread_t tid) ;
extern void Pthread_join(pthread_t tid, void **thread_return);
extern void Pthread_detach(pthread_t tid);
extern void Pthread_once(pthread_once_t *once_control, void (*init_function)()) ;
extern pthread_t Pthread_self(void);

extern void Sem_init(sem_t *sem, int pshared, unsigned int value);
extern void Sem_wait(sem_t *sem);
extern void Sem_post(sem_t *sem);
extern void Sem_destroy(sem_t *sem);

extern void Pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
extern void Pthread_mutex_lock(pthread_mutex_t *mutex);
extern void Pthread_mutex_unlock(pthread_mutex_t *mutex);
extern void Pthread_mutex_trylock(pthread_mutex_t *mutex);
extern void Pthread_mutex_destroy(pthread_mutex_t *mutex);


#endif
