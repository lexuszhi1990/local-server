#ifndef DO_REG_H_
#define DO_REG_H_


typedef struct
{
	char *serv_ip;
	in_port_t port;
}arg_t;

typedef void *(*tfn_t)(void *);

typedef struct 
{
  unsigned char temprature[2];
}home_stat;

extern sbuf_t sbuf;
extern home_stat hstat;

extern void *do_reg(void *arg); 

#endif
