#pragma once
#include <map>
#include <Windows.h>


class KWindow;
class KWindowManager
{
public:
	KWindowManager() {} /* = delete*/;;
	KWindowManager(const KWindowManager& _Window) = delete;
	KWindowManager(const KWindowManager&& _Window) = delete;
	void operator=(const KWindowManager& _Window) = delete;
	~KWindowManager() {} ;

	
public:
	static KWindowManager* pKWindowManager;

public:
	friend class KCore;

private:
	std::map<std::wstring, KWindow*> MapWindow;
	static _In_ HINSTANCE hInst ;
	static _In_ LPWSTR   WCmdLine;
	static _In_ int      iCmdShow;


private:
	static bool init(
		_In_ HINSTANCE _hInstance,
		_In_ LPWSTR    _lpCmdLine,
		_In_ int       _nCmdShow);
	void update();
	void release();

	
	int create_window(const wchar_t* _Name);

public:
	HDC main_hdc();
	HWND main_hwnd();

	static KWindowManager* instance()
	{
		if (nullptr == pKWindowManager)
		{
			pKWindowManager = new KWindowManager();
		}

		return pKWindowManager;
	}
	static HINSTANCE& hinstance()
	{
		return hInst;
	}
	static int& cmdshow()
	{
		return iCmdShow;
	}
};

