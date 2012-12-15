#ifndef SOCK_H_
#define SOCK_H_

typedef struct sockaddr SA;

extern int init_udp_sock(in_port_t port, const char *ip);
extern int init_tcp_sock(in_port_t port, const char *ip);
extern int udp_clientfd(int port, const char *ip) ;
extern int tcp_clientfd(int port, const char *ip) ; 
extern int Socket(int domain, int type, int protocol);
extern void Setsockopt(int s, int level, int optname, const void *optval, int optlen);
extern void Bind(int sockfd, struct sockaddr *my_addr, int addrlen);
extern void Listen(int s, int backlog);
extern int Accept(int s, struct sockaddr *addr, socklen_t *addrlen);
extern void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen);

#endif 
