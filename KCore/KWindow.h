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


	static void DrawCircle(HDC hdc, int _x, int _y, int _rX, int _rY);
	static void DrawLine(HDC hdc, int x1, int y1, int x2, int y2);

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

