// 190919OhmokServer.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "header.h"
#include "190919OhmokClient.h"


#include <KCore.h>
#include <KResourceManager.h>
#include <KFileStream.h>
#include <KWindowManager.h>
#include <KSceneManager.h>
#include <KScene.h>

#include <KInputManager.h>
#include <KSprite_Render.h>
#include <KSprite_Animator.h>
#include <KOne.h>
#include <KBitMap.h>
#include <crtdbg.h>
#include <vector>

#include "OhmokManager.h"


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

HDC hMainDC;
HDC hBackDC;
HWND hWnd;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
#if _DEBUG
	new int;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY190919OHMOKCLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY190919OHMOKCLIENT));

    MSG msg;


	KPathManager::instance()->init();
	KCore::instance()->init(hWnd);
	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KBitMap>::instance()->load_forder(L"res");
	hMainDC = KWindowManager::instance()->main_hdc();
	hBackDC = KWindowManager::instance()->back_hdc();

	OhmokManager::instance()->create();


    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_MY190919OHMOKCLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
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
	{
		
		SetTimer(hWnd, 1, 10, NULL);
		MoveWindow(hWnd, 100, 100, WINXSIZE, WINYSIZE, TRUE);
		return 0;
	}

	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WINXSIZE;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WINYSIZE;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WINXSIZE;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WINYSIZE;

		return FALSE;
	}	
	case WM_TIMER:
	{
		OhmokManager::instance()->update();
		KWindowManager::instance()->update();
		break;
	}

    case WM_DESTROY:

		KPathManager::instance()->release();
		OhmokManager::instance()->release();
		KCore::instance()->release();
		KResourceManager<KBitMap>::instance()->release();
        PostQuitMessage(0);
        break;


    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}