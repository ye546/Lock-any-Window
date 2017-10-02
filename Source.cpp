#include <windows.h>  
#include <stdlib.h>  
#include <string>  
#include <tchar.h> 
#include <cstring>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

static TCHAR szWindowClass[] = _T("Lock any window");
HWND lock, unlock, name1, findWindow;
static TCHAR szTitle[] = _T("Lock");
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow){
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}
	hInst = hInstance; 
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		200, 150,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBoxA(NULL, "KEK", NULL, MB_OK);
		return 1;
	}
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	PAINTSTRUCT ps;
	HDC hdc;
	char windowName[150];
	std::memset(windowName, 0, sizeof(char));
	switch (message)
	{
	case WM_CREATE:
		lock = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "Lock", WS_CHILD | WS_VISIBLE, 10, 10, 50, 30, hWnd, NULL, hInst, (LPVOID)lParam);
		unlock = CreateWindowExA(WS_EX_WINDOWEDGE, "Button", "Unlock", WS_CHILD | WS_VISIBLE, 110, 10, 50, 30, hWnd, NULL, hInst, (LPVOID)lParam);
		name1 = CreateWindowExA(WS_EX_CLIENTEDGE, "Edit", "name...", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 60, 150, 20, hWnd, NULL, hInst, (LPVOID)lParam);
		break;
	case WM_COMMAND:
		if (message == WM_COMMAND && (HWND)lParam == lock) {
			if (GetWindowTextA(name1, windowName, _countof(windowName)) == NULL) {
				MessageBoxA(NULL, "The textfield is empty!", NULL, MB_OK | MB_ICONERROR);
				return 0;
			}

			findWindow = FindWindowA(NULL, windowName);
			if (!findWindow) {
				MessageBoxA(NULL, "The specified window does not exist", NULL, MB_OK | MB_ICONERROR);
			}
			else if(findWindow){
				EnableWindow(findWindow, FALSE);
				MessageBoxA(NULL, "Window disabled", "Information", MB_OK | MB_ICONINFORMATION);
			}
		}
		if (message == WM_COMMAND && (HWND)lParam == unlock) {
			if (GetWindowTextA(name1, windowName, _countof(windowName)) == NULL) {
				MessageBoxA(NULL, "The textfield is empty!", NULL, MB_OK | MB_ICONERROR);
				return 0;
			}
			findWindow = FindWindowA(NULL, windowName);
			if (!findWindow) {
				MessageBoxA(NULL, "´The specified window does not exist", NULL, MB_OK | MB_ICONERROR);
			}
			else if(findWindow){
				EnableWindow(findWindow, TRUE);
				MessageBoxA(NULL, "Window enabled", "Information", MB_OK | MB_ICONINFORMATION);
			}
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}
