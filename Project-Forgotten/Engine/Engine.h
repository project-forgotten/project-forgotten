#pragma once

#include "../WindowManagement/WindowFactory.h"
#include <d3d11.h>
#include <d3dx11.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")

class Engine {

private:

	/**
	 * True, if the engine is running. If it's false the engine won't run.
	 */
	bool running = true;

	/**
	* True, if the engine has been initializes via the <code>Init()</code>
	* method.
	*/
	bool initialized = false;

	/**
	 * The pointer to the real video adapter object. Mainly used to initialize
	 * e.g. buffers and fetch textures.
	 */
	ID3D11Device* device = nullptr;

	/**
	 * Adress of the device context object. This is used for rendering.
	 */
	ID3D11DeviceContext* deviceContext = nullptr;

	/**
	 * The pointer to the swap chain.
	 */
	IDXGISwapChain* swapChain = nullptr;

	/**
	 * Initializes the D3D environment.<br />
	 * This includes the video card and swapchain.
	 */
	void InitD3D(HWND windowHandler);

public:// wtf? wie hast du dich verbunden? VPN??

	/**
	 * Creates a blank engine object. Afterwards the <code>Init()</code>
	 * method must be called.
	 */
	Engine();

	/**
	 * Cleans up the D3D environment build up for DirectX. E.g. releasing all the COM
	 * components like the swapchain and the video device.
	 */
	~Engine();

	int run();

	/**
	* Initializes the D3D environment.<br />
	* This includes the video card and swapchain.
	*/
	void Init(HWND windowHandler);

	/**
	 * The window processing function. This class is registered as listener on program 
	 * when the main window is created.
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