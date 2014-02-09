#include "Engine.h"

Engine::Engine() {
	running = true;
}

Engine::~Engine() {}

int Engine::run() {
	MSG message;

	while (running) {

		// PeekMessage only looks up for new message
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);

			if (message.message == WM_QUIT) {
				running = false;
			}

		} else {

			// TODO

		}

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