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

	// 누적타임 
	QueryPerformanceCounter(&CurCount);
	Accumule_Time = 0;
	FPSCount = 0;
}

void KTimeManager::KTimer::accumulate()
{
	// 델타타임을 구한다.
	QueryPerformanceCounter(&NextCount);

	DeltaTime = ((float)(NextCount.QuadPart - CurCount.QuadPart)) / ((float)CpuFrequency.QuadPart);
	CurCount.QuadPart = NextCount.QuadPart;


	// FPS 계산 1초당 프레임 수...
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