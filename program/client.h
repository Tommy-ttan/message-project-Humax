#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "common.h"

struct client 
{
    int fd;
    int role;
    char send_buff[BUFFER_SIZE];
    char recv_buff[BUFFER_SIZE];
    void (*pfunc_send)();
    void (*pfunc_recv)();
};

char getch(void); 
void Client_printMessageInLine(int, char *);    
void Client_showBuffer();                                     
void Client_printMessage(char *);                  
int Client_checkValidInputMessage(char *);      
void Client_processInput(char ch, void (*pfunc_process)(), void (*pfunc_exit)()); 

int Client_init(void);
int Client_connect(void);
int Client_chooseRole(void);


#endif
