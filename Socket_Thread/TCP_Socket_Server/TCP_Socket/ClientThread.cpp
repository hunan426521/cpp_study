#include "stdafx.h"
#include "ClientThread.h"


ClientThread::ClientThread(void *pPM)
{
	int nThreadNum = *(int *)pPM;
	SetEvent(ThreadEvent); //�����¼�  

	Sleep(50);//some work should to do  

	EnterCriticalSection(&csThreadCode);
	g_nNum++;
	Sleep(0);//some work should to do  
	printf("�̱߳��Ϊ%d  ȫ����ԴֵΪ%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);
	return 0;

}


ClientThread::~ClientThread()
{
}
