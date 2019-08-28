#include "KEngineinitiator.h"
#include "KSceneManager.h"


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
	SceneTest* NSCENE = new SceneTest();
	SceneTest2* NSCENE2 = new SceneTest2();
	
	KSceneManager::instance()->create_scene(NSCENE, L"Test");
	KSceneManager::instance()->create_scene(NSCENE2, L"Test2");
	KSceneManager::instance()->change_scene(L"Test");

	return true;
}

