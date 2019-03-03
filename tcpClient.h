#pragma once

#include<WS2tcpip.h>
#include<string>

#pragma comment (lib, "ws2_32.lib")

#define MAX_BUFFER_SIZE (32)

class CtcpClient
{
	std::string _ipAddress;
	int			_port;
	SOCKET		_serverSocket;

public:
	CtcpClient(std::string ipAddress, int port);

	~CtcpClient();

	bool Init();

	bool Connect();

	void Recv();

	void Send();

	void cleanUp();
};