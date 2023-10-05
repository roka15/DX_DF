// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Editor_Window.h"
#include "..\Engine_Source\Application.h"
#include "..\\Editor_Source\\TileMapToolApplication.h"
#include "..\Engine\LoadScene.h"
#include "..\Engine_Source\Input.h"
#include "..\\Engine_Source\\SceneManager.h"
#include "guiEditor.h"
#include "DontDestroyOnLoad.h"
roka::Application application;
roka::TileMapToolApplication tileMapTool;
roka::Application* applications[(UINT)roka::enums::EApplicationType::End];
roka::Application* focusApp = nullptr;

roka::DontDestroyOnLoad* M_DotDestroyObj = roka::DontDestroyOnLoad::GetInstance();

#ifdef _DEBUG
#pragma comment(lib, "..\\Libraries\\Debug\\Engine.lib")
#else
#pragma comment(lib, "..\\Libraries\\Debug\\Engine.lib")
#endif

#define MAX_LOADSTRING 100
#define ID_TILELISTBOX 1
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HWND TileToolHwnd;
// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
BOOL                CreateTileMapToolWindow(HWND, HINSTANCE);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    TileMapToolWndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(42274);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}


	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

	MSG msg;
	DWORD timeDuration = 0;
	DWORD beforeTime = 0;
	DWORD curTime;
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			curTime = timeGetTime();
			timeDuration += curTime - beforeTime;
			beforeTime = curTime;
			if (timeDuration < 1000 / 60)
			{
				continue;
			}
			timeDuration = 0;
			HWND focus = GetFocus();
			if (focus != NULL)
			{
				if (focus == application.GetHwnd())
					focusApp = &application;
				else if (focus == tileMapTool.GetHwnd())
					focusApp = &tileMapTool;
			}
			
			// 여기서 게임 로직이 돌아가야한다.
			application.Run();
			if (application.IsEditObjRener() == true)
				gui::Editor::Run();
			if (focusApp == &application)
				gui::Editor::DebugRender();
			application.Present();
			tileMapTool.Run();
			if (focusApp == &tileMapTool)
				gui::Editor::DebugRender();
			tileMapTool.Present();
		}
	}
	application.Release();
	gui::Editor::Release();
	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_EDITORWINDOW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	applications[0] = &application;
	application.SetWindow(hWnd, 0, 0, 1600, 900);
	float bgColor[4] = { 0.3f,0.74f,0.88f,1.0f };
	application.SetWindowBGColor(bgColor);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	application.Initialize();
	roka::InitializeScenes();
	gui::Editor::Initialize();

	return TRUE;
}
BOOL CreateTileMapToolWindow(HWND parent, HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_TILEMAPTOOLWINDOW);
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.lpfnWndProc = TileMapToolWndProc;
	wcex.lpszClassName = TEXT("TileMapToolWindow");

	RegisterClassExW(&wcex);

	int width = applications[0]->GetWidth();
	TileToolHwnd = CreateWindowEx(0, TEXT("TileMapToolWindow"), TEXT("TileMapToolWindow"), WS_OVERLAPPEDWINDOW,
		width, 0, 500, 500, nullptr, nullptr, hInstance, nullptr);


	applications[1] = &tileMapTool;
	tileMapTool.SetWindow(TileToolHwnd, width, 0, 500, 500);
	float bgColor[4] = { 0.03f,0.03f,0.18f,1.0f };
	tileMapTool.SetWindowBGColor(bgColor);
	tileMapTool.Initialize();

	ShowWindow(TileToolHwnd, SW_HIDE);
	//UpdateWindow(TileToolHwnd);


	if (!TileToolHwnd)
	{
		return FALSE;
	}

	return TRUE;
}
//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_TileMapTool:
			if (applications[(UINT)roka::enums::EApplicationType::TileTool] == nullptr)
			{
				CreateTileMapToolWindow(applications[(UINT)roka::enums::EApplicationType::Main]->GetHwnd(), hInst);
			}
			applications[(UINT)roka::enums::EApplicationType::TileTool]->SetActive(true);
			ShowWindow(TileToolHwnd, SW_SHOWNORMAL);
			roka::SceneManager::LoadScene(L"TileMapToolScene");
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
		roka::Input::SetMouseState(roka::EMouseBtnType::LEFT, roka::EKeyState::Down);
		break;
	case WM_LBUTTONUP:
		roka::Input::SetMouseState(roka::EMouseBtnType::LEFT, roka::EKeyState::Up);
		break;
	case WM_RBUTTONDOWN:
		roka::Input::SetMouseState(roka::EMouseBtnType::RIGHT, roka::EKeyState::Down);
		break;
	case WM_RBUTTONUP:
		roka::Input::SetMouseState(roka::EMouseBtnType::RIGHT, roka::EKeyState::Up);
		break;
	case WM_MOUSEWHEEL:
		roka::Input::SetMouseState(roka::EMouseBtnType::WHEEL, roka::EKeyState::Scroll, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK TileMapToolWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_NextSeriaRoom:
			roka::SceneManager::LoadScene(L"SeriaGateScene");
			ShowWindow(TileToolHwnd, SW_HIDE);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
		roka::Input::SetMouseState(roka::EMouseBtnType::LEFT, roka::EKeyState::Down);
		break;
	case WM_LBUTTONUP:
		roka::Input::SetMouseState(roka::EMouseBtnType::LEFT, roka::EKeyState::Up);
		break;
	case WM_RBUTTONDOWN:
		roka::Input::SetMouseState(roka::EMouseBtnType::RIGHT, roka::EKeyState::Down);
		break;
	case WM_RBUTTONUP:
		roka::Input::SetMouseState(roka::EMouseBtnType::RIGHT, roka::EKeyState::Up);
		break;
	case WM_MOUSEWHEEL:
		roka::Input::SetMouseState(roka::EMouseBtnType::WHEEL, roka::EKeyState::Scroll, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
