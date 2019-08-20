#pragma once
#include <Windows.h>
#include <map>



class KTimeManager
{
public:
	friend class KCore;

private:
	KTimeManager() {} /* = delete*/;	
	KTimeManager(const KTimeManager& _Core) = delete;
	KTimeManager(const KTimeManager&& _Core) = delete;
	void operator=(const KTimeManager& _Core) = delete;
	~KTimeManager() = delete;

private:
	class KTimer 
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

	private:
		LARGE_INTEGER CpuFrequency;
		LARGE_INTEGER CurCount;
		LARGE_INTEGER NextCount;

		float DeltaTime;
		float AccumulateTime;
		float AccCal_Time;
		float Fps;
		int FPSCount;
	};

private:
	static KTimer* MainTimer;
	static std::map<std::wstring, KTimer*> MapActingTimer;
	static std::map<std::wstring, KTimer*> MapPauseTimer;



	static std::map<std::wstring, KTimer*>::iterator mSTimer;
	static std::map<std::wstring, KTimer*>::iterator mETimer;
	static std::map<std::wstring, KTimer*>::iterator mFTimer;

public:
	static void init();
	static void update();
	static void release();

	
	
	static KTimeManager::KTimer* find_ActingTimer(const wchar_t* _Name);
	static KTimeManager::KTimer* find_PauseTimer(const wchar_t* _Name);


public:
	static float& fps()
	{
		return MainTimer->Fps;
	}
	
	static float& deltatime()
	{
		return MainTimer->DeltaTime;
	}

	static float& accumulate()
	{
		return MainTimer->AccumulateTime;
	}
	
	static float& fps(const wchar_t* _Name);
	static float& deltatime(const wchar_t* _Name);
	

	static KTimeManager::KTimer* create_timer(const wchar_t* _Name);
	static KTimeManager::KTimer* find_timer(const wchar_t* _Name);

	static bool start_timer(const wchar_t* _Name);
	static bool stop_timer(const wchar_t* _Name);
	static bool erase_timer(const wchar_t* _Name);
};

