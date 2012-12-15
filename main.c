#include "common.h"

tfn_t handler[TH_NUM] = {do_reg, do_nrf};

int main(int argc, char *argv[])
{ 
	pthread_t tid[TH_NUM];  arg_t arg[TH_NUM];
	in_port_t port[TH_NUM] = {TCP_PORT, 
				RENEW_PORT, 
				UDP_PORT};
  Pthread_mutex_init(&psyc, NULL);
  sbuf_init(&sbuf, SHORT_BUF);
	
	pthread_create(&tid[0], NULL, 
			handler[0], (void *)&arg[0]);
	pthread_join(tid[0], NULL);


  Pthread_mutex_destroy(&psyc);
  sbuf_deinit(&sbuf);

	return 0;
	
#if 0
	for(i = 0; i < TH_NUM; i++){
		arg[i].serv_ip = SERV_IP;	
		arg[i].port = port[i];
	}
	for(i = 0; i < TH_NUM; i++)
		pthread_create(&tid[i], NULL, 
			handler[i], (void *)&arg[i]);
	for(i = 0; i < TH_NUM; i++){
		pthread_join(tid[i], (void **)&res[i]);
		if(res[i] == -1)
			err_thread("fatal error", errno);
	}
	pthread_rwlock_destroy(&rwlock);

#endif

}
