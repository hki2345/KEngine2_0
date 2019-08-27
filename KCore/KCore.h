#pragma once
#include <crtdbg.h>


class KUpdater;
class KCore
{
private:
	// 본체에서는 해야하니까
	KCore() :looping(true), pUpdater(nullptr) {} /* = delete*/;
	KCore(const KCore& _Core) = delete;
	KCore(const KCore&& _Core) = delete;
	void operator=(const KCore& _Core) = delete;
	~KCore() {};

	static KCore* pKParse;

public:
	static KCore* instance()
	{
		if (nullptr == pKParse)
		{
			pKParse = new KCore();
		}

		return pKParse;
	}

private:
	KUpdater* pUpdater;
	bool looping;
private:
	int main(int argc, char* argv[]) {};
	void init();
	void release();

public:
	// 실행 자 없음
	void init(int argc, char* argv[])
	{
		KCore::init();
	}

	// 최초 1회 실행
	template <typename INIT>
	void init(int argc, char* argv[])
	{
		INIT OneInit;
		OneInit.init();
		
		KCore::init();
	}

	template <typename UP>
	void loop()
	{
		pUpdater = new UP;
		if (nullptr == pUpdater)
		{
			return;
		}

		loop_updater();
	}

	// 코어 업데이트를 실행할 경우 와 아닌경우...
	void loop();
	void loop_updater();

	void shut_down();
private:
	void progress();
};



// 엔진 단계는 구조상 단 한번만 실행과 최신화를 엑세스 해준다.
// 사실 횟수는 ㅋㅋ;; 그냥 내가 정함 ㅋㅋ
// 엔진 단계 하나 실행
template<typename INIT>
int core_launch(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop();
	return 0;
}


// 엔진 단계 하나 실행 및 최신화
template<typename INIT,  typename UP>
int core_launch(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop<UP>();
	return 0;
}