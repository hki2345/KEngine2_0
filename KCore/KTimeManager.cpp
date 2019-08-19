#include "KTimeManager.h"



KTimeManager::KTimer::KTimer()
{

}
KTimeManager::KTimer::~KTimer()
{

}



void KTimeManager::KTimer::start()
{
	QueryPerformanceFrequency(&CpuFrequency);

	// ����Ÿ�� 
	QueryPerformanceCounter(&CurCount);
	Accumule_Time = 0;
	FPSCount = 0;
}

void KTimeManager::KTimer::accumulate()
{
	// ��ŸŸ���� ���Ѵ�.
	QueryPerformanceCounter(&NextCount);

	DeltaTime = ((float)(NextCount.QuadPart - CurCount.QuadPart)) / ((float)CpuFrequency.QuadPart);
	CurCount.QuadPart = NextCount.QuadPart;


	// FPS ��� 1�ʴ� ������ ��...
	Accumule_Time += DeltaTime;

	++FPSCount;

	if (1.0f <= Accumule_Time)
	{
		Fps = ((float)FPSCount / Accumule_Time);
		Accumule_Time = 0.0f;
		FPSCount = 0;
	}
}





void KTimeManager::init()
{

}