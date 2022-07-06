#include "client.h"
#include "common.h"

char input_buf[BUFFER_SIZE] = "";

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
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

/**
 * @brief print message at select line
 *
 * @param lines
 * @param msg
 */
void Client_printMessageInLine(int lines, char *msg)
{
    printf("\r"        // Moves cursor to beginning of line.
           "\033[1B"   // Move cursor up 1 lines.
           "\033[s"    // Save cursor position.
           "\033[%dA"  // Move cursor up d lines.
           "\x1b[2K"   // Clear entire line
           "%s"        // String to print.
           "\033[u"    // Restore cursor position.
           "\033[1A"   // Move cursor up d lines.
           "\033[%ldC" // Move cursor to end of lines.
           ,
           lines,
           msg,
           strlen(input_buf) + 9);
    fflush(stdout);
}

/**
 * @brief show buffer (user input temp)
 *
 */
void Client_showBuffer()
{
    char _buf[BUFFER_SIZE + 9];
    sprintf(_buf, "Message: %s", input_buf);
    Client_printMessageInLine(1, _buf);
}

/**
 * @brief insert new message in screen
 *
 * @param msg message
 */
void Client_printMessage(char *msg)
{
    printf("\n\n");
    Client_printMessageInLine(4, msg);
    Client_printMessageInLine(3, "_____________________");
    Client_printMessageInLine(2, "Enter ':q' to quit");
    Client_showBuffer();
}

/**
 * @brief check valid input message
 *
 * @param msg
 * @return int: return 1 if the message is valid (len>0, not all are spacebars)
 */
int Client_checkValidInputMessage(char *msg)
{
    for (int i = 0; i < strlen(msg); i++)
        if (isalpha(msg[i]) || isdigit(msg[i]))
            return 1;
    return 0;
}

/**
 * @brief handle user input string
 * 
 * @param ch input character
 * @param pfunc_process the function will be executed when the user enters the message
 * @param pfunc_exit The function will be executed when the program exits
 */
void Client_processInput(char ch, void (*pfunc_process)(), void (*pfunc_exit)())
{
    if (ch == '\n') // newline
    {
        if (!strcmp(input_buf, ":q"))
            pfunc_exit();
        if (Client_checkValidInputMessage(input_buf))
		{
            Client_printMessage(input_buf);
			pfunc_process();
		}
        input_buf[0] = '\0';
    }
    else if (ch == 127) // backspace
    {
        input_buf[strlen(input_buf) - 1] = '\0';
    }
    else if (isprint(ch) && strlen(input_buf) < BUFFER_SIZE) // insert ch to buffer
    {
        int _len = strlen(input_buf);
        input_buf[_len] = ch;
        input_buf[_len + 1] = '\0';
    }
}

/**
 * @brief function tto init client
 *
 * @return int: return file discription of client socket
 */
int Client_init(void)
{
    int _fd;
    _fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return _fd;
}

/**
 * @brief: function to connect server
 *
 * @return int: return file discription of client socket
 */
int Client_connect()
{
    struct sockaddr_in _saddr;
    int _ret_val, _count = 0, _fd_socket;
    char _buffer_IP[50];
    _fd_socket = Client_init();
    if (_fd_socket == -1)
    {
        fprintf(stderr, "socket failed [%s]\n", strerror(errno));
        return -1;
    }

    _saddr.sin_family = AF_INET;
    _saddr.sin_port = htons(SOCKET_PORT);
    while (1)
    {
        if (_count > 2)
        {
            printf("Close app!\n");
            close(_fd_socket);
            return -1;
        }
        else
        {
            printf("Enter server IP to connect: ");
            fgets(_buffer_IP, sizeof(_buffer_IP), stdin);
            _buffer_IP[strlen(_buffer_IP) - 1] = '\0';
            _saddr.sin_addr.s_addr = inet_addr(_buffer_IP);
            printf("trying to connect...\n");
            _ret_val = connect(_fd_socket, (struct sockaddr *)&_saddr, sizeof(struct sockaddr_in));
            if (_ret_val == -1)
            {
                printf("the IP address %s is incorrect, please try again!\n", _buffer_IP);
            }
            else
            {
                printf("The Server is now connected\n");
                break;
            }
        }
        _count++;
    }
    return _fd_socket;
}

/**
 * @brief function to choose role of user(as: talker, listener, both)
 *
 * @return int: return an interger corresponds chosen role: 1- Listener
 *                                                          2- Talker
 *                                                          3- Both
 */
int Client_chooseRole(void)
{
    int _role = 0;

    printf("Please choose your role: \n");
    printf("1.Listener\n2.Talker\n3.Both\n");
    printf("Enter your choice:");
    scanf("%d", &_role);
    if (_role < 1 || _role > 3)
    {
        while (_role < 1 || _role > 3)
        {
            printf("\nYour choice is invalid, please choose again:");
            scanf("%d", &_role);
        }
    }
    return _role;
}
