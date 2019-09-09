#include "KWindowManager.h"
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
	return true;
}

void KWindowManager::init()
{
	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->init();
	}
}


void KWindowManager::update()
{
	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->update();

		// Ãæµ¹ ¾îÂ¼±¸ ;;
		SIter->second->render();
	}
}


void KWindowManager::release()
{
	std::map<std::wstring, KWindow*>::iterator SIter = MapWindow.begin();
	std::map<std::wstring, KWindow*>::iterator EIter = MapWindow.end();

	for (; SIter != EIter; ++SIter)
	{
		SIter->second->release();
		RELEASE_PTR(SIter->second);
	}

	MapWindow.clear();
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

int KWindowManager::create_window(HWND _Name)
{
	KWindow* NewWindow = new KWindow();
	NewWindow->hMainDC = GetDC(_Name);
	NewWindow->hBackDC = NewWindow->hMainDC;
	NewWindow->mhWnd = _Name;
	MapWindow.insert(std::make_pair(L"Custom", NewWindow));

	return 0;
}

HDC& KWindowManager::back_hdc()
{
	return MapWindow.begin()->second->bhdc();
}
HDC& KWindowManager::main_hdc()
{
	return MapWindow.begin()->second->hdc();
}
HWND& KWindowManager::main_hwnd()
{
	return MapWindow.begin()->second->hwnd();
}