#pragma once

#include <Windows.h>

/**
 * The Windows startup function for Win32 projects. This is the entrance point
 * of the applciation. 
 * 
 * @return The application status code when exiting (0 == no error) 
 */
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow);