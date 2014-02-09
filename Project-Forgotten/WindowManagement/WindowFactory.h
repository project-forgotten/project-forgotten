#pragma once

#include <windows.h>

/**
 * The namespace WindowFactory is used to handle everything related to
 * a Windows window.
 */
namespace WindowFactory {

	/**
	 * The <code>Window</code> class is instantiated with a generic class type
	 * and a function pointer to the window processing function to handle
	 * all the window events.
	 *
	 * @tparam	T						 
	 * 				The class which has the window handler function.
	 * @tparam	LRESULT(T::*MsgProc)(HWND, UINT, WPARAM, LPARAM)
	 * 				Function pointer to window input handling function.
	 */
	template<class T, LRESULT(T::*MessageProcessing)(HWND, UINT, WPARAM, LPARAM)>
	class WindowClass {

		private:

			/**
			 * Stores the window registering result. Used to deregister the class in destructor.
			 */
			ATOM cls;

			/**
			 * Bootstrap window procedure to handle the window creation process and once registers the 
			 * 
			 *
			 * @param	hWnd  	The window handler.
			 * @param	msg   	The message the window received.
			 * @param	wParam	The wParam field of the message.
			 * @param	lParam	The lParam field of the message.
			 *
			 * @return	A CALLBACK.
			 */
			static LRESULT CALLBACK BootstrapWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
				
				if (msg == WM_CREATE) {
					T* obj = reinterpret_cast<T*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
					SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(obj));
					SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WndProc));
					return (obj->*MessageProcessing)(hWnd, msg, wParam, lParam);
				}

				return DefWindowProc(hWnd, msg, wParam, lParam);
			}

			/**
			 * The standart WndProc function to handle the window events. This function always
			 * calls the method of the given template class.
			 *
			 * @param	hWnd  	The window handler.
			 * @param	msg   	The message the window received.
			 * @param	wParam	The wParam field of the message.
			 * @param	lParam	The lParam field of the message.
			 *
			 * @return	A CALLBACK.
			 */
			static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
				T* obj = reinterpret_cast<T*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
				return (obj->*MessageProcessing)(hWnd, msg, wParam, lParam);
			}


		public:

			/**
			 * Creates a window class with the given parameters.
			 * 
			 * @param	lpszClassName	Name of the window class structure.
			 * @param	style		 	The style of the window.
			 * @param	hIcon		 	The icon of the window.
			 * @param	hIconSm		 	The icon sm.
			 * @param	hCursor		 	Handle of the cursor.
			 * @param	hbrBackground	(Optional) the background color of the window.
			 * @param	lpszMenuName 	(Optional) name of the menu.
			 */
			WindowClass(LPCTSTR lpszClassName,
					UINT style,
					HICON hIcon,
					HICON hIconSm,
					HCURSOR hCursor,
					HBRUSH hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
					LPCTSTR lpszMenuName = 0) {
				WNDCLASSEX wnd_cls;
				wnd_cls.cbSize = sizeof(wnd_cls);
				wnd_cls.style = style;
				wnd_cls.lpfnWndProc = &BootstrapWndProc;
				wnd_cls.cbClsExtra = 0;
				wnd_cls.cbWndExtra = 0;
				wnd_cls.hInstance = GetModuleHandle(0);
				wnd_cls.hIcon = hIcon;
				wnd_cls.hCursor = hCursor;
				wnd_cls.hbrBackground = hbrBackground;
				wnd_cls.lpszMenuName = lpszMenuName;
				wnd_cls.lpszClassName = lpszClassName;
				wnd_cls.hIconSm = hIconSm;
				cls = RegisterClassEx(&wnd_cls);
			}

			/**
			 * Deregister the window class from the WinAPI.
			 */
			~WindowClass() {
				UnregisterClass((LPCTSTR)cls, GetModuleHandle(0));
			}

			/**
			 * Registers a window in the window class. The returned HWND can be used to
			 * call <code>ShowWindow(HWND, int)</code> and show the window actually.
			 *
			 * @param [in,out]	obj 	The object with the window handler function.
			 * @param	dwExStyle   	The ex style.
			 * @param	lpWindowName	Name of the window.
			 * @param	dwStyle			The style.
			 * @param	nWidth			(Optional) the width of the window
			 * @param	nHeight			(Optional) the height.
			 * @param	X				(Optional) the  int to process.
			 * @param	Y				(Optional) the  int to process.
			 * @param 	adjustWindow	(Optional) true, if the size of the internal rectangle should be adjusted 										
			 * @param	hWndParent  	(Optional) the window parent.
			 * @param	hMenu			(Optional) the menu.		
			 *
			 * @return	The new window handler. Does need to be catched to visualize the window.
			 */
			HWND createWindow(T& obj,
							  DWORD dwExStyle,
							  LPCTSTR lpWindowName,
							  DWORD dwStyle,
							  int nWidth = CW_USEDEFAULT,
							  int nHeight = CW_USEDEFAULT,
							  int X = CW_USEDEFAULT,
							  int Y = CW_USEDEFAULT,
							  bool adjustWindow = false,
							  HWND hWndParent = 0,
							  HMENU hMenu = 0) {

				RECT windowRectangle = { 0, 0, nWidth, nHeight };

				if (adjustWindow) {
					AdjustWindowRect(&windowRectangle, dwStyle, FALSE);
				}

				return CreateWindowEx(dwExStyle,
									MAKEINTATOM(cls), // the window class name is queried
									lpWindowName,
									dwStyle,
									X,
									Y,
									windowRectangle.right - windowRectangle.left,
									windowRectangle.bottom - windowRectangle.top,
									hWndParent,
									hMenu,
									GetModuleHandle(0),
									static_cast<void*>(&obj));
			}

		};
}