#ifndef __SERVER_H__
#define __SERVER_H__

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


#define EXIT_STRING             ":q"
#define INPUT_BUFFER_SIZE       255


char getch(void); 
void printMessage(int, char *);                 
void showBuffer();                              
void insertNewMessage(char *);                  
int checkValidInputMessage(char *);      
void processInput(char, void (*)());   

#endif