// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppRunner.h"
#include "main.h"
#include "MouseInputEvent.h"
#include <pthread.h>

#include "WindowsNativeState.h"
#include "EegeoWindowsGuard.h"

#include <chrono>
#include <windowsx.h>

using namespace Eegeo::Windows;
using namespace Eegeo::Windows::Input;

WindowsNativeState g_nativeState;
AppRunner* g_pAppRunner = NULL;

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
        DestroyWindow(g_nativeState.GetWindow());
        break;
    }

    case WM_LBUTTONDOWN:
        g_pAppRunner->HandleMouseEvent(WindowsInputProcessor::MakeMouseInputEvent(Eegeo::Windows::Input::MousePrimaryDown, wparam, lparam, 0));
        break;

    case WM_LBUTTONUP:
        g_pAppRunner->HandleMouseEvent(WindowsInputProcessor::MakeMouseInputEvent(Eegeo::Windows::Input::MousePrimaryUp, wparam, lparam, 0));
        break;

    case WM_RBUTTONDOWN:
        g_pAppRunner->HandleMouseEvent(WindowsInputProcessor::MakeMouseInputEvent(Eegeo::Windows::Input::MouseSecondaryDown, wparam, lparam, 0));
        break;

    case WM_RBUTTONUP:
        g_pAppRunner->HandleMouseEvent(WindowsInputProcessor::MakeMouseInputEvent(Eegeo::Windows::Input::MouseSecondaryUp, wparam, lparam, 0));
        break;

    case WM_MBUTTONDOWN:
        g_pAppRunner->HandleMouseEvent(WindowsInputProcessor::MakeMouseInputEvent(Eegeo::Windows::Input::MouseMiddleDown, wparam, lparam, 0));
        break;

    case WM_MBUTTONUP:
        g_pAppRunner->HandleMouseEvent(WindowsInputProcessor::MakeMouseInputEvent(Eegeo::Windows::Input::MouseMiddleUp, wparam, lparam, 0));
        break;

    case WM_MOUSEMOVE:
        g_pAppRunner->HandleMouseEvent(WindowsInputProcessor::MakeMouseInputEvent(Eegeo::Windows::Input::MouseMove, wparam, lparam, 0));
        break;

    case WM_MOUSEWHEEL:
        g_pAppRunner->HandleMouseEvent(WindowsInputProcessor::MakeMouseInputEvent(Eegeo::Windows::Input::MouseWheel, wparam, lparam, GET_WHEEL_DELTA_WPARAM(wparam)));
        break;

    case WM_KEYDOWN:
        g_pAppRunner->HandleKeyboardDownEvent(static_cast<char>(wparam));
        break;

    case WM_KEYUP:
        g_pAppRunner->HandleKeyboardUpEvent(static_cast<char>(wparam));
        break;

    case WM_PAINT:
        break;

    case WM_KILLFOCUS:
        if (g_pAppRunner)
        {
            g_pAppRunner->SetAllInputEventsToPointerUp(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
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
EGLNativeWindowType CreateNativeWindow(const std::string& appName, HINSTANCE hinstance, int width, int height, bool fullScreen)
{
    WNDCLASSEX wc;
    DEVMODE dmScreenSettings;
    int posX, posY;

    // Setup the windows class with default settings.
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC)WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hinstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = appName.c_str();
    wc.cbSize = sizeof(WNDCLASSEX);

    // Register the window class.
    RegisterClassEx(&wc);

    // Setup the screen settings depending on whether it is running in full screen or in windowed mode.
    if (fullScreen)
    {
        // If full screen set the screen to maximum size of the users desktop and 32bit.
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = (unsigned long)width;
        dmScreenSettings.dmPelsHeight = (unsigned long)height;
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
        posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
        posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
    }

    // Create the window with the screen settings and get the handle to it.
    EGLNativeWindowType window = CreateWindowEx(WS_EX_APPWINDOW, appName.c_str(), appName.c_str(),
        WS_OVERLAPPEDWINDOW,
        posX, posY, width, height, NULL, NULL, hinstance, NULL);

    return window;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    const std::string appName("Eegeo");
    const int defaultWidth = 1366;
    const int defaultHeight = 768;
    const bool fullScreen = false;
    const int width = fullScreen ? GetSystemMetrics(SM_CXSCREEN) : defaultWidth;
    const int height = fullScreen ? GetSystemMetrics(SM_CYSCREEN) : defaultHeight;
    
    const bool requiresPBuffer = false;
    const float oversampleScale = 1.f;
    const std::string deviceModel;
    const float deviceDpi = 0.f;

    HINSTANCE hinst = GetModuleHandle(NULL);
    EGLNativeWindowType window = CreateNativeWindow(appName, hInstance, width, height, fullScreen);

    g_nativeState = WindowsNativeState::Make(appName, hInstance, window, width, height, fullScreen, requiresPBuffer, oversampleScale, deviceModel, deviceDpi);

    ShowWindow(window, SW_SHOW);
    ShowCursor(true);

    g_pAppRunner = Eegeo_NEW(AppRunner)(&g_nativeState, false, 0);

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