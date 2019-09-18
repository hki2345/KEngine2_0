#pragma once
#include <Windows.h>
#include "KVector.h"
#include "KName.h"



class KBitMap;
class KWindow : public KName
{
public:
	KWindow();
	~KWindow();

public:
	friend class KWindowManager;


private:
	KVec2 MyWinSize;
	MSG Message;
	HDC hMainDC;
	HDC hBackDC;

	HWND mhWnd;
	WNDCLASS WndClass;
	KBitMap* BackBitMap;
	
	COLORREF BackColor;

private:
	void init();
	void update();
	void render();
	void release();
	int create();

public:
	BOOL show_window();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


public:
	inline KSize2& size()
	{
		return MyWinSize;
	}
	inline HDC& bhdc()
	{
		return hBackDC;
	}
	inline HDC& hdc()
	{
		return hMainDC;
	}
	inline HWND& hwnd()
	{
		return mhWnd;
	}
};

