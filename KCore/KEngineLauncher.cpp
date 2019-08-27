#include "KEngineinitiator.h"
#include "KEngineUpdater.h"
#include <KPathManager.h>

#include <Windows.h>
#include <math.h>
#include <vector>

#include "KCore.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("First");

struct LineInfo
{
	int ox;
	int oy;
	int tx;
	int ty;
};

std::vector<LineInfo> g_VecHDC;

void DrawCircle(HDC hdc, int _x, int _y, int _rX, int _rY);
void DrawLine(HDC hdc, int x1, int y1, int x2, int y2);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;

	g_hInst = hInstance;

	WndClass.cbClsExtra = 0; // 여분 메모리
	WndClass.cbWndExtra = 0; // 여분 메모리
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 맨 뒤를 칠할 색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서 모양
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 왼쪽 귀퉁이 아이콘
	WndClass.hInstance = hInstance; // 인스턴스
	WndClass.lpfnWndProc = WndProc; // 프로시져 함수 포인터
	WndClass.lpszClassName = lpszClass; // 윈도우 이름
	WndClass.lpszMenuName = NULL; // 메뉴 있게 할 거냐
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // 창크기 변할때 그릴거냐

	RegisterClass(&WndClass);

	hWnd = CreateWindow(
		lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		// 띄우는 위치 - 크기
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);

	KCore::instance()->init();
	ShowWindow(hWnd, nCmdShow);

	// core_launch<KEngineinitiator>(nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt = { 100, 100, 400, 300 };
	LPCTSTR str = TEXT("님은 갔습니다. 아아 사랑하는 나의 님은 갔습니다. 푸른 산빛을 "
		"깨치고 단풍나무 숲을 향하여 난 작은 길을 걸어서 차마 떨치고 갔습니다."
		"황금의 꽃같이 굳고 빛나던 옛 맹세는 차디찬 티끌이 되어 한숨의 미풍에 "
		"날아갔습니다.");

	static TCHAR Tstr[256] = { 0, };
	static int x = 100;
	static int y = 100;

	static int mx;
	static int my;
	static BOOL bNowDraw = FALSE;
	int len = 0;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, 200, 100, 800, 300);
		Ellipse(hdc, 200, 100, 800, 300);
		DrawLine(hdc, 200, 200, 500, 100);
		DrawLine(hdc, 200, 200, 500, 300);
		DrawLine(hdc, 500, 100, 800, 200);
		DrawLine(hdc, 500, 300, 800, 200);

		DrawCircle(hdc, 500, 500, 300, 400);
		TextOut(hdc, 100, 100, Tstr, lstrlen(str));

		TextOut(hdc, x, y, TEXT("A"), 1);

		for (size_t i = 0; i < g_VecHDC.size(); i++)
		{
			DrawLine(hdc, g_VecHDC[i].ox, g_VecHDC[i].oy, g_VecHDC[i].tx, g_VecHDC[i].ty);
		}

		TextOutW(hdc, 1000, 400, KPathManager::instance()->all_path().c_str(), KPathManager::instance()->all_path().size());
		EndPaint(hWnd, &ps);
		return 0;
	case WM_CHAR:
		len = lstrlen(Tstr);
		Tstr[len] = (TCHAR)wParam;
		Tstr[len + 1] = 0;
		InvalidateRect(hWnd, NULL, FALSE); // 무효화 영역 - 갱신해라 영역(?)
		// 실제로는 무효화를 하는 역할은 아니고 메시지가 있을 떄 무효화 시켜주는 겻 다시 찾아봐ㅠㅠㅠ

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			x -= 8;
			break;
		case VK_RIGHT:
			x += 8;
			break;
		case VK_UP:
			y -= 8;
			break;
		case VK_DOWN:
			y += 8;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		bNowDraw = TRUE;
		return 0;
	case WM_MOUSEMOVE:
		if (bNowDraw == TRUE)
		{
			LineInfo Tmp;

			hdc = GetDC(hWnd);
			MoveToEx(hdc, mx, my, NULL);
			Tmp.ox = mx;
			Tmp.oy = my;

			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			Tmp.tx = mx;
			Tmp.ty = my;

			LineTo(hdc, mx, my);
			g_VecHDC.push_back(Tmp);

			ReleaseDC(hWnd, hdc);
		}
		return 0;

	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		return 0;
	}
	return (DefWindowProc(hWnd, message, wParam, lParam));
}


void DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}


// rx반지름, ry 반지름
void DrawCircle(HDC hdc, int _x, int _y, int _rX, int _rY)
{
	int TX = _x;
	int TY = _y;


	float PI = 3.14f;


	for (size_t i = 0; i < 360; i++)
	{
		DrawLine(hdc,
			(int)(TX + cosf(i * PI / 180) * _rX), (int)(TX + sinf(i * PI / 180) * _rY),
			(int)(TX + cosf((i + 1) * PI / 180) * _rX), (int)(TY + sinf((i + 1) * PI / 180)* _rY));
		// DrawLine(hdc, _x, _y, TX + sinf(i * PI / 180) * _rX, TY + cosf(i * PI / 180)* _rY);
		// SetPixel(hdc, TX + sinf(i * PI / 180) * _rX, TY + cosf(i * PI / 180)* _rY, RGB(1,1,1));
	}
}


//int main(int argc, char* argv[])
//{
//	// 위에껀 업데이터까지 장착 - 루프 돌때마다 업데이터까지 실행 된다.
//	// 단, 많이쓰진 않을듯
//	// core_launch<KEngineinitiator, KEngineUpdater>(argc, argv);
//	core_launch<KEngineinitiator>(argc, argv);
//	return 0;
//}