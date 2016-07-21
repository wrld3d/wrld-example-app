#include "MapImage.h"
#include "MouseInputEvent.h"
#include "TouchScreenInputEvent.h"
#include "AppRunner.h"

#pragma comment(lib, "d3d9.lib")

namespace ExampleApp
{
    namespace CLI
    {
        MapImage::MapImage() 
            : m_pState(NULL)
        {
            
        } 

        MapImage::~MapImage()
        {
            this->!MapImage();
        }

        MapImage::!MapImage()
        {
            Lock();
            SetBackBuffer(System::Windows::Interop::D3DResourceType::IDirect3DSurface9, System::IntPtr::Zero);
            Unlock();

            Eegeo_DELETE m_appRunner;
            m_appRunner = NULL;

            Eegeo_DELETE m_pState;
            m_pState = NULL;

            DestroyDirect3D();
        }

        void MapImage::Init(int width, int height, float oversampleScale, bool hasNativeTouchInput, int maxDeviceTouchCount)
        {
            System::Windows::Application^ app = System::Windows::Application::Current;
            System::Windows::Interop::WindowInteropHelper^ windowInteropHelper = gcnew System::Windows::Interop::WindowInteropHelper(app->MainWindow);

            HWND windowHandle = (HWND)windowInteropHelper->Handle.ToPointer();

            const std::string appName = "WPFControl";
            const float deviceDpi = static_cast<float>(GetScreenDPI());
            const std::string deviceModel = "WPFControl";
            const bool fullScreen = false;
            const HINSTANCE hinstance = GetModuleHandle(NULL);
            const bool requiresPBuffer = true;
            const int screenWidth = (int)(width * oversampleScale);
            const int screenHeight = (int)(height * oversampleScale);

            if (m_pState == NULL)
            {
                m_pState = WindowsNativeState::Create(appName, hinstance, windowHandle, screenWidth, screenHeight, fullScreen, requiresPBuffer, oversampleScale, deviceModel, deviceDpi);
            }

            m_appRunner = new AppRunner(m_pState, hasNativeTouchInput, maxDeviceTouchCount);
            m_appRunner->ActivateSurface();
            m_appRunner->ActivateSharedSurface();

            InitDirect3D(windowHandle);			

			InitBackBuffer();
        }

		void MapImage::InitBackBuffer()
		{
			void* surfaceSharePointer = m_appRunner->GetMainRenderSurfaceSharePointer();
			IDirect3DSurface9* surface = GetSurfaceFromShareHandle(surfaceSharePointer, m_pState->GetWidth(), m_pState->GetHeight());
			Lock();
			SetBackBuffer(System::Windows::Interop::D3DResourceType::IDirect3DSurface9, System::IntPtr(surface));
			Unlock();
			surface->Release();
		}
        
        IDirect3DSurface9* MapImage::GetSurfaceFromShareHandle(void* shareHandle, int width, int height)
        {
            /* Check if the user just wants to clear the D3DImage backbuffer */
            if (!shareHandle)
            {
                return NULL;
            }

            HRESULT hr = S_OK;
            IDirect3DTexture9* pTexture = NULL;

            hr = m_d3d9Device->CreateTexture(width, height, 1,
                D3DUSAGE_RENDERTARGET,
                D3DFMT_A8R8G8B8,
                D3DPOOL_DEFAULT,
                &pTexture,
                (HANDLE*)&shareHandle);

            if (SUCCEEDED(hr))
            {
                IDirect3DSurface9* surface;
                hr = pTexture->GetSurfaceLevel(0, &surface);
                pTexture->Release();

                return surface;
            }

            return NULL;
        }

        HRESULT MapImage::InitDirect3D(HWND windowHandle)
        {
            pin_ptr<IDirect3D9Ex*> pd3d9(&m_d3d9);
            Direct3DCreate9Ex(D3D_SDK_VERSION, pd3d9);

            if (!m_d3d9)
                return E_FAIL;

            D3DPRESENT_PARAMETERS		d3dpp;
            ZeroMemory(&d3dpp, sizeof(d3dpp));
            d3dpp.Windowed = TRUE;
            d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
            d3dpp.hDeviceWindow = windowHandle;
            d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

            pin_ptr<IDirect3DDevice9Ex*> pd3d9Device(&m_d3d9Device);
            
            HRESULT hr = m_d3d9->CreateDeviceEx(D3DADAPTER_DEFAULT,
                D3DDEVTYPE_HAL,
                windowHandle,
                D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                &d3dpp,
                NULL,
                pd3d9Device);

            return hr;
        }

        void MapImage::DestroyDirect3D()
        {
            if (m_d3d9Device)
            {
                m_d3d9Device->Release();
                m_d3d9Device = NULL;
            }

            if (m_d3d9)
            {
                m_d3d9->Release();
                m_d3d9 = NULL;
            }
        }

        void MapImage::Render(float dt)
        {
            m_appRunner->UpdateNative(dt);
            m_appRunner->UpdateUiViews(dt);			

            InvalidateImage();
        }

        void MapImage::InvalidateImage()
        {
            Lock();
            AddDirtyRect(System::Windows::Int32Rect(
                0,
                0,
                PixelWidth,
                PixelHeight
                ));
            Unlock();
        }

        namespace
        {
            Eegeo::Windows::Input::MouseInputEvent MakeMouseInputEvent(Eegeo::Windows::Input::MouseInputAction mouseInputAction, int x, int y, int wheelDelta, System::Windows::Input::ModifierKeys modifierKeys)
            {
                const u32 modifierKeysU32 = static_cast<u32>(modifierKeys);

                u32 keyboardModifiers = Eegeo::Windows::Input::KeyboardModifierNone;
                if (modifierKeysU32 & static_cast<u32>(System::Windows::Input::ModifierKeys::Alt))
                    keyboardModifiers |= Eegeo::Windows::Input::KeyboardModifierAlt;

                if (modifierKeysU32 & static_cast<u32>(System::Windows::Input::ModifierKeys::Shift))
                    keyboardModifiers |= Eegeo::Windows::Input::KeyboardModifierShift;

                if (modifierKeysU32 & static_cast<u32>(System::Windows::Input::ModifierKeys::Control))
                    keyboardModifiers |= Eegeo::Windows::Input::KeyboardModifierControl;

                return Eegeo::Windows::Input::MouseInputEvent(mouseInputAction, keyboardModifiers, x, y, wheelDelta);
            }

            Eegeo::Windows::Input::TouchScreenInputEvent MakeTouchScreenInputEvent(float x, float y, float z, int id, Eegeo::Windows::Input::TouchScreenInputAction touchScreenInputAction)
            {
                return Eegeo::Windows::Input::TouchScreenInputEvent(x, y, z, id, touchScreenInputAction);
            }
        }

        int MapImage::ScaledScreenCoord(int value)
        {
            return (int)(m_pState->GetOversampleScale() * value);
        }

        void MapImage::HandlePanStartEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys)
        {
            m_appRunner->HandleMouseEvent(MakeMouseInputEvent(Eegeo::Windows::Input::MousePrimaryDown, ScaledScreenCoord(x), ScaledScreenCoord(y), 0, modifierKeys));
        }

        void MapImage::HandlePanEndEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys)
        {
            m_appRunner->HandleMouseEvent(MakeMouseInputEvent(Eegeo::Windows::Input::MousePrimaryUp, ScaledScreenCoord(x), ScaledScreenCoord(y), 0, modifierKeys));
        }

        void MapImage::HandleRotateStartEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys)
        {
            m_appRunner->HandleMouseEvent(MakeMouseInputEvent(Eegeo::Windows::Input::MouseSecondaryDown, ScaledScreenCoord(x), ScaledScreenCoord(y), 0, modifierKeys));
        }

        void MapImage::HandleRotateEndEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys)
        {
            m_appRunner->HandleMouseEvent(MakeMouseInputEvent(Eegeo::Windows::Input::MouseSecondaryUp, ScaledScreenCoord(x), ScaledScreenCoord(y), 0, modifierKeys));
        }

        void MapImage::HandleTiltStart(int x, int y, System::Windows::Input::ModifierKeys modifierKeys)
        {
            m_appRunner->HandleMouseEvent(MakeMouseInputEvent(Eegeo::Windows::Input::MouseMiddleDown, ScaledScreenCoord(x), ScaledScreenCoord(y), 0, modifierKeys));
        }

        void MapImage::HandleTiltEnd(int x, int y, System::Windows::Input::ModifierKeys modifierKeys)
        {
            m_appRunner->HandleMouseEvent(MakeMouseInputEvent(Eegeo::Windows::Input::MouseMiddleUp, ScaledScreenCoord(x), ScaledScreenCoord(y), 0, modifierKeys));
        }

        void MapImage::HandleMouseMoveEvent(int x, int y, System::Windows::Input::ModifierKeys modifierKeys)
        {
            m_appRunner->HandleMouseEvent(MakeMouseInputEvent(Eegeo::Windows::Input::MouseMove, ScaledScreenCoord(x), ScaledScreenCoord(y), 0, modifierKeys));
        }

        void MapImage::HandleZoomEvent(int x, int y, int wheelDelta, System::Windows::Input::ModifierKeys modifierKeys)
        {
            m_appRunner->HandleMouseEvent(MakeMouseInputEvent(Eegeo::Windows::Input::MouseWheel, ScaledScreenCoord(x), ScaledScreenCoord(y), wheelDelta, modifierKeys));
        }

        void MapImage::HandleKeyboardDownEvent(int asciiKeyCode)
        {
            m_appRunner->HandleKeyboardDownEvent(asciiKeyCode);
        }

        void MapImage::HandleTouchDownEvent(float x, float y, float z, int id)
        {
            m_appRunner->HandleTouchEvent(MakeTouchScreenInputEvent(x, y, z, id, Eegeo::Windows::Input::TouchScreenInputAction::TouchScreenDown));
        }
        
        void MapImage::HandleTouchUpEvent(float x, float y, float z, int id)
        {
            m_appRunner->HandleTouchEvent(MakeTouchScreenInputEvent(x, y, z, id, Eegeo::Windows::Input::TouchScreenInputAction::TouchScreenUp));
        }

        void MapImage::HandleTouchMoveEvent(float x, float y, float z, int id)
        {
            m_appRunner->HandleTouchEvent(MakeTouchScreenInputEvent(x, y, z, id, Eegeo::Windows::Input::TouchScreenInputAction::TouchScreenMove));
        }

        void MapImage::SetAllInputEventsToPointerUp(int x, int y)
        {
            m_appRunner->SetAllInputEventsToPointerUp(ScaledScreenCoord(x), ScaledScreenCoord(y));
        }

        void MapImage::SetAllTouchInputEventsToPointerUp(int touchId)
        {
            m_appRunner->SetAllTouchInputEventsToPointerUp(touchId);
        }

        void MapImage::RespondToResize(int width, int  height)
        {
            const int scaledWidth = ScaledScreenCoord(width);
            const int scaledHeight = ScaledScreenCoord(height);

            m_appRunner->RespondToSize(scaledWidth, scaledHeight);

            void* surfaceSharePointer = m_appRunner->GetMainRenderSurfaceSharePointer();
            IDirect3DSurface9* surface = GetSurfaceFromShareHandle(surfaceSharePointer, scaledWidth, scaledHeight);
            Lock();
            SetBackBuffer(System::Windows::Interop::D3DResourceType::IDirect3DSurface9, System::IntPtr(surface));
            Unlock();

            surface->Release();
        }

        bool MapImage::ShouldStartFullscreen()
        {
            return m_appRunner->ShouldStartFullscreen();
        }

        void MapImage::SetFullscreen(bool fullscreen)
        {
            m_appRunner->SetFullscreen(fullscreen);
        }

        int MapImage::GetScreenDPI()
        {
            SetProcessDPIAware();
            HDC screen = GetDC(NULL);
            return GetDeviceCaps(screen, LOGPIXELSX);
        }
    }
}
