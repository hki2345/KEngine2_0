#include "KMacro.h"
#include "KCore.h"
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

	release();
}

void KCore::loop_updater()
{

	while (looping)
	{
		pUpdater->update();
		progress();
	}

	RELEASE_PTR(pUpdater);
	release();
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

void KCore::release()
{
	KSceneManager::release();
}