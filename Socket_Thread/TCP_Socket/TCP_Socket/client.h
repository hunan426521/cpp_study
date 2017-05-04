#pragma once

#include <stdio.h>
#include <Windows.h>

#pragma comment(lib, "Ws2_32.lib")

class client
{
public:
	client();
	int Connect(int port, const char* address); 
	int Sendmsg(const char* msg, int len);
	void Close();
	~client();
private:
	SOCKET m_sock;
};

