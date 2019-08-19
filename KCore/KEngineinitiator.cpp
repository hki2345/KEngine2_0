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
	KSceneManager::create_scene(L"Test");
	KSceneManager::change_scene(L"Test");

	return;
}

