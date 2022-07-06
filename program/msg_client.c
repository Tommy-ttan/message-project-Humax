#include "client.h"
#include "common.h"


void sendMessageToServer()
{
}
void exitProgram()
{
	//	sendMessage(server_fd, EXIT_MESSAGE);
	printf("\nQuit program\n");
	exit(0);
}

int main()
{
	printf("--- HUMAX CHAT APP ----");

	printf("\n---- WELCOME TO HUMAX CHAT ROOM ----\n\n\n\n");
	Client_printMessage("");


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