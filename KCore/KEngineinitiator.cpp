#include "KEngineinitiator.h"
#include "KSceneManager.h"


#include "SceneTest.h"


KEngineinitiator::KEngineinitiator()
{
}


KEngineinitiator::~KEngineinitiator()
{
	int a = 0;
}


bool KEngineinitiator::init()
{
	SceneTest* NSCENE = new SceneTest();
	
	KSceneManager::instance()->create_scene(NSCENE, L"Test");
	KSceneManager::instance()->change_scene(L"Test");

	return true;
}

