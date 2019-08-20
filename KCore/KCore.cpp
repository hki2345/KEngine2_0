#include "KMacro.h"
#include "KCore.h"
#include "KUpdater.h"

#include <KResourceManager.h>
#include "KPathManager.h"
#include "KInputManager.h"
#include "KSceneManager.h"
#include "KTimeManager.h"



#include <crtdbg.h>


KUpdater* KCore::pUpdater = nullptr;
bool KCore::looping = true;

void KCore::init()
{
	KPathManager::init();
	KTimeManager::init();
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





#include <iostream>
void KCore::progress()
{
	// system("cls");
	KSceneManager::update();
	KTimeManager::update();
	// KInputManager::update('0');


	std::cout << KTimeManager::accumulate() << std::endl;
	std::cout << KTimeManager::deltatime() << std::endl;
	std::cout << KTimeManager::fps() << std::endl;
}

void KCore::release()
{
	KSceneManager::release();
	KTimeManager::release();
}