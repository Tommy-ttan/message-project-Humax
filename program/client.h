#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h> 
#include <signal.h>
#include <unistd.h>  
#include <termios.h>
#include <pthread.h>
#include <sys/wait.h>
#include "common.h"



char getch(void); 
void printMessageInLine(int, char *);                 
void showBuffer();                              
void printMessage(char *);                  
int checkValidInputMessage(char *);      
void processInput(char, void (*)());   




#endif