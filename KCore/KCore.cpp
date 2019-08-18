#include "KCore.h"
#include "KTemp.h"
#include "KUpdater.h"
#include "KSceneManager.h"



#include <crtdbg.h>


KUpdater* KCore::pUpdater = nullptr;
bool KCore::looping = true;

void KCore::init()
{
	KSceneManager::init();
}

void KCore::loop()
{
	while (looping)
	{
		progress();
	}
}

void KCore::loop_updater()
{

	while (looping)
	{
		pUpdater->update();
		progress();
	}

	release_ptr(pUpdater);
}

void KCore::shut_down()
{
	looping = false;
}






void KCore::progress()
{
	KSceneManager::update();
	KCore::shut_down();
}