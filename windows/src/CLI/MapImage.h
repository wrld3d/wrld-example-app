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

            void Init(int width, int height);
			void InitBackBuffer();
            void Render(float dt);

            void HandlePanStartEvent(int x, int y);
            void HandlePanEndEvent(int x, int y);
            void HandleRotateStartEvent(int x, int y);
            void HandleRotateEndEvent(int x, int y);
            void HandleTiltStart(int x, int y);
            void HandleTiltEnd(int x, int y);
            void HandleKeyboardDownEvent(int asciiKeyCode);
            void HandleKeyboardUpEvent(int asciiKeyCode) {}
            void HandleMouseMoveEvent(int x, int y);
            void HandleZoomEvent(int delta, int zoomDistance, int x, int y);
            void SetAllInputEventsToPointerUp(int x, int y);
            void Pause() {}
            void Resume() {}
            void RespondToResize(int width, int height);

        private:

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

