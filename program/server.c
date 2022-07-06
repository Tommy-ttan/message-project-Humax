#include "server.h"

/**
 * @brief Create a Client with next = NULL
 *
 * @param _fd file description of new client
 * @return <p_client>
 */
p_client Server_createClient(int _fd)
{
	p_client head = malloc(sizeof(p_client));
	head->fd = _fd;
	head->next = NULL;
	return head;
}

/**
 * @brief Create a new client list start from head
 *
 * @return <p_client> List_head
 */
p_client Server_createList(void)
{
	return Server_createClient(0);
}

/**
 * @brief add new client to list. 
 * create a new list if there's no list
 * @param _client_list active client list
 * @param _fd file description of client
 * @return <int> success or not
 */
int Server_addList(p_client _client_list, int _fd)
{
	if (_client_list == NULL)
	{
		_client_list = Server_createList();
		Server_addList(_client_list, _fd);
		return 1;
	}
	p_client _browse = _client_list;
	while (_browse->next != NULL)
	{
		_browse = _browse->next;
	}
	p_client _new = Server_createClient(_fd);
	_browse->next = _new;

	return 1;
}

/**
 * @brief remove a client from client list
 *
 * @param _client_list active client list
 * @param _fd file description of client need to be removed
 * @return <int> success or not
 */
int Server_removeList(p_client _client_list, int _fd)
{
	if (_client_list == NULL)
		return 0;
	p_client _browse1 = _client_list;
	p_client _browse2 = _browse1->next;
	while (_browse2 != NULL)
	{
		if (_browse2->fd == _fd)
		{
			_browse1->next = _browse2->next;
			free(_browse2);
			return 1;
		}
		_browse1 = _browse2;
		_browse2 = _browse2->next;
	}
	return 0;
}

/**
 * @brief Show the current client list
 *
 * @param _client_list active client list
 * @return <int> empty or not
 */
int Server_showList(p_client _client_list)
{
	if (_client_list == NULL || _client_list->next == NULL)
	{
		printf("Client list is empty");
		return 0;
	}

	p_client _browse = _client_list->next;
	while (_browse != NULL)
	{
		printf("%d -> ", _browse->fd);
		_browse = _browse->next;
	}
	printf("NULL\n");
	return 1;
}

/**
 * @brief Init the server
 * 
 * @return <int> listenfd, as a param of Server_acceptConnect() 
 */
int Server_init(void)
{
	int listenfd = 0;
	struct sockaddr_in serv_addr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SOCKET_PORT);

	bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(listenfd, 10);

	return listenfd;
}
/**
 * @brief accept new connection and add new client to list
 * 
 * @param listenFd: file discriptor of server socket
 * @param _client_list: linked list of clients 
 * @return int: return file discriptor of neww socket that connect to client
 */
int Server_acceptConnect(int  listenFd, p_client _client_list)
{
	int newFd;
	struct sockaddr_in newAddr;
	socklen_t cliLen = sizeof(newAddr);
	newFD = accept(listenFd, (struct sockaddr*)&new_addr, &cliLen);
	if(newFd >= 0)
	{
		Server_addList(_client_list, listenFd);
	}
	return newFd;
}
