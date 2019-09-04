#include "KEngineinitiator.h"
#include "KSceneManager.h"
#include "GameManager.h"



#include <KResourceManager.h>
#include "KBitMap.h"


KEngineinitiator::KEngineinitiator()
{
}


KEngineinitiator::~KEngineinitiator()
{
	int a = 0;
}


bool KEngineinitiator::init()
{
	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\player0.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back_normal.bmp");
	KResourceManager<KBitMap>::instance()->create(L"", L"Circus\\back_deco.bmp");
	
	
	GameManager::instance()->init();
	return true;
}

