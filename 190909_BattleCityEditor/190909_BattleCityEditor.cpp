// 190909_BattleCityEditor.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "header.h"
#include "190909_BattleCityEditor.h"
#include <BattleTile.h>
#include "afxdialogex.h"

#include <KResourceManager.h>
#include <KFileStream.h>
#include <KWindowManager.h>
#include <KInputManager.h>

#include <KBitMap_Render.h>
#include <KOne.h>
#include <KBitMap.h>
#include <crtdbg.h>
#include <vector>


#if _DEBUG
#if Win32
#pragma comment(lib, "KCore_Debug32")
#elif x64
#pragma comment(lib, "KCore_Debug64")
#endif // WIN32

#else
#if Win32
#pragma comment(lib, "KCore_Release32")
#elif x64
#pragma comment(lib, "KCore_Release64")
#endif
#endif




#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

std::vector<BATTLETILE_INFO> VectorTank;
std::vector<KOne*> VectorOneMap;
std::vector<KBitMap_Render*> VectorBitMap;


BATTLECITY_TILE eCurTile = BATTLECITY_TILE::BROWN_BLOCK00; 
KPos2 CurPos = KPos2::Zero;

const int XSize = 10;
const int YSize = 10;



HDC hMainDC;
HDC hBackDC;
HWND hWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



void create_map();
void release_map();
void input_key();
void reset_render();


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	new int;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtSetBreakAlloc(3446);


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY190909BATTLECITYEDITOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY190909BATTLECITYEDITOR));

    MSG msg;

	KPathManager::instance()->init();
	KWindowManager::instance()->create_window(hWnd);
	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KBitMap>::instance()->load_forder(L"BattleCity");

	create_map();

	hMainDC = GetDC(hWnd);
	hBackDC = CreateCompatibleDC(hMainDC); 
	
	HBITMAP MyBitMap = CreateCompatibleBitmap(hMainDC, 800, 600);
	//HBITMAP OldBitmap = (HBITMAP)SelectObject(hBackDC, MyBitMap);
	//BITMAP	BitMapData;
	// GetObjectW(MyBitMap, sizeof(BITMAP), &BitMapData);

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
		input_key();
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY190909BATTLECITYEDITOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY190909BATTLECITYEDITOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("Load"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 800, 500, 100, 25, hWnd, (HMENU)0, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Save"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 920, 500, 100, 25, hWnd, (HMENU)1, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Reset"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 500, 100, 25, hWnd, (HMENU)2, hInst, NULL);


		CreateWindow(TEXT("button"), TEXT("Brown Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 25, 100, 25, hWnd, (HMENU)3, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Brown Block01"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 55, 100, 25, hWnd, (HMENU)4, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Brown Block02"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 85, 100, 25, hWnd, (HMENU)5, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Brown Block03"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 115, 100, 25, hWnd, (HMENU)6, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Brown Block04"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 145, 100, 25, hWnd, (HMENU)7, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Metal Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 175, 100, 25, hWnd, (HMENU)8, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Wood Block"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 205, 100, 25, hWnd, (HMENU)9, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Water Block"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 235, 100, 25, hWnd, (HMENU)10, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Stone Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 265, 100, 25, hWnd, (HMENU)11, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Stone Block01"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 295, 100, 25, hWnd, (HMENU)12, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Stone Block02"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 325, 100, 25, hWnd, (HMENU)13, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Stone Block03"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 355, 100, 25, hWnd, (HMENU)14, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Phoenix Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 385, 100, 25, hWnd, (HMENU)15, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Spawn Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, 1040, 415, 100, 25, hWnd, (HMENU)16, hInst, NULL);

		SetTimer(hWnd, 1, 10, NULL);
		return 0;

    case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
		{
			//TCHAR BASED_CODE szFilter[] = _T("STATE 파일(*.State) | *.STATE;*.state; |모든파일(*.*)|*.*||");

			//CFileDialog dlg(TRUE, _T("*.STATE"), _T("*.state"), OFN_HIDEREADONLY, szFilter, this);

			//if (IDOK == dlg.DoModal())
			//{
			//	// 한번에 불러오려는 포스 ->
			//	// 이 좌표 다음이 바로 다음 선택한 파일의 패스를 나타냄
			//	CString pathName = dlg.GetFileTitle();
			//}
			//else
			//{
			//	return;
			//}

			wchar_t arr[256];
			HANDLE hHandle = CreateFile(L"로드창", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
			memset(arr, 0, sizeof(arr));

			ReadFile(hHandle, arr, 256 * sizeof(wchar_t), 0, NULL);
			break;
		}
		case 1:
		{
			MessageBox(hWnd, TEXT("Second Button Clicked"), TEXT("Button"), MB_OK);
		}
			break;
		case 2:
		{
			MessageBox(hWnd, TEXT("Third Button Clicked"), TEXT("Button"), MB_OK);
		}
			break;


		default:
			eCurTile = BATTLECITY_TILE((wParam) - 3);
			break;
		}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			for (size_t i = 0; i < VectorBitMap.size(); i++)
			{
				VectorBitMap[i]->render(hdc);
			}
			EndPaint(hWnd, &ps);
        }
        break;

	case WM_TIMER:
		// BitBlt(hMainDC, 0, 0, 800, 600, hBackDC, 0, 0, SRCCOPY);
		// Rectangle(hBackDC, 0, 0, 800, 600);
		InvalidateRect(hWnd, NULL, false);
		break;
    case WM_DESTROY:
		release_map();
		KFileStream::instance()->release();
		KPathManager::instance()->release();
		KWindowManager::instance()->release();
		KInputManager::instance()->release();
		KResourceManager<KBitMap>::instance()->release();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void create_map()
{
	for (size_t y = 0; y < YSize; y++)
	{
		for (size_t x = 0; x < XSize; x++)
		{
			BATTLETILE_INFO Tmp;
			Tmp.x = x;
			Tmp.y = y;
			Tmp.Idx = BATTLECITY_TILE::BROWN_BLOCK00;
			VectorTank.push_back(Tmp);

			VectorOneMap.push_back(new KOne());
			VectorOneMap[x + (y * XSize)]->create();
			VectorOneMap[x + (y * XSize)]->pos({ x * 50.0f, y* 50.0f });
			VectorOneMap[x + (y * XSize)]->size({ 50.0f, 50.0f });

			VectorBitMap.push_back(VectorOneMap[x + (y * XSize)]->add_component<KBitMap_Render>());
			VectorBitMap[x + (y * XSize)]->init();
			VectorBitMap[x + (y * XSize)]->set_noscenebit(L"BattleCity\\block00.bmp");
		}
	}
}

void release_map()
{
	for (size_t i = 0; i < VectorOneMap.size(); i++)
	{
		VectorOneMap[i]->release();
		delete VectorOneMap[i];
	}
	VectorTank.clear();
	VectorBitMap.clear();
}

void input_key()
{
	if (true == KInputManager::instance()->is_down(VK_LEFT))
	{
		if (CurPos.x - 1 >= 0)
		{
			CurPos.x -= 1;
		}
	}
	else if (true == KInputManager::instance()->is_down(VK_RIGHT))
	{
		if (CurPos.x - 1 <= XSize - 1)
		{
			CurPos.x += 1;
		}
	}
	else if (true == KInputManager::instance()->is_down(VK_UP))
	{
		if (CurPos.y - 1 >= 0)
		{
			CurPos.y -= 1;
		}
	}
	else if (true == KInputManager::instance()->is_down(VK_DOWN))
	{
		if (CurPos.y + 1 <= YSize - 1)
		{
			CurPos.y += 1;
		}
	}
	else if (true == KInputManager::instance()->is_down(VK_SPACE))
	{
		VectorTank[CurPos.x + XSize * CurPos.y].Idx = eCurTile;
		reset_render();
	}
	else if (true == KInputManager::instance()->is_down(VK_ESCAPE))
	{
		KFileStream::instance()->write_file(L"Test.btd", VectorTank);
		reset_render();
	}
	else if (true == KInputManager::instance()->is_down(VK_BACK))
	{
		KFileStream::instance()->read_file(L"Test.btd", VectorTank);
		reset_render();
	}
}


void reset_render()
{
	for (size_t i = 0; i < VectorTank.size(); i++)
	{
		switch (VectorTank[i].Idx)
		{
		case BROWN_BLOCK00:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block00.bmp");
			break;
		case BROWN_BLOCK01:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block01.bmp");
			break;
		case BROWN_BLOCK02:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block02.bmp");
			break;
		case BROWN_BLOCK03:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block03.bmp");
			break;
		case BROWN_BLOCK04:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block04.bmp");
			break;
		case METAL_BLOCK00:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block05.bmp");
			break;
		case WOOD_BLOCK00:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block06.bmp");
			break;
		case WATER_BLOCK00:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block07.bmp");
			break;
		case STONE_BLOCK00:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block09.bmp");
			break;
		case STONE_BLOCK01:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block10.bmp");
			break;
		case STONE_BLOCK02:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block11.bmp");
			break;
		case STONE_BLOCK03:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block12.bmp");
			break;
		case PHOENIX_BLOCK00:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\block13.bmp");
			break;
		case SPAWN_BLOCK00:
			VectorBitMap[i]->set_noscenebit(L"BattleCity\\shield_00.bmp");
			break;
		case BC_BLOCKNUM:
			break;
		default:
			break;
		}
	}
}
