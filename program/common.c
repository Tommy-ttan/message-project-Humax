#include "common.h"

/**
 * @brief send mess (from buffer)
 * 
 * @param fd
 * @param buff 
 * @return void
 */
void sendMess(int fd, char buff[])
{
    write(fd, buff, BUFFER_SIZE);
}

/**
 * @brief receive message
 * 
 * @param fd
 * @param buff 
 * @return void
 */
void recvMess(int fd, char buff[])
{
    read(fd, buff, BUFFER_SIZE);
}