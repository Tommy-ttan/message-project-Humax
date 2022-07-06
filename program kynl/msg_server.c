#include "server.h"
#include "common.h"

p_client gclient_list;
int glisten_fd;

void *ClientHandle(void *arg_client_fd)
{
    int n;
    int client_fd = *((int *)arg_client_fd);
    char _recv_buf[BUFFER_SIZE];
    printf("client fd: %d\n", client_fd);
    while (1)
    {
		memset(_recv_buf, 0, BUFFER_SIZE);
        n = recvMess(client_fd, _recv_buf);
        if(n < 0)
		{
			perror("Error while receiving data from client");
			exit(1);
		}
		//else if(n == 0 || !strcmp(_recv_buf, EXIT_MESSAGE))
        else if(n == 0)
		{
			Server_removeList(gclient_list, client_fd);
            printf("Remove client fd: %d\n", client_fd);
		}
		else
		{
			printf("client fd %d: %s\n", client_fd, _recv_buf);
            Server_sendAll(gclient_list, _recv_buf);
		}
    }
    return arg_client_fd;   
}

int main()
{
    pthread_t tid;
    int new_client_fd;
    
    printf("\n--- HUMAX CHAT APP SERVER ----\n");
    //create list
    gclient_list = Server_createList();
    //init server
    glisten_fd = Server_init();

    while (1)
    {
        //accpet connection from client
        new_client_fd = Server_acceptConnect(glisten_fd, gclient_list);
        printf("Accecpt new client fd: %d\n", new_client_fd);
        //create new thread for each client
        //pthread_t *clien_thread_attr = Server_readLastThreadAttr(gclient_list);
        //pthread_create(clien_thread_attr, NULL, ClientHandle, NULL);
        pthread_create(&tid, NULL, ClientHandle, (void *)&new_client_fd);
    }


    
    printf("Server is closed!\n");
    return 0;
}
