#include "KWindow.h"
#include "KWindowManager.h"
#include "KCore.h"

#include <vector>
#include <KResourceManager.h>
#include <KPathManager.h>
#include <KMacro.h>

#include "KSceneManager.h"
#include "KTimeManager.h"


#include "KBitMap.h"

KWindow::KWindow() : BackBitMap(nullptr)
{
}


KWindow::~KWindow()
{
}


struct LineInfo
{
	int ox;
	int oy;
	int tx;
	int ty;
};

std::vector<LineInfo> g_VecHDC;


void KWindow::init()
{
	if (nullptr == BackBitMap)
	{
		BackBitMap = KResourceManager<KBitMap>::create(L"", L"BackBuffer");
		hBackDC = BackBitMap->size(vSize);
	}

	KSceneManager::instance()->init();
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
	BitBlt(hMainDC, 0, 0, vSize.ix, vSize.iy, hBackDC, 0, 0, SRCCOPY);
	Rectangle(hBackDC, 0, 0, vSize.ix, vSize.iy);
}

void KWindow::release()
{
	KSceneManager::instance()->release();
	KResourceManager<KBitMap>::erase(L"BackBuffer");
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
	//case WM_PAINT:
	//{
	//	hdc = BeginPaint(hWnd, &ps);
	//	
	//	for (size_t i = 0; i < g_VecHDC.size(); i++)
	//	{
	//		DrawLine(hdc, g_VecHDC[i].ox, g_VecHDC[i].oy, g_VecHDC[i].tx, g_VecHDC[i].ty);
	//	}

	//	std::wstring FPS = L"FPS: ";
	//	FPS += KTimeManager::instance()->fps_string();

	//	TextOut(hdc, 1000, 600, FPS.c_str(), (int)KTimeManager::instance()->fps_string().size());

	//	FPS = L"Delta: ";
	//	FPS += std::to_wstring(KTimeManager::instance()->deltatime());
	//	TextOut(hdc, 1000, 620, FPS.c_str(), 10);
	//	TextOut(hdc, 1000, 400, KPathManager::instance()->all_path().c_str(), (int)KPathManager::instance()->all_path().size());
	//	InvalidateRect(hWnd, NULL, FALSE);
	//	EndPaint(hWnd, &ps);
	//	return 0;
	//}
	//case WM_CHAR:
	//	len = lstrlen(Tstr);
	//	Tstr[len] = (TCHAR)wParam;
	//	Tstr[len + 1] = 0;
	//	InvalidateRect(hWnd, NULL, FALSE); // ��ȿȭ ���� - �����ض� ����(?)
	//	// �����δ� ��ȿȭ�� �ϴ� ������ �ƴϰ� �޽����� ���� �� ��ȿȭ �����ִ� �� �ٽ� ã�ƺ��ФФ�

	//case WM_KEYDOWN:
	//	switch (wParam) {
	//	case VK_LEFT:
	//		x -= 8;
	//		break;
	//	case VK_RIGHT:
	//		x += 8;
	//		break;
	//	case VK_UP:
	//		y -= 8;
	//		break;
	//	case VK_DOWN:
	//		y += 8;
	//		break;
	//	}
	//	InvalidateRect(hWnd, NULL, TRUE);
	//case WM_LBUTTONDOWN:
	//	mx = LOWORD(lParam);
	//	my = HIWORD(lParam);
	//	bNowDraw = TRUE;
	//	return 0;
	//case WM_MOUSEMOVE:
	//	if (bNowDraw == TRUE)
	//	{
	//		LineInfo Tmp;

	//		hdc = GetDC(hWnd);
	//		MoveToEx(hdc, mx, my, NULL);
	//		Tmp.ox = mx;
	//		Tmp.oy = my;

	//		mx = LOWORD(lParam);
	//		my = HIWORD(lParam);
	//		Tmp.tx = mx;
	//		Tmp.ty = my;

	//		LineTo(hdc, mx, my);
	//		g_VecHDC.push_back(Tmp);

	//		ReleaseDC(hWnd, hdc);
	//	}
	//	return 0;

	//case WM_LBUTTONUP:
	//	bNowDraw = FALSE;
	//	return 0;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}



void KWindow::DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}


// rx������, ry ������
void KWindow::DrawCircle(HDC hdc, int _x, int _y, int _rX, int _rY)
{
	int TX = _x;
	int TY = _y;


	float PI = 3.14f;


	for (size_t i = 0; i < 360; i++)
	{
		DrawLine(hdc,
			(int)(TX + cosf(i * PI / 180) * _rX), (int)(TX + sinf(i * PI / 180) * _rY),
			(int)(TX + cosf((i + 1) * PI / 180) * _rX), (int)(TY + sinf((i + 1) * PI / 180)* _rY));
		// DrawLine(bhdc, _x, _y, TX + sinf(i * PI / 180) * _rX, TY + cosf(i * PI / 180)* _rY);
		// SetPixel(bhdc, TX + sinf(i * PI / 180) * _rX, TY + cosf(i * PI / 180)* _rY, RGB(1,1,1));
	}
}