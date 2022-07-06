#include "common.h"

void sendMess(int fd, char buff[])
{
    write(fd, buff, BUFFER_SIZE);
}

void recvMess(int fd, char buff[])
{
    read(fd, buff, BUFFER_SIZE);
}