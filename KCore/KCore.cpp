#include "KMacro.h"
#include "KCore.h"
#include "KUpdater.h"
#include "KPathManager.h"
#include "KInputManager.h"
#include "KSceneManager.h"



#include <crtdbg.h>


KUpdater* KCore::pUpdater = nullptr;
bool KCore::looping = true;

void KCore::init()
{
	KPathManager::init();
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





#include <Windows.h>
void KCore::progress()
{
	KSceneManager::update();
}

void KCore::release()
{
	KSceneManager::release();
}