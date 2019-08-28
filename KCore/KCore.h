#pragma once
#include <crtdbg.h>
#include <Windows.h>

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
	// ���� �� ����
	void init(int argc, wchar_t* argv[])
	{
		KCore::init();
	}

	// ���� 1ȸ ����
	template <typename INIT>
	void init(int argc, wchar_t* argv[])
	{
		INIT OneInit;
		OneInit.init();
		
		KCore::init();
	}

	// ������� ������
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

	// �ھ� ������Ʈ�� ������ ��� �� �ƴѰ��...
	void loop();
	void loop_updater();

	void shut_down();
private:
	void progress();
};



// ���� �ܰ�� ������ �� �ѹ��� ����� �ֽ�ȭ�� ������ ���ش�.
// ��� Ƚ���� ����;; �׳� ���� ���� ����
// ���� �ܰ� �ϳ� ����
template<typename INIT>
int core_launch(int argc, wchar_t* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop();
	return 0;
}

// ���� �ܰ� �ϳ� ���� �� �ֽ�ȭ
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

// ���� �ܰ� �ϳ� ���� �� �ֽ�ȭ
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