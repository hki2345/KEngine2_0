#include "KEngineinitiator.h"
#include "KSceneManager.h"


KEngineinitiator::KEngineinitiator()
{
}


KEngineinitiator::~KEngineinitiator()
{
	int a = 0;
}


void KEngineinitiator::init()
{
	KSceneManager::instance()->create_scene(L"Test");
	KSceneManager::instance()->change_scene(L"Test");

	return;
}

