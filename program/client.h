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
void printMessageInLine(int, char *);                 
void showBuffer();                              
void printMessage(char *);                  
int checkValidInputMessage(char *);      
void processInput(char, void (*)());   

int initClient(void);
int connectServer(void);
int chooseRole(void);


#endif
