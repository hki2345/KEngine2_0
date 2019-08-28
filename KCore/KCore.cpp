#include "KMacro.h"
#include "KCore.h"
#include "KUpdater.h"

#include <KResourceManager.h>
#include <KPathManager.h>


#include "KWindowManager.h"
#include "KInputManager.h"
#include "KSceneManager.h"
#include "KTimeManager.h"


#if _DEBUG
#if Win32
#pragma comment(lib, "KContainer_Debug32")
#elif x64
#pragma comment(lib, "KContainer_Debug64")
#endif // WIN32

#else
#if Win32
#pragma comment(lib, "KContainer_Release32")
#elif x64
#pragma comment(lib, "KContainer_Release64")
#endif
#endif


KCore* KCore::pKCore = nullptr;



void KCore::init()
{
	KSceneManager::instance()->init();
	KPathManager::instance()->init();
	KTimeManager::instance()->init();
}

void KCore::init(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	KWindowManager::instance()->init(_hInstance, _lpCmdLine, _nCmdShow);

	KPathManager::instance()->init();
	KTimeManager::instance()->init();

	KWindowManager::instance()->create_window(L"Main");
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
	KTimeManager::instance()->update();
	KWindowManager::instance()->update();
}

void KCore::release()
{
	KPathManager::instance()->release();
	KTimeManager::instance()->release();
	KInputManager::instance()->release();
	KWindowManager::instance()->release();
	RELEASE_PTR(pKCore);
}