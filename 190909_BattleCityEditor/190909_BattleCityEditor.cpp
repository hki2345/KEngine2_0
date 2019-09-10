// 190909_BattleCityEditor.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "header.h"
#include "190909_BattleCityEditor.h"
#include <BattleTile.h>

#include <KCore.h>
#include <KResourceManager.h>
#include <KFileStream.h>
#include <KWindowManager.h>
#include <KSceneManager.h>
#include <KScene.h>

#include <KInputManager.h>
#include <KBitMap_Render.h>
#include <KOne.h>
#include <KBitMap.h>
#include <crtdbg.h>
#include <vector>
#include <deque>

#include <CommDlg.h>


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



KScene* EditScene;

std::vector<std::wstring> VectorPath;
std::vector<BATTLETILE_INFO> VectorTank;
std::vector<KOne*> VectorOneMap;
std::vector<KBitMap_Render*> VectorBitMap;

std::vector<KOne*> VectorButtonOneMap;
std::vector<KBitMap_Render*> VectorButtonBitMap;
std::deque<BATTLETILE_INFO> DequeRedoTank;
std::deque<BATTLETILE_INFO> DequeUndoTank;

KOne* CurOneMap;
KBitMap_Render* CurBitMap;


BATTLECITY_TILE CurTileIdx = BATTLECITY_TILE::NONE_BLOCK00; 
KPos2 CurPos = KPos2::Zero;

const int XSize = 13;
const int YSize = 13;
const int ReservationSize = 25;
const int TileSize = 40;
const int StrSize = 512;

const int WinXSize = 800;
const int WinYSize = 800;

wchar_t PathStr[StrSize] = L"므시여";
wchar_t Message[8] = L"빠밤";


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
void reset_tile();


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

	float ScreenSize = 275.0f;
	KCore::instance()->init(hWnd, { (float)WinXSize - ScreenSize, (float)WinYSize - ScreenSize });
	KResourceManager<KBitMap>::instance()->init();
	KResourceManager<KBitMap>::instance()->load_forder(L"BattleCity");

	create_map();

	hMainDC = KWindowManager::instance()->main_hdc();
	hBackDC = KWindowManager::instance()->back_hdc();



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
	{
		int MaxX = 400;
		int MaxY = 650;


		CreateWindow(TEXT("button"), TEXT("Load"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX - 240, MaxY, 100, 25, hWnd, (HMENU)0, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Save"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX - 120, MaxY, 100, 25, hWnd, (HMENU)1, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Reset"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX - 0, MaxY, 100, 25, hWnd, (HMENU)2, hInst, NULL);

		int MaxX2 = 600;
		int Start = 20;
		int Size = 45;
		int idx = -1;
		long long ButtonIdx = 3;

		CreateWindow(TEXT("button"), TEXT("None Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Brown Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Brown Block01"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Brown Block02"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Brown Block03"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Brown Block04"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Metal Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Wood Block"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Water Block"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Stone Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Stone Block01"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Stone Block02"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Stone Block03"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Phoenix Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Spawn Block00"), WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON, MaxX2, Start + Size * ++idx, 100, 25, hWnd, (HMENU)++ButtonIdx, hInst, NULL);

		SetTimer(hWnd, 1, 10, NULL);
		MoveWindow(hWnd, 100, 100, WinXSize, WinYSize, TRUE);
		return 0;
	}
	case WM_GETMINMAXINFO:
	{
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WinXSize;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WinYSize;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WinXSize;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WinYSize;

		return FALSE;
	}

    case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
		{
			OPENFILENAME NewOpen;
			memset(&NewOpen, 0, sizeof(OPENFILENAME));
			NewOpen.lStructSize = sizeof(OPENFILENAME);
			NewOpen.hwndOwner = hWnd;
			NewOpen.lpstrFilter = L"모든 파일 (*.*)\0*.*\0Text File\0*.txt";
			NewOpen.lpstrFile = PathStr;
			NewOpen.nMaxFile = StrSize;
			NewOpen.lpstrInitialDir = KPathManager::instance()->directory().c_str();

			if (GetOpenFileName(&NewOpen))
			{
				wsprintf(Message, L"%s 파일을 선택했습니다.", NewOpen.lpstrFile);
				MessageBox(hWnd, Message, L"불러오기 성공", MB_OK);


				KFileStream::instance()->read_file(NewOpen.lpstrFile, VectorTank);
			}
			else
			{
				MessageBox(hWnd, Message, L"불러오기 실-패", MB_OK);
			}

			break;
		}
		case 1:
		{
			OPENFILENAME NewOpen;
			memset(&NewOpen, 0, sizeof(OPENFILENAME));
			NewOpen.lStructSize = sizeof(OPENFILENAME);
			NewOpen.hwndOwner = hWnd;
			NewOpen.lpstrFilter = L"모든 파일 (*.*)\0*.*\0Text File\0*.txt";
			NewOpen.lpstrFile = PathStr;
			NewOpen.nMaxFile = StrSize;
			NewOpen.lpstrInitialDir = KPathManager::instance()->directory().c_str();

			if (GetSaveFileName(&NewOpen))
			{
				wsprintf(Message, L"%s 파일로 저장합니다.", NewOpen.lpstrFile);
				MessageBox(hWnd, Message, L"저장하기 성공", MB_OK);

				KFileStream::instance()->write_file(NewOpen.lpstrFile, VectorTank);
			}
			else
			{
				MessageBox(hWnd, Message, L"저장하기 실-패", MB_OK);
			}
		}
			break;
		case 2:
		{
			reset_tile();
		}
			break;


		default:
			CurTileIdx = BATTLECITY_TILE((wParam) - 3);
			break;
		}
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		
			EndPaint(hWnd, &ps);
        }
        break;

	case WM_TIMER:	
	{
		reset_render();

		wchar_t Text[64] = L"Current Tile: ";
		TextOutW(hMainDC, CurOneMap->pos().x - 100, CurOneMap->pos().y + 10, Text, lstrlenW(Text));

		KWindowManager::instance()->update();
		
		for (size_t i = 0; i < VectorButtonBitMap.size(); i++)
		{
			VectorButtonBitMap[i]->render(hMainDC);
		}

		Rectangle(hMainDC,
			CurBitMap->kone()->pos().x,
			CurBitMap->kone()->pos().y,
			CurBitMap->kone()->pos().x + CurBitMap->kone()->size().x,
			CurBitMap->kone()->pos().y + CurBitMap->kone()->size().y);
		CurBitMap->render(hMainDC);

		break;
	}
	case WM_DESTROY:
		release_map();
		KFileStream::instance()->release();
		KPathManager::instance()->release();
		KResourceManager<KBitMap>::instance()->release();

		KCore::instance()->release();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void create_map()
{
	VectorPath.push_back(L"BattleCity\\none.bmp");;
	VectorPath.push_back(L"BattleCity\\block00.bmp");
	VectorPath.push_back(L"BattleCity\\block01.bmp");
	VectorPath.push_back(L"BattleCity\\block02.bmp");
	VectorPath.push_back(L"BattleCity\\block03.bmp");
	VectorPath.push_back(L"BattleCity\\block04.bmp");
	VectorPath.push_back(L"BattleCity\\block05.bmp");
	VectorPath.push_back(L"BattleCity\\block06.bmp");
	VectorPath.push_back(L"BattleCity\\block07.bmp");
	VectorPath.push_back(L"BattleCity\\block08.bmp");
	VectorPath.push_back(L"BattleCity\\block09.bmp");
	VectorPath.push_back(L"BattleCity\\block10.bmp");
	VectorPath.push_back(L"BattleCity\\block11.bmp");
	VectorPath.push_back(L"BattleCity\\block12.bmp");
	VectorPath.push_back(L"BattleCity\\block13.bmp");
	VectorPath.push_back(L"BattleCity\\tank_up_01.bmp");


	EditScene = KSceneManager::instance()->create_scene(L"EditScene");
	KSceneManager::instance()->change_scene(L"EditScene");

	for (size_t y = 0; y < YSize; y++)
	{
		for (size_t x = 0; x < XSize; x++)
		{
			BATTLETILE_INFO Tmp;
			Tmp.x = x;	
			Tmp.y = y;
			VectorTank.push_back(Tmp);

			VectorOneMap.push_back(EditScene->create_kone(L"Tile"));
			VectorOneMap[x + (y * XSize)]->create();
			VectorOneMap[x + (y * XSize)]->pos({ x * (float)TileSize, y * (float)TileSize });
			VectorOneMap[x + (y * XSize)]->size(TileSize);

			VectorBitMap.push_back(VectorOneMap[x + (y * XSize)]->add_component<KBitMap_Render>());
			VectorBitMap[x + (y * XSize)]->init();
			VectorBitMap[x + (y * XSize)]->set_bit(VectorPath[0].c_str());
		}
	}


	int XPos = 0;
	int YPos = 0;
	int YSplit = 20;
	for (int i = 0; i < (int)BATTLECITY_TILE::BC_BLOCKNUM; i++)
	{
		VectorButtonOneMap.push_back(EditScene->create_kone(L"Button Tile"));
		VectorButtonOneMap[i]->create();
		VectorButtonOneMap[i]->pos({550.0f + XPos * 100.0f, YPos * ((float)TileSize + 5.0f) + 20.0f});
		VectorButtonOneMap[i]->size(TileSize);

		VectorButtonBitMap.push_back(VectorButtonOneMap[i]->add_component<KBitMap_Render>());
		VectorButtonBitMap[i]->init();
		VectorButtonBitMap[i]->set_bit(VectorPath[i].c_str());
		EditScene->insert_krender(VectorButtonBitMap[i]);

		YPos += 1;

		if (i != 0 && 0 == i % YSplit)
		{
			YPos = 0;
			XPos += 1;
		}
	}

	CurOneMap = EditScene->create_kone(L"Current Tile");
	CurOneMap->create();
	CurOneMap->pos({ 300, 550.0f });
	CurOneMap->size(TileSize);

	CurBitMap = CurOneMap->add_component<KBitMap_Render>();
	CurBitMap->init();
	CurBitMap->set_bit(VectorPath[0].c_str());

	DequeUndoTank.clear();
	DequeRedoTank.clear();

	reset_tile();
}

void release_map()
{
	DequeRedoTank.clear();
	DequeUndoTank.clear();
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
		if (CurPos.x + 1 <= XSize - 1)
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
		if (ReservationSize <= DequeUndoTank.size())
		{
			DequeUndoTank.pop_front();
			DequeUndoTank.push_back(VectorTank[CurPos.x + XSize * CurPos.y]);
		}
		else
		{
			DequeUndoTank.push_back(VectorTank[CurPos.x + XSize * CurPos.y]);
		}
		VectorTank[CurPos.x + XSize * CurPos.y].Idx = CurTileIdx;
	}
	else if (true == KInputManager::instance()->is_press(VK_DELETE))
	{
		if (ReservationSize <= DequeUndoTank.size())
		{
			DequeUndoTank.pop_front();
			DequeUndoTank.push_back(VectorTank[CurPos.x + XSize * CurPos.y]);
		}
		else
		{
			DequeUndoTank.push_back(VectorTank[CurPos.x + XSize * CurPos.y]);
		}
		CurTileIdx = BATTLECITY_TILE::NONE_BLOCK00;
		VectorTank[CurPos.x + XSize * CurPos.y].Idx = CurTileIdx;
	}

	

	else if (true == KInputManager::instance()->is_down(0x51))
	{
		if ((int)CurTileIdx - 1 >= 0)
		{
			CurTileIdx = (BATTLECITY_TILE)((int)CurTileIdx - 1);
		}
	}
	else if (true == KInputManager::instance()->is_down(0x45))
	{
		if ((int)CurTileIdx + 1 < (int)BATTLECITY_TILE::BC_BLOCKNUM)
		{
			CurTileIdx = (BATTLECITY_TILE)((int)CurTileIdx + 1);
		}
	}
	else if (
		true == KInputManager::instance()->is_press(VK_LCONTROL) &&
		true == KInputManager::instance()->is_down(0x4c))
	{
		SendMessage(hWnd, WM_COMMAND, LOWORD(0), LOWORD(0));
	}

	else if (
		true == KInputManager::instance()->is_press(VK_LCONTROL) &&
		true == KInputManager::instance()->is_down(0x53))
	{
		SendMessage(hWnd, WM_COMMAND, LOWORD(1), LOWORD(0));		
	}

	else if (
		true == KInputManager::instance()->is_press(VK_LCONTROL) &&
		true == KInputManager::instance()->is_down(VK_DELETE))
	{
		SendMessage(hWnd, WM_COMMAND, LOWORD(2), LOWORD(0));
	}


	// 앞으로가기
	else if (
		true == KInputManager::instance()->is_press(VK_LCONTROL) &&
		true == KInputManager::instance()->is_press(VK_LSHIFT) &&
		true == KInputManager::instance()->is_down(0x5A))
	{
		if (0 == DequeRedoTank.size())
		{
			return;
		}
		VectorTank[DequeRedoTank.back().x + XSize * DequeRedoTank.back().y].Idx =
			DequeRedoTank.back().Idx;

		DequeUndoTank.push_back(DequeRedoTank.back());
		DequeRedoTank.pop_back();
	}
	// 뒤로가기
	else if (
		true == KInputManager::instance()->is_press(VK_LCONTROL) &&
		true == KInputManager::instance()->is_down(0x5A))
	{
		if (0 == DequeUndoTank.size())
		{
			return;
		}	


		DequeRedoTank.push_back(VectorTank[DequeUndoTank.back().x + XSize * DequeUndoTank.back().y]);
		VectorTank[DequeUndoTank.back().x + XSize * DequeUndoTank.back().y].Idx =
			DequeUndoTank.back().Idx;
		DequeUndoTank.pop_back();
	}

	
}


void reset_render()
{
	for (size_t i = 0; i < VectorTank.size(); i++)
	{
		if (CurPos.x == VectorTank[i].x && CurPos.y == VectorTank[i].y)
		{
			VectorBitMap[i]->change_bit(L"BattleCity\\e_up_00.bmp");
		}
		else
		{
			VectorBitMap[i]->change_bit(VectorPath[(int)VectorTank[i].Idx].c_str());
		}
	}


	CurBitMap->change_bit(VectorPath[(int)CurTileIdx].c_str());
}


void reset_tile()
{
	for (size_t i = 0; i < VectorTank.size(); i++)
	{
		VectorTank[i].Idx = BATTLECITY_TILE::NONE_BLOCK00;
	}

	VectorTank[6 + (YSize - 2) * XSize].Idx = BATTLECITY_TILE::BROWN_BLOCK03;
	VectorTank[5 + (YSize - 1) * XSize].Idx = BATTLECITY_TILE::BROWN_BLOCK04;
	VectorTank[6 + (YSize - 1) * XSize].Idx = BATTLECITY_TILE::PHOENIX_BLOCK00;
	VectorTank[7 + (YSize - 1) * XSize].Idx = BATTLECITY_TILE::BROWN_BLOCK02;
}