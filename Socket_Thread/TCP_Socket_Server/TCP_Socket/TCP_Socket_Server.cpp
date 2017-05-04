// TCP_Socket.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//��ʼ���¼��͹ؼ��� �Զ���λ
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
		//������Ϣ
		newSocket = accept(server1.m_sock, (sockaddr*)&tcpAddr, &len);
		if (newSocket == INVALID_SOCKET)
		{
			//�ǿ���socket

		}
		else
		{
			//��socket����
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

	SetEvent(ThreadEvent); //�����¼� 
	
	if (rval == SOCKET_ERROR)
		//��Ӧ���Ǹ��쳣�����ͻ���û�е���closeSocket��ֱ���˳���Ϸ��ʱ�򣬽����������
		printf("recv socket error\n");

	if (rval == 0)
		//recv����0��ʾ�����˳�
		printf("ending connection");
	else {
		//��ʾ���յ�������
		printf("recv %s\n", buf);
		strcat_s(buf, "ack");
		int ret = send(plist.socket, buf, sizeof(buf), 0);
	}
	Sleep(500);

	EnterCriticalSection(&csThread);
	Globalnum++;
	Sleep(100);
	printf("�ͻ����̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", plist.i, Globalnum);
	LeaveCriticalSection(&csThread);


	//system("pause");
	return 0;

}