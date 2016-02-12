#include "MapImage.h"

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

        void MapImage::Init(int width, int height)
        {
            System::Windows::Application^ app = System::Windows::Application::Current;
            System::Windows::Interop::WindowInteropHelper^ windowInteropHelper = gcnew System::Windows::Interop::WindowInteropHelper(app->MainWindow);

            HWND windowHandle = (HWND)windowInteropHelper->Handle.ToPointer();

            if (m_pState == NULL)
            {
                m_pState = new WindowsNativeState();
            }

            m_pState->appName = "WPFControl";
            m_pState->deviceDpi = static_cast<float>(GetScreenDPI());
            m_pState->deviceModel = "WPFControl";
            m_pState->fullScreen = false;
            m_pState->hinstance = GetModuleHandle(NULL);
            m_pState->requiresPBuffer = true;
            m_pState->screenWidth = width;
            m_pState->screenHeight = height;
            m_pState->window = windowHandle;			

            m_appRunner = new AppRunner(m_pState);
            m_appRunner->ActivateSurface();
            m_appRunner->ActivateSharedSurface();

            InitDirect3D(windowHandle);			

			InitBackBuffer();
        }

		void MapImage::InitBackBuffer()
		{
			void* surfaceSharePointer = m_appRunner->GetMainRenderSurfaceSharePointer();
			IDirect3DSurface9* surface = GetSurfaceFromShareHandle(surfaceSharePointer, m_pState->screenWidth, m_pState->screenHeight);
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

        void MapImage::HandlePanStartEvent(int x, int y)
        {
            m_appRunner->HandlePanStartEvent(x, y);
        }

        void MapImage::HandlePanEndEvent(int x, int y)
        {
            m_appRunner->HandlePanEndEvent(x, y);
        }

        void MapImage::HandleRotateStartEvent(int x, int y)
        {
            m_appRunner->HandleRotateStartEvent(x, y);
        }

        void MapImage::HandleRotateEndEvent(int x, int y)
        {
            m_appRunner->HandleRotateEndEvent(x, y);
        }

        void MapImage::HandleTiltStart(int x, int y)
        {
            m_appRunner->HandleTiltStart(x, y);
        }

        void MapImage::HandleTiltEnd(int x, int y)
        {
            m_appRunner->HandleTiltEnd(x, y);
        }

        void MapImage::HandleKeyboardDownEvent(int asciiKeyCode)
        {
            m_appRunner->HandleKeyboardDownEvent(asciiKeyCode);
        }

        void MapImage::HandleMouseMoveEvent(int x, int y)
        {
            m_appRunner->HandleMouseMoveEvent(x, y);
        }

        void MapImage::HandleZoomEvent(int delta, int zoomDistance, int x, int y)
        {
            m_appRunner->HandleZoomEvent(delta, zoomDistance, x, y);
        }

        void MapImage::SetAllInputEventsToPointerUp(int x, int y)
        {
            m_appRunner->SetAllInputEventsToPointerUp(x, y);
        }

        void MapImage::RespondToResize(int width, int  height)
        {
            m_appRunner->RespondToSize(width, height);

            void* surfaceSharePointer = m_appRunner->GetMainRenderSurfaceSharePointer();
            IDirect3DSurface9* surface = GetSurfaceFromShareHandle(surfaceSharePointer, width, height);
            Lock();
            SetBackBuffer(System::Windows::Interop::D3DResourceType::IDirect3DSurface9, System::IntPtr(surface));
            Unlock();

            surface->Release();
        }

        int MapImage::GetScreenDPI()
        {
            SetProcessDPIAware();
            HDC screen = GetDC(NULL);
            return GetDeviceCaps(screen, LOGPIXELSX);
        }
    }
}
