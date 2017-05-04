#include "stdafx.h"
#include "client.h"
#include <iostream>
using namespace std;


client::client()
{
}


client::~client()
{
	closesocket(m_sock);
}


int  client::Connect(int port, const char* address)
{
	int rlt = 0;
	int ierror;

	WSAData wsadata;    //启动Winsock
	ierror = WSAStartup(MAKEWORD(1, 1), &wsadata);
	if (ierror != NO_ERROR)
	{
		cout << "failed with wsastartup error :" << ierror << endl;
		rlt = 1;
		return rlt;
	}

	m_sock = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);     //创建socket
	if (m_sock == INVALID_SOCKET)
	{
		cout << "socket failed with error :" << WSAGetLastError() << endl;
		rlt = 2;
		return rlt;
	}
	//目标服务器数据
	sockaddr_in sockaddrServer;
	sockaddrServer.sin_family = AF_INET;
	sockaddrServer.sin_port = port;
	sockaddrServer.sin_addr.s_addr = inet_addr(address);

	//连接目标服务器
	ierror = connect(m_sock, (sockaddr*)&sockaddrServer, sizeof(sockaddrServer));
	if (ierror < 0)
	{
		cout << "connect failed with error :" << ierror << endl;

		rlt = 3;
		return rlt;
	}

	return rlt;
}

int client::Sendmsg(const char* msg, int len)
{
	int rlt = 0;

	int ierror = 0;

	//发送消息，指定sock发送消息
	ierror = send(m_sock, msg, len, 0);
	if (ierror < 0)
		//发送失败
	{
		cout << "send msg failed with error :" << ierror << endl;

		rlt = 1;
		return rlt;
	}

	return rlt;
}


void client::Close()
{
	closesocket(m_sock);
}