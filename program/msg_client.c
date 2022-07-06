#include "client.h"
#include "common.h"

pthread_t thread_recv, thread_insert_msg;
int thread_recv_id;


void exitProgram()
{
//	sendMessage(server_fd, EXIT_MESSAGE);
	printf("\nQuit program\n");
	exit(0);
}
void *threadRecvMessageFunc_test(void *arg)
{

	return arg;
}

int main()
{
	printf("--- HUMAX CHAT APP ----");

	printf("\n---- WELCOME TO HUMAX CHAT ROOM ----\n\n\n\n");
	printMessage("");

	// recv msg thread
	//thread_recv_id = pthread_create(&thread_recv, NULL, threadRecvMessageFunc_test, NULL);

	// insert input message
	while (1)
	{
		processInput(getch(), exitProgram);
		showBuffer();
	}

	return 0;
}