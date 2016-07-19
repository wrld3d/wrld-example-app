#pragma once

#using "PresentationFramework.dll"
#using "PresentationCore.dll"
#using "System.dll"

#include "EegeoWindowsGuard.h"

class AppRunner;
struct WindowsNativeState;

namespace ExampleApp
{
    namespace CLI
    {
        public ref class MapImage : public System::Windows::Interop::D3DImage
        {
        public:
            MapImage();
            ~MapImage();
            !MapImage();

            void Init(int width, int height, float oversampleScale, bool hasNativeTouchInput, int maxDeviceTouchCount);
            void InitBackBuffer();
            void Render(float dt);

            void HandlePanStartEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys);
            void HandlePanEndEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys);
            void HandleRotateStartEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys);
            void HandleRotateEndEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys);
            void HandleTiltStart(int x, int y, System::Windows::Input::ModifierKeys modifierKeys);
            void HandleTiltEnd(int x, int y, System::Windows::Input::ModifierKeys modifierKeys);
            void HandleKeyboardDownEvent(int asciiKeyCode);
            void HandleKeyboardUpEvent(int asciiKeyCode) {}
            void HandleTouchDownEvent(float x, float y, float z, int id);
            void HandleTouchUpEvent(float x, float y, float z, int id);
            void HandleTouchMoveEvent(float x, float y, float z, int id);
            void HandleMouseMoveEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys);
            void HandleZoomEvent(int x, int y, int wheelDelta, System::Windows::Input::ModifierKeys modifierKeys);
            void SetAllInputEventsToPointerUp(int x, int y);
            void SetAllTouchInputEventsToPointerUp(int touchId);
            void Pause() {}
            void Resume() {}
            void RespondToResize(int width, int height);

            bool ShouldStartFullscreen();

            void SetFullscreen(bool fullscreen);

        private:

            int ScaledScreenCoord(int value);

            HRESULT InitDirect3D(HWND windowHandle);
            void DestroyDirect3D();

            IDirect3DSurface9* GetSurfaceFromShareHandle(void* shareHandle, int width, int height);
            void InvalidateImage();
            int GetScreenDPI();

            IDirect3D9Ex* m_d3d9;
            IDirect3DDevice9Ex* m_d3d9Device;
            AppRunner* m_appRunner;
            WindowsNativeState* m_pState;
        };
    }
}

