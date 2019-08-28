#pragma once
#include <crtdbg.h>
#include <Windows.h>

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

	static KCore* pKCore;

public:
	static KCore* instance()
	{
		if (nullptr == pKCore)
		{
			pKCore = new KCore();
		}

		return pKCore;
	}

private:
	KUpdater* pUpdater;
	bool looping;


public:
	int main(int argc, wchar_t*argv[]) {};
	void init(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow);
	void init();
	void release();

public:
	// 실행 자 없음
	void init(int argc, wchar_t* argv[])
	{
		KCore::init();
	}

	// 최초 1회 실행
	template <typename INIT>
	void init(int argc, wchar_t* argv[])
	{
		INIT OneInit;
		OneInit.init();
		
		KCore::init();
	}

	// 윈도우용 실행자
	template <typename INIT>
	void init(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow)
	{
		INIT OneInit;
		OneInit.init();

		KCore::init(_hInstance, _lpCmdLine, _nCmdShow);
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
int core_launch(int argc, wchar_t* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop();
	return 0;
}

// 엔진 단계 하나 실행 및 최신화
template<typename INIT,  typename UP>
int core_launch(int argc, wchar_t* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop<UP>();
	return 0;
}


/******************** Window ********************/
template<typename INIT>
int core_launch(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	KCore::instance()->init<INIT>(_hInstance, _lpCmdLine, _nCmdShow);
	KCore::instance()->loop();
	return 0;
}

// 엔진 단계 하나 실행 및 최신화
template<typename INIT, typename UP>
int core_launch(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	KCore::instance()->init<INIT>(_hInstance, _lpCmdLine, _nCmdShow);
	KCore::instance()->loop<UP>();
	return 0;
}