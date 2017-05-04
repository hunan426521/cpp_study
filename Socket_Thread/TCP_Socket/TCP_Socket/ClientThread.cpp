#include "stdafx.h"
#include "ClientThread.h"


ClientThread::ClientThread(void *pPM)
{
	int nThreadNum = *(int *)pPM;
	SetEvent(ThreadEvent); //触发事件  

	Sleep(50);//some work should to do  

	EnterCriticalSection(&csThreadCode);
	g_nNum++;
	Sleep(0);//some work should to do  
	printf("线程编号为%d  全局资源值为%d\n", nThreadNum, g_nNum);
	LeaveCriticalSection(&g_csThreadCode);
	return 0;

}


ClientThread::~ClientThread()
{
}
