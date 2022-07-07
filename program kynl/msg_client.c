#include "client.h"
#include "common.h"

struct client gclient;
pthread_t gthread_id = 0;

void sendMessageToServer()
{
<<<<<<< HEAD:programKynl/msg_client.c
	char _buf[BUFFER_SIZE + 101];
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
	//kill recv thread
	if(gthread_id != 0)
		pthread_cancel(gthread_id);
	//send exit message to server
	if(gclient.connected)
	{
		char _buf[BUFFER_SIZE];
		sprintf(_buf, "[Message center]: %s letf the room!", gclient.name);
		sendMess(gclient.fd, _buf);
		sendMess(gclient.fd, EXIT_MESSAGE);
		close(gclient.fd);
	}
	//exit program
=======
	gclient.pfunc_send(gclient.fd, input_buf);
}
void exitProgram()
{
	sendMess(gclient.fd, EXIT_MESSAGE);
>>>>>>> parent of a269e9a (fix bug and add user name):program kynl/msg_client.c
	printf("\nQuit program\n");
	printf("\n\r");
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
			printf("\nServer is closed!");
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
void ctr_C_handler(sig_t s)
{
	exitProgram();
}

int main()
{
	//hanlde ctrl-C signal
	signal (SIGINT, ctr_C_handler);
	//connect to server
	printf("\n--- HUMAX CHAT APP ----\n");
	gclient.connected = 0;
	gclient.fd = Client_connect();
	if(gclient.fd < 0)
		exit(1);
<<<<<<< HEAD:programKynl/msg_client.c
	gclient.connected = 1;

	//enter user's name
	Client_getUserName(gclient.name);

=======
>>>>>>> parent of a269e9a (fix bug and add user name):program kynl/msg_client.c
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
<<<<<<< HEAD:programKynl/msg_client.c
	char _buf[BUFFER_SIZE + 20];
	sprintf(_buf, "[Message center]: %s joined the room!", gclient.name);
	sendMess(gclient.fd, _buf);

	//create receive thread
	if(gclient.role != ROLE_TALKER)
		pthread_create(&gthread_id, NULL, RecvMessageHandle, (void *)&gclient.fd);
=======

	//create receive thread
	if(gclient.pfunc_recv != NULL)
		gthread_recv_id = pthread_create(&gthreads_recv, NULL, RecvMessageHandle, (void *)&gclient.fd);
>>>>>>> parent of a269e9a (fix bug and add user name):program kynl/msg_client.c

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