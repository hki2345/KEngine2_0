#pragma once
#include <crtdbg.h>


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
	// ���� �� ����
	void init(int argc, char* argv[])
	{
		KCore::init();
	}

	// ���� 1ȸ ����
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
int core_launch(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop();
	return 0;
}


// ���� �ܰ� �ϳ� ���� �� �ֽ�ȭ
template<typename INIT,  typename UP>
int core_launch(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	new int;
	KCore::instance()->init<INIT>(argc, argv);
	KCore::instance()->loop<UP>();
	return 0;
}