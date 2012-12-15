#include "common.h"

void err_thread(const char *str, int err)
{
	char msg[BUF_SIZE];
	
	sprintf(msg, "%s : %s\n", str, strerror(err));
	fputs(msg, stderr);

//	pthread_exit((void *)3);
}
void delay_thread(const char *str)
{
	perror(str);
//	pthread_exit((void *)3);
}

void err_sys(const char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
} 

void delay_sys(const char *str)
{
	perror(str);
	sleep(DELAY_SEC);
}
