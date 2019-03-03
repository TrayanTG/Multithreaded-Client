#include<iostream>
#include<string>
#include<thread>

#include "tcpClient.h"

int main()
{
	CtcpClient client("127.0.0.1", 28199);
	if (client.Init() && client.Connect())
	{
		std::thread recvThread(&CtcpClient::Recv, &client);recvThread.detach();
		std::thread sendThread(&CtcpClient::Send, &client);sendThread.detach();
	}
	while (true);
}
