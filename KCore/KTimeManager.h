#pragma once
#include <Windows.h>
#include <map>
#include "KProgress.h"
#include "KName.h"



class KTimeManager
{
private:
	KTimeManager() {} /* = delete*/;
	KTimeManager(const KTimeManager& _Core) = delete;
	KTimeManager(const KTimeManager&& _Core) = delete;
	void operator=(const KTimeManager& _Core) = delete;
	~KTimeManager() = delete;

private:
	class KTimer : public KName
	{
	public:
		friend class KTimeManager;

	private:
		KTimer();
		KTimer(const KTimer& _Core) = delete;
		KTimer(const KTimer&& _Core) = delete;
		void operator=(const KTimer& _Core) = delete;
		~KTimer();

	private:
		void start();
		void accumulate();
		void pause();

	private:
		LARGE_INTEGER CpuFrequency;
		LARGE_INTEGER CurCount;
		LARGE_INTEGER NextCount;

		float DeltaTime;
		float Accumule_Time;
		float Fps;
		int FPSCount;

	public:
		float& fps()
		{
			return Fps;
		}

		float& deltatime()
		{
			return DeltaTime;
		}
	};

private:
	std::map<std::wstring, KTimer*> mTimer;

private:
	static void init();
};

