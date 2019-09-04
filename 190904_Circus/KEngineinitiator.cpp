#include "KEngineinitiator.h"
#include "KSceneManager.h"
#include "GameManager.h"



#include <KResourceManager.h>
#include "KBitMap.h"

#include "SceneTest.h"
#include "SceneTest2.h"

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
	KResourceManager<KBitMap>::instance()->create(L"", L"Test.bmp");
	
	
	GameManager::instance()->init();
	return true;
}

