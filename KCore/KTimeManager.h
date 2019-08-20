#pragma once
#include <Windows.h>
#include <map>
#include "KProgress.h"
#include "KName.h"



class KTimeManager
{
public:
	friend class KCore;

private:
	KTimeManager() : MainTimer(nullptr) {} /* = delete*/;
	KTimeManager(const KTimeManager& _Core) = delete;
	KTimeManager(const KTimeManager&& _Core) = delete;
	void operator=(const KTimeManager& _Core) = delete;
	~KTimeManager() {};

	static KTimeManager* pKTimeManager;

public:
	static KTimeManager* instance()
	{
		if (nullptr == pKTimeManager)
		{
			pKTimeManager = new KTimeManager();
		}

		return pKTimeManager;
	}
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
	KTimer* MainTimer;
	std::map<std::wstring, KTimer*> MapActingTimer;
	std::map<std::wstring, KTimer*> MapPauseTimer;



	std::map<std::wstring, KTimer*>::iterator mSTimer;
	std::map<std::wstring, KTimer*>::iterator mETimer;
	std::map<std::wstring, KTimer*>::iterator mFTimer;

private:
	void init();
	void update();
	void release();

	
	
	KTimeManager::KTimer* find_ActingTimer(const wchar_t* _Name);
	KTimeManager::KTimer* find_PauseTimer(const wchar_t* _Name);


public:
	float& fps()
	{
		return MainTimer->Fps;
	}
	
	float& deltatime()
	{
		return MainTimer->DeltaTime;
	}

	float& accumulate()
	{
		return MainTimer->AccumulateTime;
	}
	
	float& fps(const wchar_t* _Name);
	float& deltatime(const wchar_t* _Name);
	

	KTimeManager::KTimer* create_timer(const wchar_t* _Name);
	KTimeManager::KTimer* find_timer(const wchar_t* _Name);

	bool start_timer(const wchar_t* _Name);
	bool stop_timer(const wchar_t* _Name);
	bool erase_timer(const wchar_t* _Name);
};

