#ifndef __CLIENT_H__
#define __CLIENT_H__

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