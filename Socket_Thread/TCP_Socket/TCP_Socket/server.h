#pragma once

#include <stdio.h>
#include <Windows.h>

#pragma comment (lib,"ws2_32.lib")


class server
{
public:
	server();
	//初始化服务器,返回0表示成功
	int Init(const char* address, int port);

	//更新数据
	void Run();
	~server();

private:
	SOCKET m_sock;
};

