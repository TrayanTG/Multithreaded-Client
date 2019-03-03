#include<iostream>
#include<string>
#include<utility>
#include<thread>
#include<chrono>

#include "tcpClient.h"

int main()
{
	CtcpClient client("95.111.75.172", 28199);
	if (client.Init() && client.Connect())
	{
		std::thread recvThread(&CtcpClient::Recv, &client);recvThread.detach();
		std::thread sendThread(&CtcpClient::Send, &client);sendThread.detach();
	}
	while (true);
}