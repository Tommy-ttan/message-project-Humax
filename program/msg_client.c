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

char input_buf[INPUT_BUFFER_SIZE] = "";
pthread_t thread_recv, thread_insert_msg;
int thread_recv_id;


char getch(void);                               //get character from stdin
void printMessage(int, char *);                 //print message at select line
void showBuffer();                              //show buffer (user input temp)
void insertNewMessage(char *);                  //insert new message in screen
int checkValidInputMessage(char *);             //check valid input message 
void processInput(char);                        //process user input
void exitProgram();                             //run before the program ends
void *threadRecvMessageFunc(void *);            //thread receive message from server


char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
 }
void printMessage(int lines, char *msg)
{
        printf( "\r"                    // Moves cursor to beginning of line.
                "\033[1B"               // Move cursor up 1 lines.
                "\033[s"                // Save cursor position. 
                "\033[%dA"              // Move cursor up d lines.
                "\x1b[2K"               // Clear entire line
                "%s"                    // String to print.
                "\033[u"                // Restore cursor position.
                "\033[1A"               // Move cursor up d lines.
                "\033[%ldC"             // Move cursor to end of lines.
                ,
                lines,
                msg, 
                strlen(input_buf) + 9
        );
        fflush(stdout);
}
void showBuffer()
{
        char buf[INPUT_BUFFER_SIZE + 9];
        sprintf(buf, "Message: %s", input_buf);
        printMessage(1, buf);
}
void insertNewMessage(char *msg)
{
        printf("\n\n");
        printMessage(4, msg);
        printMessage(3, "_____________________");
        printMessage(2, "Enter ':q' to quit");
        showBuffer();
}
int checkValidInputMessage(char *msg)
{
        for(int i=0; i<strlen(msg); i++)
                if(isalpha(msg[i]) || isdigit(msg[i]))
                        return 1;
        return 0;
}
void processInput(char ch)
{
        if(ch=='\n' || strlen(input_buf) >= INPUT_BUFFER_SIZE)        //newline or buffer's length is maximum
        {
                if(!strcmp(input_buf, EXIT_STRING))
                        exitProgram();
                if(checkValidInputMessage(input_buf))
                        insertNewMessage(input_buf);
                input_buf[0]='\0';
        }
        else if(ch == 127)        //backspace
        {
              input_buf[strlen(input_buf)-1] = '\0';  
        }
        else if(isprint(ch))    //insert ch to buffer
        {
                int len = strlen(input_buf);
                input_buf[len] = ch;
                input_buf[len+1] = '\0';
        }
}
void exitProgram()
{
        printf("\nQuit program\n");
        exit(0);
}
void *threadRecvMessageFunc(void *arg)
{
        char s[10][20]={"Oneeeeeeee","Twoooooooo","Threeeeeee","Fourrrrrrr","Fiveeeeeeeee",
                "Sixxxxxxxxxx","Sevennnnnnnnn","Eighttttttttt","Nineeeeeee","Tennnnnnnnn"};
        int i=0;
        while(1)
        {
                i=(i+1)%10;
                insertNewMessage(s[i]);
                usleep(1000000);
        }
        return arg;
}


int main()
{
        printf("\nWELCOME TO HUMAX CHAT ROOM\n\n\n\n");
        insertNewMessage("");

        //recv msg thread
        thread_recv_id = pthread_create(&thread_recv, NULL, threadRecvMessageFunc, NULL);

        //insert input message
        while(1)
        {
                processInput(getch());
		showBuffer();      
        }

        return 0;
}
