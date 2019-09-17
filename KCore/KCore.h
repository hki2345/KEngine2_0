#pragma once
#include <crtdbg.h>
#include <Windows.h>
#include "KVector.h"
#include "KDebugManager.h"


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
	class KCoreUpdater
	{
	public:
		KCoreUpdater() {};
		~KCoreUpdater() {};

	public:
		virtual void update() {};
	};


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
	KCore::KCoreUpdater* pUpdater;
	bool looping;


private:
	void init(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow);
	void init();
	void release();

public:
	// 콘솔용 실행 자 없음
	void init(int argc, wchar_t* argv[])
	{
		KCore::init();
	}

	// 콘솔용 최초 1회 실행
	template <typename INIT>
	void init(int argc, wchar_t* argv[])
	{
		KCore::init();

		INIT OneInit;
		OneInit.init();
	}

	// 윈도우용 실행자
	template <typename INIT>
	void init(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow)
	{
		KCore::init(_hInstance, _lpCmdLine, _nCmdShow);
		
		INIT OneInit;
		OneInit.init();
	}

	// 윈도우용 실행자 - 이미 있는 윈도우에 띄우는 용도
	void init(HWND _hWnd, const KSize2& _Size = KSize2::Zero);


	// 최신화
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

	// 최신화 및 초기화
	template <typename UP, typename RELEASE>
	void loop()
	{
		pUpdater = new UP;
		if (nullptr == pUpdater)
		{
			return;
		}

		loop_updater();


		RELEASE OneRelease;
		OneRelease.release();
	}

	// 코어 최신화 과정이 있는 경우 와 아닌경우...
	void loop();
	void loop_updater();
	inline void shut_down()
	{
		looping = false;
	}

private:
	void progress();
};



/******************** Console ********************/
// 엔진 단계 실행자
template<typename INIT>
int core_launch(int argc, wchar_t* argv[])
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop();
	return 0;
}

// 엔진 단계 하나 실행 및 최신화
template<typename INIT,  typename UP>
int core_launch(int argc, wchar_t* argv[])
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop<UP>();
	return 0;
}


// 엔진 단계 하나 실행 및 최신화
template<typename INIT, typename UP, typename RELEASE>
int core_launch(int argc, wchar_t* argv[])
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop<UP, RELEASE>();
	return 0;
}



/******************** Window ********************/
template<typename INIT>
int core_launch(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(_hInstance, _lpCmdLine, _nCmdShow);
	KCore::instance()->loop();
	return 0;
}

template<typename INIT, typename UP>
int core_launch(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(_hInstance, _lpCmdLine, _nCmdShow);
	KCore::instance()->loop<UP>();
	return 0;
}


template<typename INIT, typename UP, typename RELEASE>
int core_launch(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{

#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
#endif // _DEBUG

	KCore::instance()->init<INIT>(_hInstance, _lpCmdLine, _nCmdShow);
	KCore::instance()->loop<UP, RELEASE>();
	return 0;
}