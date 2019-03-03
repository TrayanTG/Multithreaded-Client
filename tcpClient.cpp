#include<iostream>

#include "tcpClient.h"

CtcpClient::CtcpClient(std::string ipAddress, int port)
	:_ipAddress(ipAddress), _port(port)
{
	//_serverSocket = INVALID_SOCKET;
}

CtcpClient::~CtcpClient()
{
	cleanUp();
}

bool CtcpClient::Init()
{
	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	int wsInit = WSAStartup(ver, &data);

	return wsInit == 0;
}


bool CtcpClient::Connect()
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket != INVALID_SOCKET)
	{
		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(_port);
		inet_pton(AF_INET, _ipAddress.c_str(), &hint.sin_addr);

		int connectResult = connect(_serverSocket, (sockaddr*)&hint, sizeof(hint));
		if (connectResult == SOCKET_ERROR)
		{
			cleanUp();
			return false;
		}
		char buf[MAX_BUFFER_SIZE];
		int bytesReceived = 0;
		memset(buf, 0, MAX_BUFFER_SIZE);
		bytesReceived = recv(_serverSocket, buf, MAX_BUFFER_SIZE, 0);
		std::cout << buf << std::endl;
		return true;
	}
	return false;
}

void CtcpClient::Recv()
{
	char buf[MAX_BUFFER_SIZE];
	int bytesReceived = 0;
	do
	{
		memset(buf, 0, MAX_BUFFER_SIZE);
		bytesReceived = recv(_serverSocket, buf, MAX_BUFFER_SIZE, 0);
		if (bytesReceived >= 0)
		{
			std::cout << std::string(buf, 0, bytesReceived) << std::endl<<"> ";
		}
	} while (bytesReceived >= 0);
}

void CtcpClient::Send()
{
	std::string msg;
	do
	{
		std::cout << "> ";
		getline(std::cin, msg);

		if (msg.size() > 0)
		{
			send(_serverSocket, msg.c_str(), msg.size() + 1, 0);
		}
	} while (msg.size() > 0);
}

void CtcpClient::cleanUp()
{
	closesocket(_serverSocket);
	WSACleanup();
}

