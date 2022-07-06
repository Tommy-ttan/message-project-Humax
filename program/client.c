#include "client.h"

char input_buf[INPUT_BUFFER_SIZE] = "";

// Kynl
/**
 * @brief get character from stdin
 * 
 * @return char 
 */
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

/**
 * @brief print message at select line
 * 
 * @param lines 
 * @param msg 
 */
void printMessageInLine(int lines, char *msg)
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

/**
 * @brief show buffer (user input temp)
 * 
 */
void showBuffer()
{
        char buf[INPUT_BUFFER_SIZE + 9];
        sprintf(buf, "Message: %s", input_buf);
        printMessageInLine(1, buf);
}

/**
 * @brief insert new message in screen
 * 
 * @param msg 
 */
void printMessage(char *msg)
{
        printf("\n\n");
        printMessageInLine(4, msg);
        printMessageInLine(3, "_____________________");
        printMessageInLine(2, "Enter ':q' to quit");
        showBuffer();
}

/**
 * @brief check valid input message
 * 
 * @param msg 
 * @return int 
 */
int checkValidInputMessage(char *msg)
{
        for(int i=0; i<strlen(msg); i++)
                if(isalpha(msg[i]) || isdigit(msg[i]))
                        return 1;
        return 0;
}

/**
 * @brief process user input
 * 
 * @param ch 
 */
void processInput(char ch, void (*p_exit_func)())
{
        if(ch == '\n' || strlen(input_buf) >= INPUT_BUFFER_SIZE)        //newline or buffer's length is maximum
        {
                if(!strcmp(input_buf, EXIT_STRING))
                    p_exit_func();
                if(checkValidInputMessage(input_buf))
                    printMessage(input_buf);
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