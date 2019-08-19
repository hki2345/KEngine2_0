#pragma once
class KTimeManager
{
private:
	KTimeManager() {} /* = delete*/;
	KTimeManager(const KTimeManager& _Core) = delete;
	KTimeManager(const KTimeManager&& _Core) = delete;
	void operator=(const KTimeManager& _Core) = delete;
	~KTimeManager() = delete;

private:
	class Timer
	{
	public:
		Timer() {};
		~Timer() {};

	private:

	};


private:
	static void init();
};

