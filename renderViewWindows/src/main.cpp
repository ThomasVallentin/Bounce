#include "RayTracer.h"
#include "TriangleMesh.hpp"
#include "FileLoaders.hpp"

#include <windows.h>
#include <cstdint>
#include <iostream>
#include <thread>


static RayTracer tracer;

// Window variables
static bool running = false;

// Bitmap buffer data
static BITMAPINFO bitmapInfo;
static void *bitmapMemory;
static int bitmapWidth;
static int bitmapHeight;
static int bytesPerPixel = 4;

// Render data
static int imageWidth = 400;
static int imageHeight = 200;

void fillScene() {
    Shader *whiteLambert = new Lambert(.8, .8, .8);
    Shader *redLambert = new Lambert(0.9, 0.1, 0.1);

    // Loading the ground
    OBJLoader loader = OBJLoader();
    std::string objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\ground.obj)";
    loader.load(objPath, false);

    for (HitableComposite *hitc : loader.hitables) {
        for (Hitable *hit : hitc->list())
            hit->shader_ptr = redLambert;

        tracer.addHitable(hitc);
    }

    // Loading the test geometry
    objPath = R"(D:\REPO\Bounce\bounceRenderer\ressources\geometries\fawn.obj)";
    loader.load(objPath, false);

    for (HitableComposite *hitc : loader.hitables) {
        for (Hitable *hit : hitc->list())
        {
            hit->shader_ptr = whiteLambert;
        }
        tracer.addHitable(hitc);
    }
}

static void getTracedColor(int x, int y, uint8_t (&color)[3]){
    vector3 vColor(0,0,0);

    if (x < imageWidth && y < imageHeight)
    {
        vColor[0] = tracer.pixels().at((y*imageWidth + x) * 3);
        vColor[1] = tracer.pixels().at((y*imageWidth + x) * 3 + 1);
        vColor[2] = tracer.pixels().at((y*imageWidth + x) * 3 + 2);

        vColor = applyGamma(vColor, tracer.gamma());
        vColor = unitToColor(vColor);
    }
    color[0] = vColor[0];
    color[1] = vColor[1];
    color[2] = vColor[2];
}

static void fillPixel(uint32_t *pixel, uint8_t (&color)[3])
{
    *pixel = (color[0] << 16 | color[1] << 8 | color[2]);
}

static void render(){
    // Writes data to the bitmapMemory
    uint8_t color[3] = {0, 0, 0};
    int pitch = bitmapWidth * bytesPerPixel;
    uint8_t *row = (uint8_t  *)bitmapMemory;
    for (int y = 0; y < bitmapHeight; y++)
    {
        uint32_t *pixel = (uint32_t *)row;
        for (int x = 0; x < bitmapWidth; x++)
        {
            getTracedColor(x, y, color);
            fillPixel(pixel, color);
            pixel++;
        }
        row += pitch;
    }
}

static void resizeDIBSection(int width, int height){
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

    fillScene();

    tracer.initialize();

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
