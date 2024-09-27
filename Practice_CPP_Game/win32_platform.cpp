#include<windows.h>
bool running = true;
LRESULT CALLBACK window_callback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result;
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY:
	{
		running = false;
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
	while (running) {
		MSG message;
		while (PeekMessage(&message, window,0,0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	
	}

}