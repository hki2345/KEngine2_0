#include "KEngineinitiator.h"
#include "KEngineUpdater.h"



int main(int argc, char* argv[])
{
	// ������ �������ͱ��� ���� - ���� �������� �������ͱ��� ���� �ȴ�.
	// ��, ���̾��� ������
	// core_launch<KEngineinitiator, KEngineUpdater>(argc, argv);
	core_launch<KEngineinitiator>(argc, argv);
	return 0;
}