#pragma once

#include <stdio.h>
#include <Windows.h>

#pragma comment (lib,"ws2_32.lib")


class server
{
public:
	server();
	//��ʼ��������,����0��ʾ�ɹ�
	int Init(const char* address, int port);

	//��������
	void Run();
	~server();

private:
	SOCKET m_sock;
};

