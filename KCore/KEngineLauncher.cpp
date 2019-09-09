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
//	// 위에껀 업데이터까지 장착 - 루프 돌때마다 업데이터까지 실행 된다.
//	// 단, 많이쓰진 않을듯
//	// core_launch<KEngineinitiator, KEngineUpdater>(argc, argv);
//	core_launch<KEngineinitiator>(argc, argv);
//	return 0;
//}