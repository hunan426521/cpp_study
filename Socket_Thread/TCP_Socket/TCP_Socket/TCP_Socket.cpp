// TCP_Socket.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "client.h"
#include <stdlib.h>
#include <process.h>
#include <Windows.h>
#include <string.h>

unsigned int __stdcall ClientThread(void *pPM);

int main()
{
	//HANDLE ThreadEvent;
	HANDLE handle[4];
	int i = 0;
	while (i < 4)
	{
		handle[i] = (HANDLE)_beginthreadex(NULL, 0, ClientThread, &i, 0, NULL);
		i++;
		Sleep(1000);
	}
	WaitForMultipleObjects(4, handle, TRUE, INFINITE);

	system("pause");
	return 0;
	
	
	
}




unsigned int __stdcall ClientThread(void *pPM)
{
	client client1;
	int seq = *(int *)pPM;
	printf("client %d send msg \n", seq);
	char *seq1 = (char *)pPM;
	//char *seq1="";
	//_itoa_s(seq, seq1, 10, 10);
	char buf[64] = "";
	char *msg = "hello I'm";
	strcpy_s(buf, msg);
	strcat_s(buf, seq1);

	//���ӵ�127.0.0.1�������أ�,�˿ں�Ϊ8888�ķ����
	printf("Connect\n");
	client1.Connect(8888, "127.0.0.1");

	while (1) {
		//������Ϣ
		printf("client %d send msg \n", seq);
		client1.Sendmsg(buf, sizeof(buf));
		Sleep(3000);
	}
	//�ر�socket
	printf("close\n");
	client1.Close();


	system("pause");
	return 0;

}