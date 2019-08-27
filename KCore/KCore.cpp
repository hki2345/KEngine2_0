#include "KMacro.h"
#include "KCore.h"
#include "KUpdater.h"

#include <KResourceManager.h>
#include <KPathManager.h>
#include "KInputManager.h"
#include "KSceneManager.h"
#include "KTimeManager.h"



#if _DEBUG
#if WIN32
#pragma comment(lib, "KContainer_Debug32")
#else
#pragma comment(lib, "KContainer_Debug64")
#endif // WIN32

#else
#if WIN32
#pragma comment(lib, "KContainer_Release32")
#else
#pragma comment(lib, "KContainer_Release64")
#endif
#endif


KCore* KCore::pKParse = nullptr;



void KCore::init()
{
	KPathManager::instance()->init();
	KTimeManager::instance()->init();
	KSceneManager::instance()->init();
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





#include <iostream>
#include <conio.h>
void KCore::progress()
{
	KSceneManager::instance()->update();
	KTimeManager::instance()->update();
	// KInputManager::update('0');

	std::cout << KTimeManager::instance()->accumulate() << std::endl;
	std::cout << KTimeManager::instance()->deltatime() << std::endl;
	std::cout << KTimeManager::instance()->fps() << std::endl;
}

void KCore::release()
{
	KSceneManager::instance()->release();
	KPathManager::instance()->release();
	KTimeManager::instance()->release();
	KInputManager::instance()->release();
	RELEASE_PTR(pKParse);
}