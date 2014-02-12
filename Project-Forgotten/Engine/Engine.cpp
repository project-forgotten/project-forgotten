#include "Engine.h"

Engine::Engine() {
}

Engine::~Engine() {

	// release swapchain before device, because has pointer to device
	if (swapChain) {
		swapChain->SetFullscreenState(false, NULL);
		swapChain->Release();
	}

	// release device before deviceContext, because has pointer to deviceContext
	if (device) {
		device->Release();
	}

	if (deviceContext) {
		deviceContext->Release();
	}

}

int Engine::run() {

	// check if the D3D environment has been initialized
	if (!initialized) {
		return -1;
	}

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

			// TODO: graphics stuff

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

void Engine::InitD3D(HWND windowHandler) {

	DXGI_SWAP_CHAIN_DESC swapChainDescending;
	ZeroMemory(&swapChainDescending, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDescending.BufferCount			= 1;
	swapChainDescending.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDescending.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescending.OutputWindow		= windowHandler;
	swapChainDescending.SampleDesc.Count	= 4;	// Multisampling AA
	swapChainDescending.Windowed			= TRUE;

	D3D11CreateDeviceAndSwapChain(NULL,
								  D3D_DRIVER_TYPE_HARDWARE,
								  NULL,
								  D3D11_CREATE_DEVICE_DEBUG, // maybe NULL
								  NULL,
								  NULL,
								  D3D11_SDK_VERSION,
								  &swapChainDescending,
								  &swapChain,
								  &device,
								  NULL,
								  &deviceContext);

}

void Engine::Init(HWND windowHandler) {
	InitD3D(windowHandler);
	initialized = true;
}