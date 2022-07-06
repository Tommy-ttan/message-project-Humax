#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h> 
#include <netdb.h> 

#define SOCKET_PORT	    5000

int initClient(void);
int connectServer(void);
int chooseRole(void);


struct client 
{
    int fd;
    int role;
    char *send_buff[];
    char *recv_buff[];
    void (*pfunc_send)();
    void (*pfunc_recv)();
}




#endif
