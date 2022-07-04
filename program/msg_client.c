#include "server.h"
#include "client.h"
#include "common.h"

pthread_t thread_recv, thread_insert_msg;
int thread_recv_id;

void exitProgram();					 // run before the program ends
void *threadRecvMessageFunc(void *); // thread receive message from server

void exitProgram()
{
	printf("\nQuit program\n");
	exit(0);
}
void *threadRecvMessageFunc_test(void *arg)
{
	char s[10][20] = {"Oneeeeeeee", "Twoooooooo", "Threeeeeee", "Fourrrrrrr", "Fiveeeeeeeee",
					  "Sixxxxxxxxxx", "Sevennnnnnnnn", "Eighttttttttt", "Nineeeeeee", "Tennnnnnnnn"};
	int i = 0;
	while (1)
	{
		i = (i + 1) % 10;
		insertNewMessage(s[i]);
		usleep(1000000);
	}
	return arg;
}

int main()
{
	printf("--- HUMAX CHAT APP ----");

	printf("\n---- WELCOME TO HUMAX CHAT ROOM ----\n\n\n\n");
	insertNewMessage("");

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