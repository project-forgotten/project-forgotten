#include "StartUp.h"
#include "WindowManagement\WindowFactory.h"
#include "Engine\Engine.h"

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow) {

	WindowFactory::WindowClass<Engine, &Engine::WindowProcessing> win(L"GameWindow",
																	 CS_HREDRAW | CS_VREDRAW,
																	 NULL,
																	 NULL,
																	 LoadCursor(NULL, IDC_ARROW),
																	 (HBRUSH)COLOR_WINDOW,
																	 NULL);

	Engine engine;

	HWND windowHandler = win.createWindow(engine,
										NULL,
										L"Project: Forgotten",
										WS_OVERLAPPEDWINDOW,
										500,
										400,
										300,
										300,
										true);

	ShowWindow(windowHandler, nCmdShow);

	engine.Init(windowHandler);

	engine.run();

	return 0;

}