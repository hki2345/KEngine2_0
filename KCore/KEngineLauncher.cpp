#include "KEngineinitiator.h"
#include "KEngineUpdater.h"



int main(int argc, char* argv[])
{
	// 위에껀 업데이터까지 장착 - 루프 돌때마다 업데이터까지 실행 된다.
	// 단, 많이쓰진 않을듯
	// core_launch<KEngineinitiator, KEngineUpdater>(argc, argv);
	core_launch<KEngineinitiator>(argc, argv);
	return 0;
}