#pragma once
#include <crtdbg.h>
#include <Windows.h>
#include "KVector.h"
#include "KDebugManager.h"


class KUpdater;
class KCore
{
private:
	// ��ü������ �ؾ��ϴϱ�
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
	// �ֿܼ� ���� �� ����
	void init(int argc, wchar_t* argv[])
	{
		KCore::init();
	}

	// �ֿܼ� ���� 1ȸ ����
	template <typename INIT>
	void init(int argc, wchar_t* argv[])
	{
		KCore::init();

		INIT OneInit;
		OneInit.init();
	}

	// ������� ������
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

	// ������� ������ - �̹� �ִ� �����쿡 ���� �뵵
	void init(HWND _hWnd, const KSize2& _Size = KSize2::Zero);


	// �ֽ�ȭ
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

	// �ֽ�ȭ �� �ʱ�ȭ
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

	// �ھ� �ֽ�ȭ ������ �ִ� ��� �� �ƴѰ��...
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
// ���� �ܰ� ������
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

// ���� �ܰ� �ϳ� ���� �� �ֽ�ȭ
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


// ���� �ܰ� �ϳ� ���� �� �ֽ�ȭ
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