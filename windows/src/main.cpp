// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppRunner.h"
#include "main.h"
#include <pthread.h>

#include "WindowsNativeState.h"
#include "EegeoWindowsGuard.h"

#include <chrono>

using namespace Eegeo::Windows;
using namespace Eegeo::Windows::Input;

WindowsNativeState g_nativeState;
AppRunner* g_pAppRunner = NULL;

const int ZOOM_DISTANCE = 70;

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
    switch (umessage)
    {
        // Check if the window is being destroyed.
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }

    // Check if the window is being closed.
    case WM_CLOSE:
    {
        g_pAppRunner->Exit();
        DestroyWindow(g_nativeState.window);
        break;
    }

    case WM_LBUTTONDOWN:
        g_pAppRunner->HandlePanStartEvent(LOWORD(lparam), HIWORD(lparam));
        break;

    case WM_LBUTTONUP:
        g_pAppRunner->HandlePanEndEvent(LOWORD(lparam), HIWORD(lparam));
        break;

    case WM_RBUTTONDOWN:
        g_pAppRunner->HandleRotateStartEvent(LOWORD(lparam), HIWORD(lparam));
        break;

    case WM_RBUTTONUP:
        g_pAppRunner->HandleRotateEndEvent(LOWORD(lparam), HIWORD(lparam));
        break;

    case WM_MBUTTONDOWN:
        g_pAppRunner->HandleTiltStart(LOWORD(lparam), HIWORD(lparam));
        break;

    case WM_MBUTTONUP:
        g_pAppRunner->HandleTiltEnd(LOWORD(lparam), HIWORD(lparam));
        break;

    case WM_KEYDOWN:
        g_pAppRunner->HandleKeyboardDownEvent(static_cast<char>(wparam));
        break;

    case WM_KEYUP:
        g_pAppRunner->HandleKeyboardUpEvent(static_cast<char>(wparam));
        break;

    case WM_MOUSEMOVE:
        g_pAppRunner->HandleMouseMoveEvent(LOWORD(lparam), HIWORD(lparam));
        break;

    case WM_PAINT:
        break;

    case WM_MOUSEWHEEL:
        g_pAppRunner->HandleZoomEvent(GET_WHEEL_DELTA_WPARAM(wparam), ZOOM_DISTANCE, LOWORD(lparam), HIWORD(lparam));
        break;

    case WM_KILLFOCUS:
        if (g_pAppRunner)
        {
            g_pAppRunner->SetAllInputEventsToPointerUp(LOWORD(lparam), HIWORD(lparam));
        }
        break;

    case WM_SIZE:
    {
        if (g_pAppRunner)
        {
            if (wparam == SIZE_MINIMIZED)
            {
                g_pAppRunner->Pause();
            }
            else
            {
                if (wparam == SIZE_RESTORED || wparam == SIZE_MAXIMIZED)
                {
                    g_pAppRunner->Resume();
                }

                g_pAppRunner->RespondToResize();
            }
        }

        break;
    }
    }

    return DefWindowProc(hwnd, umessage, wparam, lparam);
}

//Initialise the platform
void InitNativeWindow(WindowsNativeState &nativeState)
{
    WNDCLASSEX wc;
    DEVMODE dmScreenSettings;
    int posX, posY;

    // Get the instance of this application.
    nativeState.hinstance = GetModuleHandle(NULL);

    // Setup the windows class with default settings.
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = nativeState.hinstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = nativeState.appName;
    wc.cbSize = sizeof(WNDCLASSEX);

    // Register the window class.
    RegisterClassEx(&wc);

    // Setup the screen settings depending on whether it is running in full screen or in windowed mode.
    if (nativeState.fullScreen)
    {
        // Determine the resolution of the clients desktop screen.
        nativeState.screenWidth = GetSystemMetrics(SM_CXSCREEN);
        nativeState.screenHeight = GetSystemMetrics(SM_CYSCREEN);

        // If full screen set the screen to maximum size of the users desktop and 32bit.
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = (unsigned long)nativeState.screenWidth;
        dmScreenSettings.dmPelsHeight = (unsigned long)nativeState.screenHeight;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // Change the display settings to full screen.
        ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

        // Set the position of the window to the top left corner.
        posX = posY = 0;
    }
    else
    {
        // Place the window in the middle of the screen.
        posX = (GetSystemMetrics(SM_CXSCREEN) - nativeState.screenWidth) / 2;
        posY = (GetSystemMetrics(SM_CYSCREEN) - nativeState.screenHeight) / 2;
    }

    // Create the window with the screen settings and get the handle to it.
    nativeState.window = CreateWindowEx(WS_EX_APPWINDOW, nativeState.appName, nativeState.appName,
        WS_OVERLAPPEDWINDOW,
        posX, posY, nativeState.screenWidth, nativeState.screenHeight, NULL, NULL, nativeState.hinstance, NULL);

    // Bring the window up on the screen and set it as main focus.
    ShowWindow(nativeState.window, SW_SHOW);
    //SetForegroundWindow(nativeState.window);
    //SetFocus(nativeState.window);

    ShowCursor(true);

}

void InitNativeState(const char* appName, int width, int height, bool fullScreen)
{
    g_nativeState.appName = appName;
    g_nativeState.screenWidth = width;
    g_nativeState.screenHeight = height;

    g_nativeState.fullScreen = fullScreen;
    g_nativeState.requiresPBuffer = false;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    InitNativeState("Eegeo", 1366, 768, false);

    InitNativeWindow(g_nativeState);

    g_pAppRunner = Eegeo_NEW(AppRunner)(&g_nativeState);

    if (!g_pAppRunner->ActivateSurface())
        return -1;

    g_pAppRunner->ActivateSharedSurface();

    MSG msg;

    // Initialize the message structure.
    ZeroMemory(&msg, sizeof(MSG));

    auto current = std::chrono::steady_clock::now();
    auto end = current;
    auto diff = current - end;
    float dt = 0.0f;

    while (g_pAppRunner->IsRunning())
    {
        // Handle the windows messages
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            current = std::chrono::steady_clock::now();
            diff = current - end;
            dt = static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());

            g_pAppRunner->UpdateNative(dt / 1000.0f);
            g_pAppRunner->UpdateUiViews(dt / 1000.0f);

            end = current;
        }
    }

    Eegeo_DELETE g_pAppRunner;

    return 0;
}