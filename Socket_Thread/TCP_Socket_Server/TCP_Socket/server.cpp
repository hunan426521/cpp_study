#include "stdafx.h"
#include "server.h"
#include <string.h>


server::server()
{
}


server::~server()
{
	//�ر������Socket
	closesocket(m_sock);
}


int server::Init(const char* address, int port)
{
	int rlt = 0;

	//���ڼ�¼������Ϣ�������
	int iErrorMsg;

	//��ʼ��WinSock
	WSAData wsaData;
	iErrorMsg = WSAStartup(MAKEWORD(1, 1), &wsaData);

	if (iErrorMsg != NO_ERROR)
	{
		//��ʼ��WinSockʧ��
		printf("wsastartup failed with error : %d\n", iErrorMsg);

		rlt = 1;
		return rlt;
	}

	//���������Socket
	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock == INVALID_SOCKET)

	{
		//����Socket�쳣
		printf("socket failed with error : %d\n", WSAGetLastError());

		rlt = 2;
		return rlt;
	}

	//������Ϣ
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = port;
	serverAddr.sin_addr.s_addr = inet_addr(address);

	//��
	iErrorMsg = bind(m_sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (iErrorMsg < 0)
	{
		//��ʧ��
		printf("bind failed with error : %d\n", iErrorMsg);
		rlt = 3;
		return rlt;
	}

	//��������
	listen(m_sock, 5);


	return rlt;
}

void server::Run()
{

	sockaddr_in tcpAddr;
	int len = sizeof(sockaddr);
	SOCKET newSocket;
	char buf[1024];
	int rval;

	do
	{
		//������Ϣ
		newSocket = accept(m_sock, (sockaddr*)&tcpAddr, &len);


		if (newSocket == INVALID_SOCKET)
		{
			//�ǿ���socket

		}
		else
		{
			//��socket����
			printf("new socket connect : %d\n", newSocket);


			//��Ϣ����
			do
			{
				printf("process\n");
				//��������
				memset(buf, 0, sizeof(buf));
				rval = recv(newSocket, buf, 1024, 0);


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
					int ret = send(newSocket, buf, sizeof(buf), 0);
				}

			} while (rval != 0);

			//�رն�ӦAccept��socket
			closesocket(newSocket);
		}



	} while (1);

	//�ر������Socket
	closesocket(m_sock);
}
