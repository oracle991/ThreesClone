#include <Windows.h>


// 関数プロトタイプ
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
bool CreateMainWindow(HINSTANCE, int);
LRESULT WINAPI WinProc(HWND, UINT, WPARAM, WPARAM);

HINSTANCE hinst;

const char CLASS_NAME[] = "WinMain";
const char APP_TITLE[] = "Hello World";
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    MSG msg;

    if (!CreateMainWindow(hInstance, nCmdShow))
    {
        return false;
    }


    int done = 0;
    while (!done)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                done = 1;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return msg.wParam;
}

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0); //終了通知
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CreateMainWindow(HINSTANCE hInstance, int nCmdShow)
{
    WNDCLASSEX wcx;
    HWND hwnd;

    wcx.cbSize = sizeof(wcx);
    wcx.style = CS_HREDRAW | CS_VREDRAW; //windowsize変更時に再描画
    wcx.lpfnWndProc = WinProc;
    wcx.cbClsExtra = 0;
    wcx.cbWndExtra = 0;
    wcx.hInstance = hInstance;
    wcx.hIcon = NULL;
    wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcx.lpszMenuName = NULL;
    wcx.lpszClassName = CLASS_NAME;
    wcx.hIconSm = NULL;

    if (RegisterClassEx(&wcx) == 0)
    {
        return false;
    }

    hwnd = CreateWindow(
        CLASS_NAME,
        APP_TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        (HWND)NULL,
        (HMENU)NULL,
        hInstance,
        (LPVOID)NULL);

    if (!hwnd)
    {
        return false;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return true;
}

