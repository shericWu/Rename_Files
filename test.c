#include<windows.h>
#include<stdbool.h>
#include<assert.h>

const char g_szClassName[] = "myWindowClass";


bool RegisterWindowClass(WNDCLASSEX *wc, HINSTANCE hInstance);
bool CreateMyWindow(HWND *hwnd, HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
LPSTR lpCmdLine, int nCmdShow){
    
    
    WNDCLASSEX wc;
    assert(RegisterWindowClass(&wc, hInstance) == true);
    
    HWND hwnd;
    assert(CreateMyWindow(&hwnd, hInstance) == true);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    MSG Msg;
    while(GetMessage(&Msg, NULL, 0, 0) > 0){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

// Step 1: Registering the Window Class
bool RegisterWindowClass(WNDCLASSEX *wc, HINSTANCE hInstance){
    wc->cbSize = sizeof(WNDCLASSEX);
    wc->style = 0;
    wc->lpfnWndProc = WndProc;
    wc->cbClsExtra = 0;
    wc->cbWndExtra = 0;
    wc->hInstance = hInstance;
    wc->hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc->hCursor = LoadCursor(NULL, IDC_ARROW);
    wc->hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc->lpszMenuName = NULL;
    wc->lpszClassName = g_szClassName;
    wc->hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(wc)){
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    return true;
}

// Step 2: Creating the Window
bool CreateMyWindow(HWND *hwnd, HINSTANCE hInstance){
    *hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The title of my window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        960, 540,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if(*hwnd == NULL){
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return false;
    }
    return true;
}

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}