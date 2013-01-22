#include "common.h"

/* ioctl 相关命令 */
#define READ_STATUS                0x0011
#define READ_FIFO                  0x0012
#define WRITE_STATUS               0x0211
#define SET_TXMODE                 0x0221
#define SET_RXMODE                 0x0222
#define RX_FLUSH                   0x0300
#define TX_FLUSH                   0x0310
#define WRITE_DATA_CHANNEL         0x0400
#define REG_RESET                  0x8000
#define SHUTDOWN                   0x0900

#define Bufsize 5
#define EpSize 128
#define MAX_EVENTS 128

volatile unsigned char data_pipe = 0;
volatile unsigned char data_channel = 0;
unsigned char TxBuf[Bufsize] = {0x05, 0x06, 0x07, 0x08, 0x09};
unsigned char RxBuf[Bufsize] = {0};
pthread_mutex_t psyc;
sem_t nrf_sem;
static int nrf_fd;

/*  在RxBuf中最后一个字节，也就是第4个字节，存放的是发送端的编号，
 *  从这个编号，便可在TX_ADDRESS_LIST中查找出对应的发送端地址
 */
void send_ctrl(int cmd)
{
    switch (cmd) {
        case 1 :
            TxBuf[0] = 0x2;
            break;
        case 2 :
            TxBuf[0] = 0x1;
            break;
        case 3 :
            TxBuf[0] = 0x1;
            break;
        case 4 :
            TxBuf[0] = 0x1;
            break;
        case 5 :
            TxBuf[0] = 0x5;
            break;
        case 6 :
            TxBuf[0] = 0x6;
            break;
        case 7 :
            TxBuf[0] = 0x7;
            break;
        case 8 :
            TxBuf[0] = 0x8;
            break;
        case 9 :
            TxBuf[0] = 0x9;
            break;
        default:break;
    }
    Sem_wait(&nrf_sem);
    //ioctl(nrf_fd, WRITE_DATA_CHANNEL, data_pipe);
    write(nrf_fd, TxBuf, Bufsize);
    //ioctl(nrf_fd, SET_RXMODE, NULL);
    Sem_post(&nrf_sem);
    printf("TxBuf : %d\n", TxBuf[0]);
}



void read_ctrl(int data)
{
    switch ( data & 0x0f) {
        case POLLIN:
            Sem_wait(&nrf_sem);
            read(nrf_fd, RxBuf, Bufsize);
            //ioctl(nrf_fd, SET_RXMODE, NULL);
            Sem_post(&nrf_sem);

            printf("1 > %x, 2 > %x, 3 > %x, 4 > %x, channel > %x, res : %d\n", \
                    RxBuf[0], RxBuf[1], RxBuf[2], RxBuf[3], RxBuf[4] );


            hstat.temprature[0] = RxBuf[0];
            hstat.temprature[1] = RxBuf[1];

            unsigned short int temp = 0;
            float vis = RxBuf[0] & 0x04;
            temp = RxBuf[0] & 0x40;
            temp |= (RxBuf[1] << 8);
            temp = temp >> 4;
            vis = (float)temp + vis/16;
            printf("the temp is %f\n", vis);

            break;
        case POLLOUT:
            printf("send ok...\n");
            break;
        case POLLERR:
            printf("when sended, a error appeared...\n");
            break;
        default :
            break;
    }  

    return;
}

int nrf_init(struct epoll_event *nrf_event)
{
    int nrf_fd = open("/dev/nrf24l01", O_RDWR);  
    if(nrf_fd < 0) {
        perror("Can't open /dev/nrf24l01 \n");
        exit(1);
    }
    printf("open /dev/nrf24l01 success. fd is %x \n", nrf_fd);

    //clean the status
    ioctl(nrf_fd, REG_RESET, NULL);

    return nrf_fd;
}

void *nrf_send(void *argwr)
{
    int cmd;
    sleep(1);
    while (1) {
        cmd = sbuf_remove(&sbuf);
        printf("come to a cmd\n");
        send_ctrl(cmd);
    }

    return (void *)1;
}


void *nrf_read(void *argrd)
{

    int i, ret;
    int ep_fd;
    struct epoll_event nrf_event, *events;

    //init nrf24l01
    nrf_fd = nrf_init(&nrf_event);
    nrf_event.data.fd = nrf_fd;
    nrf_event.events = EPOLLIN;// | EPOLLOUT; //make send ok and out of kernal

    /* init epoll struct */
    ep_fd = epoll_create(EpSize);
    if (ep_fd < 0) {
        perror("failed to epoll create");
        exit(1);
    }
    //add event to ep_fd
    ret = epoll_ctl(ep_fd, EPOLL_CTL_ADD, nrf_fd, &nrf_event);
    if (ret) {
        perror("failed to epoll_ctl");
        exit(1);
    }

    events = Malloc(sizeof(struct epoll_event) * MAX_EVENTS);
    for( ; ; ) {
        ret = epoll_wait(ep_fd, events, MAX_EVENTS, -1);
        if (ret < 0) {
            perror("failed to wait");
            break;
        }
        for (i = 0; i < ret; i++) {
            printf("event= 0x%x, on fd = 0x%x\n", 
                    events[i].events, events[i].data.fd);
            if (events[i].data.fd == nrf_fd) {
                data_pipe = (unsigned char)((events[i].events & 0xf0) >> 4);
                printf("event %x have a msg to read from pipe %d...\n",
                                events[i].events, data_pipe);
                read_ctrl(events[i].events);
            }
        }
        #ifdef DEBUG
            printf("one round is over\n");
        #endif
    }

    free(events);
    close(nrf_fd);
    close(ep_fd);

    return 0;
}


void *do_nrf(void *arg)
{
    pthread_t tid[2];
    Pthread_mutex_init(&psyc, NULL);
    Sem_init(&nrf_sem, 0, 1);

    pthread_create(&tid[0], NULL, nrf_send, NULL);
    pthread_create(&tid[1], NULL, nrf_read, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    Sem_destroy(&nrf_sem);
    Pthread_mutex_destroy(&psyc);
    return 0;
}

