#pragma once
#include <Windows.h>
#include "KName.h"


class KWindow : public KName
{
public:
	KWindow();
	~KWindow();

public:
	friend class KWindowManager;


private:
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;

private:
	void update();

public:
	int create();
	BOOL show_window();

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


	static void DrawCircle(HDC hdc, int _x, int _y, int _rX, int _rY);
	static void DrawLine(HDC hdc, int x1, int y1, int x2, int y2);
};

