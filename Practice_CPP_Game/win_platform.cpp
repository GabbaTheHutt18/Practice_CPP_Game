#include<Windows.h>
#include"Utilities.cpp"

global_variable bool running = true;

struct Render_State {
	int height, width;
	void* memory;
	BITMAPINFO bitmapinfo;
};

global_variable Render_State render_state;
#include"Renderer.cpp"
LRESULT CALLBACK window_callback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result;
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY:
	{
		running = false;
	} break;
	case WM_SIZE:
	{
		RECT rect;
		GetClientRect(hWnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;
		int size = render_state.width * render_state.height * sizeof(unsigned int);
		if (render_state.memory)
		{
			VirtualFree(render_state.memory,0, MEM_RELEASE);
		}
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		render_state.bitmapinfo.bmiHeader.biSize = sizeof(render_state.bitmapinfo.bmiHeader);
		render_state.bitmapinfo.bmiHeader.biWidth = render_state.width;
		render_state.bitmapinfo.bmiHeader.biHeight = render_state.height;
		render_state.bitmapinfo.bmiHeader.biPlanes = 1;
		render_state.bitmapinfo.bmiHeader.biBitCount = 32;
		render_state.bitmapinfo.bmiHeader.biCompression = BI_RGB;


	} break;
	default:
	{
		result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	//create window class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = TEXT("Game Window");
	window_class.lpfnWndProc = window_callback;
	//register class
	RegisterClass(&window_class);
	//create window
	HWND window = CreateWindow(window_class.lpszClassName, TEXT("Practice C++ Game!"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);
	while (running) {
		MSG message;
		while (PeekMessage(&message, window,0,0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		clear_screen(0xff5500);
		draw_rect(0, 0, 20, 20, 0x00ff22);

		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height,0,0, render_state.width, render_state.height,render_state.memory, &render_state.bitmapinfo, DIB_RGB_COLORS, SRCCOPY);
	
	}

}