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
	BitBlt(hMainDC, 0, 0, vSize.ix, vSize.iy, hBackDC, 0, 0, SRCCOPY);
	Rectangle(hBackDC, 0, 0, vSize.ix, vSize.iy);
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

	hWnd = CreateWindow(
		KName::name().c_str(), KName::name().c_str(), WS_OVERLAPPEDWINDOW,
		// ���� ��ġ - ũ��
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, KWindowManager::hinstance(), NULL);


	RECT rc;
	GetClientRect(hWnd, &rc);

	vSize.ix = (int)rc.right;
	vSize.iy = (int)rc.bottom;

	hMainDC = GetDC(hWnd);
	// hBackDC = ;


	return (int)Message.wParam;
}



BOOL KWindow::show_window()
{
	return ShowWindow(hWnd, KWindowManager::cmdshow());
}



LRESULT CALLBACK KWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		KCore::instance()->shut_down();
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}