// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppRunner.h"
#include "Graphics.h"
#include "AndroidThreadHelper.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "ImagePathHelpers.h"

AppRunner::AppRunner
(
    AndroidNativeState* pNativeState
)
    : m_pNativeState(pNativeState)
    , m_pAppHost(NULL)
    , m_updatingNative(true)
    , m_isPaused(false)
{
    ASSERT_NATIVE_THREAD

    Eegeo::Helpers::ThreadHelpers::SetThisThreadAsMainThread();
}

AppRunner::~AppRunner()
{
    ASSERT_NATIVE_THREAD

    bool destroyEGL = true;
    m_displayService.ReleaseDisplay(destroyEGL);

    if(m_pAppHost != NULL)
    {
        Eegeo_DELETE(m_pAppHost);
    }
}

void AppRunner::CreateAppHost()
{
    ASSERT_NATIVE_THREAD

    if(m_pAppHost == NULL && m_displayService.IsDisplayAvailable())
    {
        const Eegeo::Rendering::ScreenProperties& screenProperties = Eegeo::Rendering::ScreenProperties::Make(
                    m_displayService.GetDisplayWidth(),
                    m_displayService.GetDisplayHeight(),
                    ExampleApp::Helpers::ImageHelpers::GetPixelScale(),
                    m_pNativeState->deviceDpi);
        m_pAppHost = Eegeo_NEW(AppHost)
                     (
                         *m_pNativeState,
                         screenProperties,
                         m_displayService.GetDisplay(),
                         m_displayService.GetSharedSurface(),
                         m_displayService.GetResourceBuildSharedContext()
                     );
    }
}

void AppRunner::Pause()
{
    ASSERT_NATIVE_THREAD

    if(m_pAppHost != NULL && !m_isPaused)
    {
        m_pAppHost->OnPause();
        m_isPaused = true;
    }

    ReleaseDisplay();
}

void AppRunner::Resume()
{
    ASSERT_NATIVE_THREAD

    if(m_pAppHost != NULL && m_isPaused)
    {
        m_pAppHost->OnResume();
    }

    m_isPaused = false;
}

void AppRunner::HandleUrlOpenEvent(const AppInterface::UrlData& data)
{
    ASSERT_NATIVE_THREAD

    if(m_pAppHost != NULL)
    {
        m_pAppHost->HandleOpenUrlEvent(data);
    }
}

void AppRunner::ActivateSurface()
{
    ASSERT_NATIVE_THREAD

    Pause();
    bool displayBound = TryBindDisplay();
    Eegeo_ASSERT(displayBound, "Failed to bind display");
    CreateAppHost();
    Resume();
}

void AppRunner::HandleTouchEvent(const Eegeo::Android::Input::TouchInputEvent& event)
{
    ASSERT_NATIVE_THREAD

    if(m_pAppHost != NULL)
    {
        m_pAppHost->HandleTouchInputEvent(event);
    }
}

void AppRunner::ReleaseDisplay()
{
    ASSERT_NATIVE_THREAD

    if(m_displayService.IsDisplayAvailable())
    {
        const bool teardownEGL = false;
        m_displayService.ReleaseDisplay(teardownEGL);
    }
}

bool AppRunner::TryBindDisplay()
{
    ASSERT_NATIVE_THREAD

    if(m_displayService.TryBindDisplay(*(m_pNativeState->window)))
    {
        if(m_pAppHost != NULL)
        {
            m_pAppHost->SetSharedSurface(m_displayService.GetSharedSurface());
            const Eegeo::Rendering::ScreenProperties& screenProperties = Eegeo::Rendering::ScreenProperties::Make(
                        m_displayService.GetDisplayWidth(),
                        m_displayService.GetDisplayHeight(),
                        ExampleApp::Helpers::ImageHelpers::GetPixelScale(),
                        m_pNativeState->deviceDpi);
            m_pAppHost->NotifyScreenPropertiesChanged(screenProperties);
            m_pAppHost->SetViewportOffset(0, 0);
        }

        return true;
    }

    return false;
}

void AppRunner::UpdateNative(float deltaSeconds)
{
    ASSERT_NATIVE_THREAD

    if(m_updatingNative && m_pAppHost != NULL && m_displayService.IsDisplayAvailable())
    {
        m_pAppHost->Update(deltaSeconds);

        Eegeo_GL(eglSwapBuffers(m_displayService.GetDisplay(), m_displayService.GetSurface()));
        Eegeo::Helpers::GLHelpers::ClearBuffers();

        m_pAppHost->Draw(deltaSeconds);
    }
}

void AppRunner::UpdateUiViews(float deltaSeconds)
{
    ASSERT_UI_THREAD

    if(m_pAppHost != NULL)
    {
        m_pAppHost->UpdateUiViewsFromUiThread(deltaSeconds);
    }
}

void AppRunner::StopUpdatingNativeBeforeTeardown()
{
    ASSERT_NATIVE_THREAD

    Eegeo_ASSERT(m_updatingNative, "Should only call StopUpdatingNativeBeforeTeardown once, before teardown.\n");
    m_updatingNative = false;
}

void AppRunner::DestroyApplicationUi()
{
    ASSERT_UI_THREAD

    if(m_pAppHost != NULL)
    {
        m_pAppHost->DestroyUiFromUiThread();
    }
}
