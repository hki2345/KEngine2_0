#include "KWindowManager.h"
#include "KSceneManager.h"
#include "KWindow.h"

#include "KMacro.h"

KWindowManager* KWindowManager::pKWindowManager = nullptr;


_In_ HINSTANCE KWindowManager::hInst = NULL;
_In_ LPWSTR    KWindowManager::WCmdLine = nullptr;
_In_ int       KWindowManager::iCmdShow = 0;

bool KWindowManager::init(
	_In_ HINSTANCE _hInstance,
	_In_ LPWSTR    _lpCmdLine,
	_In_ int       _nCmdShow)
{
	hInst = _hInstance;
	WCmdLine = _lpCmdLine;
	iCmdShow = _nCmdShow;

	KSceneManager::instance()->init();
	return true;
}


void KWindowManager::update()
{
	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->update();
	}

	KSceneManager::instance()->update();
}


void KWindowManager::release()
{
	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();

	for (; SIter != EIter; ++SIter)
	{
		RELEASE_PTR(SIter->second);
	}

	MapWindow.clear();
	KSceneManager::instance()->release();

	RELEASE_PTR(pKWindowManager);
}



int KWindowManager::create_window(const wchar_t* _Name)
{
	KWindow* NewWindow = new KWindow();
	NewWindow->name(_Name);
	NewWindow->create();
	NewWindow->show_window();
	MapWindow.insert(std::make_pair(_Name, NewWindow));

	return true;
}