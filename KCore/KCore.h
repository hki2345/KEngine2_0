#pragma once
#include <crtdbg.h>


class KUpdater;
class KCore
{
private:
	// ��ü������ �ؾ��ϴϱ�
	KCore() {} /* = delete*/;
	KCore(const KCore& _Core) = delete;
	KCore(const KCore&& _Core) = delete;
	void operator=(const KCore& _Core) = delete;
	~KCore() = delete;
	

private:
	static KUpdater* pUpdater;
	static bool looping;


private:
	int main(int argc, char* argv[]) {};
	static void init();
	static void release();

public:
	// ���� �� ����
	static void init(int argc, char* argv[])
	{
		KCore::init();
	}

	// ���� 1ȸ ����
	template <typename INIT>
	static void init(int argc, char* argv[])
	{
		INIT OneInit;
		OneInit.init();
		
		KCore::init();
	}

	template <typename UP>
	static void loop()
	{
		pUpdater = new UP;
		if (nullptr == pUpdater)
		{
			return;
		}

		loop_updater();
	}

	// �ھ� ������Ʈ�� ������ ��� �� �ƴѰ��...
	static void loop();
	static void loop_updater();

	static void shut_down();
private:
	static void progress();
};



// ���� �ܰ�� ������ �� �ѹ��� ����� �ֽ�ȭ�� ������ ���ش�.
// ��� Ƚ���� ����;; �׳� ���� ���� ����
// ���� �ܰ� �ϳ� ����
template<typename INIT>
int core_launch(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	KCore::init<INIT>(argc, argv);
	KCore::loop();
	return 0;
}


// ���� �ܰ� �ϳ� ���� �� �ֽ�ȭ
template<typename INIT,  typename UP>
int core_launch(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	KCore::init<INIT>(argc, argv);
	KCore::loop<UP>();
	return 0;
}