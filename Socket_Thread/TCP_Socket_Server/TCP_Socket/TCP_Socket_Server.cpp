// TCP_Socket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "server.h"
#include <stdlib.h>
#include <process.h>
#include <Windows.h>
#include <string.h>

struct parlist
{
	SOCKET socket;
	int i;
}tparlist;

unsigned int __stdcall ServerThread(void *pPM);
int Globalnum;
HANDLE ThreadEvent;
CRITICAL_SECTION csThread;
int main()
{
	//初始化事件和关键段 自动置位
	ThreadEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	InitializeCriticalSection(&csThread);

	HANDLE handle[7];
	Globalnum = 0;
	int i = 0;

	//parlist *tparlist;
	//tparlist->i = i;
	server server1;
	int srlt = server1.Init("127.0.0.1", 8888);
	if (srlt == 0)
	{
		printf("init ok...\n");
	}
	else
		printf("serverNet init failed with error : %d\n", srlt);

	sockaddr_in tcpAddr;
	int len = sizeof(sockaddr);
	SOCKET newSocket;
	

	while (1)
	{
		//接收信息
		newSocket = accept(server1.m_sock, (sockaddr*)&tcpAddr, &len);
		if (newSocket == INVALID_SOCKET)
		{
			//非可用socket

		}
		else
		{
			//新socket连接
			printf("new socket connect : %d\n", newSocket);
		}

		tparlist.i = i;
		tparlist.socket = newSocket;
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, ServerThread, &tparlist, 0, NULL);
		WaitForSingleObject(ThreadEvent, INFINITE);
		i++;
	}

	WaitForMultipleObjects(4, handle, TRUE, INFINITE);
	CloseHandle(ThreadEvent);
	DeleteCriticalSection(&csThread);

	//system("pause");
	return 0;
	
	
	
}




unsigned int __stdcall ServerThread(void *pPM)
{
	parlist plist = *(parlist *)pPM;
	char buf[1024];
	int rval;

	memset(buf, 0, sizeof(buf));
	rval = recv(plist.socket, buf, 1024, 0);

	SetEvent(ThreadEvent); //触发事件 
	
	if (rval == SOCKET_ERROR)
		//这应该是个异常，当客户端没有调用closeSocket就直接退出游戏的时候，将会进入这里
		printf("recv socket error\n");

	if (rval == 0)
		//recv返回0表示正常退出
		printf("ending connection");
	else {
		//显示接收到的数据
		printf("recv %s\n", buf);
		strcat_s(buf, "ack");
		int ret = send(plist.socket, buf, sizeof(buf), 0);
	}
	Sleep(500);

	EnterCriticalSection(&csThread);
	Globalnum++;
	Sleep(100);
	printf("客户端线程编号为%d  全局资源值为%d\n", plist.i, Globalnum);
	LeaveCriticalSection(&csThread);


	//system("pause");
	return 0;

}