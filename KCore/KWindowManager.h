#pragma once
#include <map>
#include <Windows.h>
#include "KVector.h"


class KWindow;
class KWindowManager
{
private:
	KWindowManager() {} /* = delete*/;;
	KWindowManager(const KWindowManager& _Window) = delete;
	KWindowManager(const KWindowManager&& _Window) = delete;
	void operator=(const KWindowManager& _Window) = delete;
	~KWindowManager() {} ;
	static KWindowManager* pKWindowManager;

public:
	friend class KCore;

public:
	static KWindowManager* instance()
	{
		if (nullptr == pKWindowManager)
		{
			pKWindowManager = new KWindowManager();
		}

		return pKWindowManager;
	}


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

	void init();

public:
	void update();
	void release();
	int create_window(const wchar_t* _Name);
	int create_window(HWND _Name, const KSize2& _Size = KSize2::Zero);
	
public:
	void backcolor(const COLORREF& _Color);

public:
	static inline HINSTANCE& hinstance()
	{
		return hInst;
	}
	static inline int& cmdshow()
	{
		return iCmdShow;
	}
	HDC& back_hdc();
	HDC& main_hdc();
	HWND& main_hwnd();
	KSize2& main_size();
};

