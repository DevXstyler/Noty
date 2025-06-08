#include <iostream>
#include <windows.h>

//variables
int height = 600;
int width = 800;



LRESULT CALLBACK WindowProc(hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg){
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_SIZE:
            {
                HWND hEdit; // global
                RECT rc;
                GetClientRect(hwnd, &rc);

                int newWidth = rc.right - rc.left;   
                int newHeight = rc.bottom - rc.top; 

                SetWindowPos(hwndTextBox, NULL, 0, 0, newWidth, newHeight, SWP_NOZORDER | SWP_NOACTIVATE);

            }
            return 0;
        case WM_CTLCOLOREDIT:
            {
                HDC hdc = (HDC)wParam;
                SetBkColor(hdc, RGB(0, 0, 0));
                SetTextColor(hdc, RGB(255, 255, 255));
                return (LRESULT)GetStockObject(BLACK_BRUSH);
            }
        default:
            return DefWindowProc(hwnd,uMsg,wParam,lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.hInstance = hInstance;
    wc.lpszClassName = "Noty";
    wc.lpfnWndProc = WindowProc;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

    RegisterClassEx(&wc);
    HWND hwnd = CreateWindowEx(0, wc.lpszClassName, "Noty", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);
    HWND hEdit = CreateWindowEx(0, "EDIT", "Enter your notes here.", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE, 0, 0, width, height, hwnd, NULL, hInstance, NULL);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);


    // Create a message loop
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int) msg.wParam;
}