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
		BackBitMap = KResourceManager<KBitMap>::instance()->create(L"KCore", L"BackBuffer");
		hBackDC = BackBitMap->kwindow_size(vSize);
	}

	KSceneManager::instance()->kwindow(this);
	KSceneManager::instance()->init();
}

void KWindow::update()
{
	if (TRUE == PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	KTimeManager::instance()->update();
	KSceneManager::instance()->update();
}


void KWindow::render()
{
	KSceneManager::instance()->render();
	BitBlt(hMainDC, 0, 0, (int)vSize.x, (int)vSize.y, hBackDC, 0, 0, SRCCOPY);
	// InvalidateRect(mhWnd, NULL, FALSE);


	// ������ ��ĥ
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	myBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hBackDC, myBrush);
	Rectangle(hBackDC, 0, 0, (int)vSize.x, (int)vSize.y);
	SelectObject(hBackDC, oldBrush);
	DeleteObject(myBrush);
}

void KWindow::release()
{
	KSceneManager::instance()->release();
}




int KWindow::create()
{

	WndClass.cbClsExtra = 0; // ���� �޸�
	WndClass.cbWndExtra = 0; // ���� �޸�
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // �� �ڸ� ĥ�� ��
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���� ������ ������
	WndClass.hInstance = KWindowManager::hinstance(); // �ν��Ͻ�
	WndClass.lpfnWndProc = this->WndProc; // ���ν��� �Լ� ������
	WndClass.lpszClassName = KName::name().c_str(); // ������ �̸�
	WndClass.lpszMenuName = NULL; // �޴� �ְ� �� �ų�
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // âũ�� ���Ҷ� �׸��ų�

	RegisterClass(&WndClass);

	mhWnd = CreateWindow(
		KName::name().c_str(), KName::name().c_str(), WS_OVERLAPPEDWINDOW,
		// ���� ��ġ - ũ��
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, KWindowManager::hinstance(), NULL);


	RECT rc;
	GetClientRect(mhWnd, &rc);

	vSize.x = (float)rc.right;
	vSize.y = (float)rc.bottom;

	hMainDC = GetDC(mhWnd);
	// hBackDC = ;


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