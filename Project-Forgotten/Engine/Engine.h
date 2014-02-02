#pragma once

#include "../WindowManagement/WindowFactory.h"

class Engine {

private:

public:
	Engine();

	~Engine();

	int Engine::run();

	/**
	 * @fn	LRESULT Engine::WindowProcessing(HWND windowHandler, UINT message, WPARAM wParam, LPARAM lParam);
	 *
	 *
	 * @param	windowHandler	Handle of the window handler.
	 * @param	message		 	The message.
	 * @param	wParam		 	The wParam field of the message.
	 * @param	lParam		 	The lParam field of the message.
	 *
	 * @return	A CALLBACK.
	 */
	LRESULT WindowProcessing(HWND windowHandler, UINT message, WPARAM wParam, LPARAM lParam);

};