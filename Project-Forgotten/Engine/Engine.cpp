#include "Engine.h"

Engine::Engine() {}

Engine::~Engine() {}

int Engine::run() {
	MSG message;

	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

LRESULT Engine::WindowProcessing(HWND windowHandler, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY: PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(windowHandler, message, wParam, lParam);
}