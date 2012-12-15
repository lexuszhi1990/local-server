#include "common.h"

int init_udp_sock(in_port_t port, const char *ip)
{
	int sfd, res, optval=1;
	struct sockaddr_in udp_serv_addr;

	sfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sfd == -1)
		return -1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, 
		   (const void *)&optval , sizeof(int)) < 0)
		return -1;

	memset(&udp_serv_addr, 0, sizeof(udp_serv_addr));
	udp_serv_addr.sin_family = AF_INET;
	udp_serv_addr.sin_port = htons(port);	
	inet_pton(AF_INET, ip, &udp_serv_addr.sin_addr.s_addr);

	res = bind(sfd, (struct sockaddr *)&udp_serv_addr, sizeof(udp_serv_addr));
	if(res == -1){
		close(sfd);
		return -1;
	}

	return sfd;
}

int init_tcp_sock(in_port_t port, const char *ip)
{
	int lfd, res, optval=1;
	struct sockaddr_in serv_addr;

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if(lfd == -1)
		return -1;
	if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, 
		   (const void *)&optval , sizeof(int)) < 0)
		return -1;

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(TCP_PORT);
	inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

	res = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if(res == -1){
		close(lfd);
		return -1;
	}

	res = listen(lfd, QLEN);
	if(res == -1){
		close(lfd);
		return -1;
	}

	return lfd;
}

int udp_clientfd(int port, const char *ip) 
{
    int clientfd; 
    struct sockaddr_in serveraddr;

    if ((clientfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	return -1; /* check errno for cause of error */

    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serveraddr.sin_addr.s_addr);

    /* Establish a connection with the server */
    if (connect(clientfd, (SA *) &serveraddr, sizeof(serveraddr)) < 0)
	return -1;
    return clientfd;
}

int tcp_clientfd(int port, const char *ip) 
{
    int clientfd; 
    struct sockaddr_in serveraddr;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	return -1; /* check errno for cause of error */

    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serveraddr.sin_addr.s_addr);

    /* Establish a connection with the server */
    if (connect(clientfd, (SA *) &serveraddr, sizeof(serveraddr)) < 0)
	return -1;
    return clientfd;
}





/**************************** 
* Sockets interface wrappers
****************************/

int Socket(int domain, int type, int protocol) 
{
    int rc;

    if ((rc = socket(domain, type, protocol)) < 0)
	err_sys("Socket error");
    return rc;
}

void Setsockopt(int s, int level, int optname, const void *optval, int optlen) 
{
    int rc;

    if ((rc = setsockopt(s, level, optname, optval, optlen)) < 0)
	err_sys("Setsockopt error");
}

void Bind(int sockfd, struct sockaddr *my_addr, int addrlen) 
{
    int rc;

    if ((rc = bind(sockfd, my_addr, addrlen)) < 0)
	err_sys("Bind error");
}

void Listen(int s, int backlog) 
{
    int rc;

    if ((rc = listen(s,  backlog)) < 0)
	err_sys("Listen error");
}

int Accept(int s, struct sockaddr *addr, socklen_t *addrlen) 
{
    int rc;

    if ((rc = accept(s, addr, addrlen)) < 0)
	err_sys("Accept error");
    return rc;
}

void Connect(int sockfd, struct sockaddr *serv_addr, int addrlen) 
{
    int rc;

    if ((rc = connect(sockfd, serv_addr, addrlen)) < 0)
	err_sys("Connect error");
}


