#include "common.h"


pthread_rwlock_t rwlock;
pthread_mutex_t psyc;
sbuf_t sbuf;

void *serv_thread(void *vargp)
{
    int res;
    char buf[SHORT_BUF];
    int connfd;

    Pthread_mutex_lock(&psyc);
    connfd = *(int *)vargp;
    Pthread_mutex_unlock(&psyc);

    Pthread_detach(pthread_self());
#ifdef DEBUG
    printf("one serv thread is created...\n");
#endif
    for(;;){
       res = recv(connfd, buf, SHORT_BUF, 0);
        if (res == -1) {
            delay_sys("fail to recv\n");
            break;
        } else if (res == 0) {
            delay_sys("the connect broken\n"); 
            break;
        }

        buf[res] = 0;
        printf("Have receve the commind : %s\n", buf);
        if (strcmp(buf, "lexus1") == 0) {
            printf("lexus1 forward\n");
            sbuf_insert(&sbuf, 1);
        }
        if (strcmp(buf, "lexus2") == 0) {
            printf("lexus2 back\n");
            sbuf_insert(&sbuf, 2);
        }
        if (strcmp(buf, "lexus3") == 0) {
            printf("lexus3 right\n");
            sbuf_insert(&sbuf, 3);
        }
        if (strcmp(buf, "lexus4") == 0) {
            printf("lexus4 left\n");
            sbuf_insert(&sbuf, 4);
        }
        if (strcmp(buf, "lexusend") == 0) {
            printf("lexusend end\n");
            sbuf_insert(&sbuf, 5);
            break;
        }
    }
    
    printf("cilent %d is left...\n", connfd);
    close(connfd);
    return NULL;
}

void *do_reg(void *arg)
{
	int sfd, nread, confd, n; 
	char buf[BUF_SIZE];
	struct sockaddr_in cli_addr;		
	arg_t *rarg; 
  socklen_t len = sizeof(struct sockaddr_in); 
  pthread_t tid;

	rarg = (arg_t *)arg;
	sfd = init_tcp_sock(rarg->port, rarg->serv_ip);
	if(sfd == -1) {
    err_sys("failed to init tcp socket...\n");
  }
	
#ifdef DEBUG		
  printf("init the tcp sock\n"); /* for debuging... */
#endif
	while(1){
    Pthread_mutex_lock(&psyc);
    confd = Accept(sfd, (SA *)&cli_addr, &len);
    Pthread_mutex_unlock(&psyc);
    Pthread_create(&tid, NULL, serv_thread, &confd);
#ifdef DEBUG		
    printf("one client come to server: %s\n",
            inet_ntoa(cli_addr.sin_addr));
#endif

  }

  close(sfd);
  return NULL;
}

