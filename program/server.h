#ifndef __SERVER_H__
#define __SERVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "common.h"

/**
 * @brief _client structure to make client list, use only for server-side.
 * @param fd file description
 */
typedef struct _client{
	int fd;
	struct _client *next;
} *p_client;

p_client Server_createClient(int _fd);
p_client Server_createList(void);
int Server_addList(p_client _client_list, int _fd);
int Server_removeList(p_client _client_list, int _fd);
int Server_showList(p_client _client_list);

int Server_init(void);


#endif
