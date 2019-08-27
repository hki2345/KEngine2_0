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

	WndClass.cbClsExtra = 0; // ���� �޸�
	WndClass.cbWndExtra = 0; // ���� �޸�
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �� �ڸ� ĥ�� ��
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ�� ���
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ���� ������ ������
	WndClass.hInstance = hInstance; // �ν��Ͻ�
	WndClass.lpfnWndProc = WndProc; // ���ν��� �Լ� ������
	WndClass.lpszClassName = lpszClass; // ������ �̸�
	WndClass.lpszMenuName = NULL; // �޴� �ְ� �� �ų�
	WndClass.style = CS_HREDRAW | CS_VREDRAW; // âũ�� ���Ҷ� �׸��ų�

	RegisterClass(&WndClass);

	hWnd = CreateWindow(
		lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		// ���� ��ġ - ũ��
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
	LPCTSTR str = TEXT("���� �����ϴ�. �ƾ� ����ϴ� ���� ���� �����ϴ�. Ǫ�� ����� "
		"��ġ�� ��ǳ���� ���� ���Ͽ� �� ���� ���� �ɾ ���� ��ġ�� �����ϴ�."
		"Ȳ���� �ɰ��� ���� ������ �� �ͼ��� ������ Ƽ���� �Ǿ� �Ѽ��� ��ǳ�� "
		"���ư����ϴ�.");

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
		InvalidateRect(hWnd, NULL, FALSE); // ��ȿȭ ���� - �����ض� ����(?)
		// �����δ� ��ȿȭ�� �ϴ� ������ �ƴϰ� �޽����� ���� �� ��ȿȭ �����ִ� �� �ٽ� ã�ƺ��ФФ�

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


// rx������, ry ������
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
//	// ������ �������ͱ��� ���� - ���� �������� �������ͱ��� ���� �ȴ�.
//	// ��, ���̾��� ������
//	// core_launch<KEngineinitiator, KEngineUpdater>(argc, argv);
//	core_launch<KEngineinitiator>(argc, argv);
//	return 0;
//}