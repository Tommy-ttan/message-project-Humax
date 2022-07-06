
#include </usr/include/x86_64-linux-gnu/sys/select.h>
#include"client.h"


/**
 * @brief function tto init client
 * 
 * @return int: return file discription of client socket
 */
int initClient(void)
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
int connectServer()
{
    struct sockaddr_in _saddr;
    int _ret_val, _count = 0, _fd_socket;
    char _buffer_IP[50];
    _fd_socket = initClient();
    if(_fd_socket == -1)
    {
        fprintf(stderr, "socket failed [%s]\n", strerror(errno));
        return -1;
    }
    
    _saddr.sin_family = AF_INET;
    _saddr.sin_port = htons(SOCKET_PORT);
    while (1)
    {
        if(_count > 2)
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
                printf("The Socket is now connected\n");
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
int chooseRole(void)
{
    int _role = 0;

    printf("Please choose your role: \n");
    printf("1.Listener\n2.Talker\n3.Both\n");
    printf("Enter your choice:");
    scanf("%d", &_role);
    if(_role < 0 || _role > 3)
    {
        while(_role < 0 || _role > 3)
        {
            printf("\nYour choice is invalid, please choose again:");
            scanf("%d", &_role);
        }
    }
    return _role;
}
