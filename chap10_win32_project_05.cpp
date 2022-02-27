// chap10_win32_project_05.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "chap10_win32_project_05.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Custom Global Variables
HWND hwndList = NULL;
HWND hwndEditDoc = NULL;

// buffer for storing retrieved string
WCHAR szItemText[500];

// buffer of string items list
WCHAR szItem[10][12] = {
	{TEXT("CHAPTER 01")}, {TEXT("CHAPTER 02")}, {TEXT("CHAPTER 03")}, {TEXT("CHAPTER 04")}, {TEXT("CHAPTER 05")},
	{TEXT("CHAPTER 06")}, {TEXT("CHAPTER 07")}, {TEXT("CHAPTER 08")}, {TEXT("CHAPTER 09")}, {TEXT("CHAPTER 10")}
};

// buffer for the description of each item in the list
WCHAR szItemDesc[10][500] = {
	{TEXT("Readers are introduced to the very fundamental elements of C++, such as what variable is,expression,operator,logical expression,conditional expression,logical operator,..Etc")},
	{TEXT("In this chapter, readers get a bit elevated to the next level of the fundamental that introduces what array variable is, what the function is, variable scopes, intellisense,..Etc")},
	{TEXT("This chapter lets readers enter the very gateway of C++ which completely details varying control structures in C++ like decision making statements, looping control statements, multi-dimensional array,..Etc  ")},
	{TEXT("Readers stepping on the pathway to the C++ which completely details the pointer and its wide manifestations that can be drew from it such as the array, manifestation of pointer to pointers, memory allocation, function pointers.. Etc")},
	{TEXT("Readers stepping forward the pathway into C++ which introduces and detailing on reference which is known as sibling of its predecessor that is pointer.")},
	{TEXT("This chapter is truly the core cream of C++, where you will find anything related to the intrinsic core of C++'s tastes such as OOP, polymorphism, virtual function, virtual inheritance,.. Etc")},
	{TEXT("Readers are simply brought to one level above the fundamental C++'s core which detailing the new C++'s I/O stream (iostream), Exception Trapping & Handling mechanism,..Etc")},
	{TEXT("Readers entered into the highest level of C++ which featuring on Template Functions, Template Classes, Templated Types, Explicit Template Classes Specialization & Partial Template Specialization for Classes")},
	{TEXT("You can/might say this is actually a setback that rooted from the traditional C language, but despite it's true or not, this stuff had served much general programming features beside C++ itself, that is the Preprocessor Statements")},
	{TEXT("You finally will find the sincere aim of the previous chapter that rendered itself as foundation to provide the most features used in today's most sophisticated Microsoft Windows A.P.I.")}		
};


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHAP10_WIN32_PROJECT_05, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHAP10_WIN32_PROJECT_05));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHAP10_WIN32_PROJECT_05));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHAP10_WIN32_PROJECT_05);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT,0, 650, 400, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            // Parse the menu selections:
            switch ( LOWORD(wParam) )
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

			case IDL_LIST_BOX:
				switch (HIWORD(wParam)) {
					case LBN_SELCHANGE:
					{
						int selIndex = (int)SendMessageW(hwndList, LB_GETCURSEL, NULL, NULL);

						CopyMemory(szItemText, (LPWSTR)SendMessageW(hwndList, LB_GETITEMDATA, selIndex, NULL), 500);

						SetWindowTextW(hwndEditDoc, szItemText);
					}break;
						default: break;
				} break;
	
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;

	case WM_CREATE:
	{
		hwndList = CreateWindowW(TEXT("LISTBOX"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_STANDARD | LBS_HASSTRINGS,
			10, 50, 120, 250, hWnd, (HMENU)(int)IDL_LIST_BOX, ::hInst, NULL);

		hwndEditDoc = CreateWindowW(TEXT("Edit"), NULL, WS_CHILD | WS_BORDER | WS_VISIBLE | ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL,
			140, 50, 450, 250, hWnd, (HMENU)(int)IDC_EDIT_CTL_DOC, ::hInst, NULL);

		for (int i = 0; i < 10; )
		{
			SendMessageW(hwndList, LB_ADDSTRING, NULL, (LPARAM)szItem[i]);
			SendMessageW(hwndList, LB_SETITEMDATA, i, (LPARAM)szItemDesc[i]); ++i;
		}

	}
	break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
