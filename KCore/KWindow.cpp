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

	WndClass.cbClsExtra = 0; // 여분 메모리
	WndClass.cbWndExtra = 0; // 여분 메모리
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // 맨 뒤를 칠할 색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 모양
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 왼쪽 귀퉁이 아이콘
	WndClass.hInstance = KWindowManager::hinstance(); // 인스턴스
	WndClass.lpfnWndProc = this->WndProc; // 프로시져 함수 포인터
	WndClass.lpszClassName = KName::name().c_str(); // 윈도우 이름
	WndClass.lpszMenuName = NULL; // 메뉴 있게 할 거냐
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // 창크기 변할때 그릴거냐

	RegisterClass(&WndClass);

	hWnd = CreateWindow(
		KName::name().c_str(), KName::name().c_str(), WS_OVERLAPPEDWINDOW,
		// 띄우는 위치 - 크기
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
	//	InvalidateRect(hWnd, NULL, FALSE); // 무효화 영역 - 갱신해라 영역(?)
	//	// 실제로는 무효화를 하는 역할은 아니고 메시지가 있을 떄 무효화 시켜주는 겻 다시 찾아봐ㅠㅠㅠ

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


// rx반지름, ry 반지름
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