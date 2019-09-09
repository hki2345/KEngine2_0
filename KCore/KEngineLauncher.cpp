#include "KEngineinitiator.h"
#include "KEngineUpdater.h"
#include <KPathManager.h>

#include <Windows.h>
#include <math.h>
#include <vector>

#include "KCore.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	core_launch<KEngineinitiator>(hInstance, lpCmdLine, nCmdShow);
}

//int main(int argc, wchar_t* argv[])
//{
//	// ������ �������ͱ��� ���� - ���� �������� �������ͱ��� ���� �ȴ�.
//	// ��, ���̾��� ������
//	// core_launch<KEngineinitiator, KEngineUpdater>(argc, argv);
//	core_launch<KEngineinitiator>(argc, argv);
//	return 0;
//}