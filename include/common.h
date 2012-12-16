#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "sock.h"
#include "err.h"    
#include "thread.h"
#include "mem.h"
#include "sbuf.h"

#include "do_reg.h"
#include "do_nrf.h"

#define BUF_SIZE 1024
#define SHORT_BUF 128
#define QLEN 20
#define SEC 5
#define TH_NUM 2
#define ROOT_PATH "../jpg"

#define TCP_PORT 8000
#define UDP_PORT 8080
#define RENEW_PORT 8060
#define SERV_IP "192.168.1.4"

#define RENEW_MSG "need renew"
#define FIRST_MSG "first renew"

#endif 
