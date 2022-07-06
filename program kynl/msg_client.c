#include "client.h"
#include "common.h"

struct client gclient;
pthread_t gthreads_recv;
int gthread_recv_id;

void sendMessageToServer()
{
	gclient.pfunc_send(gclient.fd, input_buf);
}
void exitProgram()
{
	sendMess(gclient.fd, EXIT_MESSAGE);
	printf("\nQuit program\n");
	exit(0);
}
void *RecvMessageHandle(void *arg_client_fd)
{
	int n;
	int client_fd = *((int *)arg_client_fd);
	while (1)
	{
		n = gclient.pfunc_recv(client_fd, gclient.recv_buff);
		if(n < 0)
		{
			perror("Error while receiving data from server");
			exit(1);
		}
		else if(n == 0)
		{
			printf("Server is closed!");
			exitProgram();
		}
		else
		{
			Client_printMessage(gclient.recv_buff);
		}
		memset(gclient.recv_buff, 0, BUFFER_SIZE);
	}
	return NULL;
}

int main()
{
	printf("\n--- HUMAX CHAT APP ----\n");
	//connect to server
	gclient.fd = Client_connect();
	if(gclient.fd < 0)
		exit(1);
	//select role
	gclient.role = Client_chooseRole();
	switch (gclient.role)
	{
	case 1:
		gclient.pfunc_send = NULL;
		gclient.pfunc_recv = recvMess;
		break;
	case 2:
		gclient.pfunc_send = sendMess;
		gclient.pfunc_recv = NULL;
		break;
	default:
		gclient.pfunc_send = sendMess;
		gclient.pfunc_recv = recvMess;
		break;
	}
	//welcome to chat room
	printf("\n---- WELCOME TO HUMAX CHAT ROOM ----\n\n\n\n");
	Client_printMessage("");

	//create receive thread
	if(gclient.pfunc_recv != NULL)
		gthread_recv_id = pthread_create(&gthreads_recv, NULL, RecvMessageHandle, (void *)&gclient.fd);

	// insert input message
	while (1)
	{
		//handle each character entered by the user
		//2 functions will be executed when the user enters a message or exits the program
		Client_processInput(getch(), sendMessageToServer, exitProgram);
		//display entered characters
		Client_showBuffer();
	}

	return 0;
}