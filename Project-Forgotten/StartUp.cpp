#include <windows.h>
#include <windowsx.h>

// forward declaration of the Window message handler
LRESULT CALLBACK WindowProcedure(HWND windowHandler, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {

	HWND gameWindowHandler;
	WNDCLASSEX gameWindow;

	ZeroMemory(&gameWindow, sizeof(WNDCLASSEX));

	gameWindow.cbSize = sizeof(WNDCLASSEX);
	gameWindow.style = CS_HREDRAW | CS_VREDRAW;
	gameWindow.lpfnWndProc = WindowProcedure;
	gameWindow.hInstance = hInstance;
	gameWindow.hCursor = LoadCursor(NULL, IDC_ARROW);
	gameWindow.hbrBackground = (HBRUSH)COLOR_WINDOW;
	gameWindow.lpszClassName = L"GameWindow";
	RegisterClassEx(&gameWindow);
	gameWindowHandler = CreateWindowEx(NULL,
		L"GameWindow",
		L"Project: Forgotten",
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		500,
		400,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(gameWindowHandler, nCmdShow);

	MSG message;

	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

/**
* Window procedure.
*
* @param	windowHandler	Handle of the window handler.
* @param	message		 	The message.
* @param	wParam		 	The wParam field of the message.
* @param	lParam		 	The lParam field of the message.
*
* @return	A CALLBACK.
*/
LRESULT CALLBACK WindowProcedure(HWND windowHandler, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY: PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(windowHandler, message, wParam, lParam);
}