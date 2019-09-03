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
	KVec2 vSize;
	MSG Message;
	HDC hMainDC;
	HDC hBackDC;

	HWND hWnd;
	WNDCLASS WndClass;
	KBitMap* BackBitMap;
	

private:
	void init();
	void update();
	void render();
	void release();

public:
	int create();
	BOOL show_window();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


public:
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
		return hWnd;
	}
};

