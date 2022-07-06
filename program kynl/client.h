#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "common.h"

struct client 
{
    int fd;
    int role;
    char send_buff[BUFFER_SIZE];
    char recv_buff[BUFFER_SIZE];
    int (*pfunc_send)(int, char *);
    int (*pfunc_recv)(int, char *);
};

extern char input_buf[BUFFER_SIZE];

char getch();
void Client_showBuffer();                                     
void Client_printMessage(char *);               
void Client_processInput(char ch, void (*pfunc_process)(), void (*pfunc_exit)()); 

int Client_connect(void);
int Client_chooseRole(void);


#endif
