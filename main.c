#include "common.h"

tfn_t handler[TH_NUM] = {do_reg, do_nrf};

int main(int argc, char *argv[])
{
	pthread_t tid[TH_NUM];
  arg_t arg[TH_NUM];
  int res[TH_NUM], i;
	in_port_t port[TH_NUM] = {TCP_PORT,
				RENEW_PORT,
        UDP_PORT};

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

  return 0;
}
