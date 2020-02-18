#include <windows.h>
#include <cstdint>
#include "RayTracer.h"

#include <iostream>
#include <thread>

#define internal static
#define local_persistent static
#define global_variable static

global_variable RayTracer tracer;

// Window variables
global_variable bool running = false;

// Bitmap buffer data
global_variable BITMAPINFO bitmapInfo;
global_variable void *bitmapMemory;
global_variable int bitmapWidth;
global_variable int bitmapHeight;
global_variable int bytesPerPixel = 4;

// Render data
global_variable int imageWidth = 800;
global_variable int imageHeight = 400;

void fillScene()
{
    Shader* whiteLambert = new Lambert(.8, .8, .8);
    Shader* redLambert = new Lambert(.8, .15, .05);
    Shader* blueLambert = new Lambert(.1, .1, .9);
    Shader* greenMetal = new Metal(.2, .9, .2, .3);

    // Filling the tracer with the objects
    tracer.addHitable(new Sphere(vector3(0.0, 0.0, -2.0), 0.5, "Sphere1", redLambert));
    tracer.addHitable(new Sphere(vector3(1.0, 0.0, -2.0), 0.5, "Sphere2", blueLambert));
    tracer.addHitable(new Sphere(vector3(-.6, 0.0, -1.2), 0.3, "Sphere3", greenMetal));

    // Huge sphere used as pseudo ground
    tracer.addHitable(new Sphere(vector3(0.0, -100.5, -1.0), 100, "Ground", whiteLambert));
}

internal bool extractColor(int x, int y, uint8_t (&color)[3]){
    if (x < imageWidth && y < imageHeight)
    {
        color[0] = tracer.m_result.at((y*imageWidth + x) * 3);
        color[1] = tracer.m_result.at((y*imageWidth + x) * 3 + 1);
        color[2] = tracer.m_result.at((y*imageWidth + x) * 3 + 2);
        return(true);
    }
    else
    {
        color[0] = 0;
        color[1] = 0;
        color[2] = 0;
        return(false);
    }
}

internal void fillPixel(uint32_t *pixel, uint8_t (&color)[3])
{
    *pixel = (color[0] << 16 | color[1] << 8 | color[2]);
}

internal void render(){
    // Writes data to the bitmapMemory
    uint8_t color[3] = {0, 0, 0};
    int pitch = bitmapWidth * bytesPerPixel;
    uint8_t *row = (uint8_t  *)bitmapMemory;
    for (int y = 0; y < bitmapHeight; y++)
    {
        uint32_t *pixel = (uint32_t *)row;
        for (int x = 0; x < bitmapWidth; x++)
        {
            extractColor(x, y, color);
            fillPixel(pixel, color);
            pixel++;
        }
        row += pitch;
    }
}

internal void resizeDIBSection(int width, int height){
    if (bitmapMemory)
    {
        VirtualFree(bitmapMemory, 0, MEM_RELEASE); // freeing the memory if it is already allocated
    }

    bitmapWidth = width;
    bitmapHeight = height;

    bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
    bitmapInfo.bmiHeader.biWidth = bitmapWidth;
    bitmapInfo.bmiHeader.biHeight = -bitmapHeight;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB ;

    int bitmapMemorySize = bytesPerPixel  * width * height;
    bitmapMemory = VirtualAlloc(nullptr, bitmapMemorySize, MEM_COMMIT, PAGE_READWRITE); // allocating memory with full read write access
}

void CALLBACK updateWindow(HDC deviceContext, RECT* clientRect, int x, int y, int width, int height){
    int clientWidth = clientRect->right - clientRect->left;
    int clientHeight = clientRect->bottom - clientRect->top;

    StretchDIBits(deviceContext,
                  x, y, bitmapWidth, bitmapHeight,
                  x, y, clientWidth, clientHeight,
                  bitmapMemory,
                  &bitmapInfo,
                  DIB_RGB_COLORS,
                  SRCCOPY);
}


LRESULT CALLBACK MainWindowCallback(HWND   window,
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

            RECT clientRect;
            GetClientRect(window, &clientRect);

            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom -clientRect.top;
            // Creating and resizing a bitmap buffer
            resizeDIBSection(width, height);
            render();
        } break;

        case WM_CLOSE:
        {
            // Ask the user before closing ?
            running = false;
            std::cout << "WM_CLOSE" << std::endl;
        } break;

        case WM_DESTROY:
        {
            running = false;
            std::cout << "WM_DESTROY" << std::endl;
        } break;

        case WM_ACTIVATEAPP:
        {
            std::cout << "WM_ACTIVATEAPP" << std::endl;
        } break;

        case WM_PAINT:
        {
            std::cout << "WM_PAINT" << std::endl;
            PAINTSTRUCT painter;
            HDC deviceContext = BeginPaint(window, &painter);

            int x = painter.rcPaint.left;
            int y = painter.rcPaint.top;
            int width = painter.rcPaint.right - painter.rcPaint.left;
            int height = painter.rcPaint.bottom - painter.rcPaint.top;

            RECT clientRect;
            GetClientRect(window, &clientRect);
            // Painting the buffer to the window
            updateWindow(deviceContext, &clientRect, x, y, width, height);

            EndPaint(window, &painter);
        } break;


        default:
        {
            // std::cout << "Default" << std::endl;
            result = DefWindowProc(window, message, wParam, lParam);
        } break;

    }

    return(result);
}

void traceRender(Camera *cam)
{
    tracer.trace(*cam);
}

INT CALLBACK WinMain(HINSTANCE instance,
                     HINSTANCE prevInstance,
                     LPSTR commandLine,
                     INT showCode)
{
    // Render engine initialization
    tracer.setWidth(imageWidth);
    tracer.setHeight(imageHeight);
    tracer.initialize();

    fillScene();

    // Starting thread using render
    Camera cam;
    std::thread renderThread(traceRender, &cam);

    // Create and register windowClass
    WNDCLASS WindowClass = {};

    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = instance;
    WindowClass.lpszClassName = "BounceRenderViewClass";

    if(!RegisterClass(&WindowClass))
    {
        std::cout << "ERROR: Failed to register the window..." << std::endl;
        return(EXIT_FAILURE);
    }

    // Creating window
    HWND window = CreateWindowEx(
            0,
            WindowClass.lpszClassName,
            "BounceRenderView",
            WS_OVERLAPPEDWINDOW|WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            imageWidth,
            imageHeight,
            nullptr,
            nullptr,
            instance,
            nullptr);
    if (!window){
        std::cout << "ERROR: Failed to creat the window..." << std::endl;
    }

    // Window's main message loop
    running = true;
    while (running)
    {
        // Emptying the message queue then redraw the window
        MSG message;
        while(PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)){
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        // Render the buffer (bitmap)
        render();

        // Updating filling window with the buffer
        HDC deviceContext = GetDC(window);

        RECT clientRect;
        GetClientRect(window, &clientRect);
        int windowWidth = clientRect.right - clientRect.left;
        int windowHeight = clientRect.bottom - clientRect.top;
        updateWindow(deviceContext, &clientRect, clientRect.left, clientRect.top, windowWidth, windowHeight);

        ReleaseDC(window, deviceContext);
    }

    renderThread.join();

    return (EXIT_SUCCESS);
}
