#ifndef DO_H_
#define DO_H_


typedef struct
{
	char *serv_ip;
	in_port_t port;
}arg_t;

typedef void *(*tfn_t)(void *);

extern pthread_rwlock_t rwlock;
extern pthread_mutex_t psyc;
extern sbuf_t sbuf;

extern void *do_reg(void *arg); 

#endif
