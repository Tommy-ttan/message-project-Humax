#include "client.h"
#include "common.h"

struct client gclient;
pthread_t gthreads_recv;
int gthread_recv_id;

void sendMessageToServer()
{
	char _buf[BUFFER_SIZE + 20];
	sprintf(_buf, "%s: %s", gclient.name, input_buf);

	//send message when user is talker or both
	if(gclient.role != ROLE_LISTENER)
		sendMess(gclient.fd, _buf);
	else
		Client_printMessage("[Message center]: Listener can not send messages!");

	//because talker can't receive messages, so we need to display the message on the screen
	if(gclient.role == ROLE_TALKER)
		Client_printMessage(_buf);
}
void exitProgram()
{
	char _buf[BUFFER_SIZE];
	sprintf(_buf, "[Message center]: %s has letf the room!", gclient.name);
	sendMess(gclient.fd, _buf);
	//exit message
	sendMess(gclient.fd, EXIT_MESSAGE);
	//exit program
	printf("\nQuit program\n");
	exit(0);
}
void *RecvMessageHandle(void *arg_client_fd)
{
	int n;
	int client_fd = *((int *)arg_client_fd);
	while (1)
	{
		n = recvMess(client_fd, gclient.recv_buff);
		if(n < 0)
		{
			printf("\nError while receiving data from server");
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
	
	//enter user's name
	Client_getUserName(gclient.name);

	//select role
	gclient.role = Client_chooseRole();

	//welcome to chat room
	printf("\n---- WELCOME TO HUMAX CHAT ROOM ----\n\n\n\n");
	Client_printMessage("");
	char _buf[BUFFER_SIZE + 20];
	sprintf(_buf, "[Message center]: %s has joined the room!", gclient.name);
	sendMess(gclient.fd, _buf);

	//create receive thread
	if(gclient.role != ROLE_TALKER)
		gthread_recv_id = pthread_create(&gthreads_recv, NULL, RecvMessageHandle, (void *)&gclient.fd);

	// insert input message
	while (1)
	{
		//handle each character entered by the user
		//2 functions will be executed when the user enters a message or exits the program
		Client_processInput(getch(), sendMessageToServer, exitProgram);
	}

	return 0;
}