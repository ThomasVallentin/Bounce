#include <windows.h>
#include <iostream>

LRESULT CALLBACK MainWindowCallback(HWND   windowHandle,
                                    UINT   message,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
    LRESULT result = 0;

    switch(message)
    {
        case WM_SIZE:
        {
            std::cout << "WM_SIZE" << std::endl;
        } break;

        case WM_DESTROY:
        {
            std::cout << "WM_DESTROY" << std::endl;
        } break;

        case WM_CLOSE:
        {
            std::cout << "WM_CLOSE" << std::endl;
        } break;

        case WM_ACTIVATEAPP:
        {
            std::cout << "WM_ACTIVATEAPP" << std::endl;
        } break;

        default:
        {
            // std::cout << "Default" << std::endl;
            result = DefWindowProc(windowHandle, message, wParam, lParam);
        } break;

    }

    return(result);
}

INT CALLBACK WinMain(HINSTANCE instance,
                     HINSTANCE prevInstance,
                     LPSTR commandLine,
                     INT showCode)
{
    WNDCLASS WindowClass = {};

    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = instance;
    WindowClass.lpszClassName = "BounceRenderViewClass";
    // WindowClass.hIcon;

    if(RegisterClass(&WindowClass))
    {
        HWND windowHandle = CreateWindowEx(DWORD dwExStyle,
                                           LPCTSTR lpClassName,
                                           LPCTSTR lpWindowName,
                                           DWORD dwStyle,
                                           int x,
                                           int y,
                                           int nWidth,
                                           int nHeight,
                                           HWND hWndParent,
                                           HMENU hMenu,
                                           HINSTANCE hInstance,
                                           LPVOID lpParam ); ;
    }
    else{
        std::cout << "ERROR: Failed to register the window..." << std::endl;
        return(EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}
