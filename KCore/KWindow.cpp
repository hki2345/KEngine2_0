#include "KWindow.h"
#include "KWindowManager.h"
#include "KCore.h"

#include <vector>
#include <KPathManager.h>
#include <KMacro.h>

#include "KSceneManager.h"
#include "KTimeManager.h"


#include <KResourceManager.h>
#include "KBitMap.h"

KWindow::KWindow() : BackBitMap(nullptr)
{
}


KWindow::~KWindow()
{
}

void KWindow::init()
{
	if (nullptr == BackBitMap)
	{
		BackBitMap = KResourceManager<KBitMap>::instance()->load(L"KCore", L"BackBuffer");
		hBackDC = BackBitMap->kwindow_size(MyWinSize);
	}

	KSceneManager::instance()->kwindow(this);
	KSceneManager::instance()->init();

	BackColor = RGB(0, 0, 0);
}

void KWindow::update()
{
	if (TRUE == PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	else
	{
		KTimeManager::instance()->update();
		KSceneManager::instance()->update();
	}
}


void KWindow::render()
{
	KSceneManager::instance()->render();
	BitBlt(hMainDC, 0, 0, (int)MyWinSize.x, (int)MyWinSize.y, hBackDC, 0, 0, SRCCOPY);
	// InvalidateRect(mhWnd, NULL, FALSE);
	
	// Rectangle(hBackDC, 0, 0, (int)MyWinSize.x, (int)MyWinSize.y);

	// 검은색 색칠
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	myBrush = CreateSolidBrush(BackColor);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hBackDC, myBrush);
	Rectangle(hBackDC, 0, 0, (int)MyWinSize.x, (int)MyWinSize.y);
	SelectObject(hBackDC, oldBrush);
	DeleteObject(myBrush);
}

void KWindow::release()
{
	KSceneManager::instance()->release();
}




int KWindow::create()
{

	WndClass.cbClsExtra = 0; // 여분 메모리
	WndClass.cbWndExtra = 0; // 여분 메모리
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // 맨 뒤를 칠할 색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 모양
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 왼쪽 귀퉁이 아이콘
	WndClass.hInstance = KWindowManager::hinstance(); // 인스턴스
	WndClass.lpfnWndProc = this->WndProc; // 프로시져 함수 포인터
	WndClass.lpszClassName = KName::sName.c_str(); // 윈도우 이름
	WndClass.lpszMenuName = NULL; // 메뉴 있게 할 거냐
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // 창크기 변할때 그릴거냐

	RegisterClass(&WndClass);

	mhWnd = CreateWindow(
		KName::sName.c_str(), KName::sName.c_str(), WS_OVERLAPPEDWINDOW,
		// 띄우는 위치 - 크기
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, KWindowManager::hinstance(), NULL);


	RECT rc;
	GetClientRect(mhWnd, &rc);

	MyWinSize.x = (float)rc.right;
	MyWinSize.y = (float)rc.bottom;

	hMainDC = GetDC(mhWnd);

	return (int)Message.wParam;
}



BOOL KWindow::show_window()
{
	return ShowWindow(mhWnd, KWindowManager::cmdshow());
}



LRESULT CALLBACK KWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		MoveWindow(hWnd, 100, 100, 800, 600, TRUE);
		break;
	}
	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = 800;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = 600;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 800;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 600;

		return FALSE;
	}
	case WM_DESTROY:
		KCore::instance()->shut_down();
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}