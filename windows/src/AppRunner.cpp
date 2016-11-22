// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppRunner.h"
#include "AppRunnerImpl.h"

AppRunner::AppRunner
(
    WindowsNativeState* pNativeState,
    bool hasNativeTouchInput,
    int maxDeviceTouchCount
)
{
    m_pImpl = Eegeo_NEW(AppRunnerImpl)(pNativeState, hasNativeTouchInput, maxDeviceTouchCount);
}

AppRunner::~AppRunner()
{
    Eegeo_DELETE m_pImpl;
}

void AppRunner::Pause()
{
    m_pImpl->Pause();
}

void AppRunner::Resume()
{
    m_pImpl->Resume();
}

bool AppRunner::ActivateSurface()
{
    return m_pImpl->ActivateSurface();
}

void AppRunner::HandleMouseEvent(const Eegeo::Windows::Input::MouseInputEvent& event)
{
    m_pImpl->HandleMouseEvent(event);
}


void AppRunner::HandleKeyboardDownEvent(char keyCode)
{
    m_pImpl->HandleKeyboardDownEvent(keyCode);
}

void AppRunner::HandleKeyboardUpEvent(char keyCode)
{
    m_pImpl->HandleKeyboardUpEvent(keyCode);
}

void AppRunner::HandleTouchEvent(const Eegeo::Windows::Input::TouchScreenInputEvent& event)
{
    m_pImpl->HandleTouchEvent(event);
}

void AppRunner::ActivateSharedSurface()
{
    m_pImpl->ActivateSharedSurface();
}

bool AppRunner::IsRunning()
{
    return m_pImpl->IsRunning();
}

void AppRunner::Exit()
{
    m_pImpl->Exit();
}

void AppRunner::SetAllInputEventsToPointerUp(int x, int y)
{
    m_pImpl->SetAllInputEventsToPointerUp(x, y);
}

void AppRunner::SetTouchInputEventToPointerUp(int touchId)
{
    m_pImpl->SetTouchInputEventToPointerUp(touchId);
}

void AppRunner::PopAllTouchEvents()
{
    m_pImpl->PopAllTouchEvents();
}

void AppRunner::UpdateNative(float deltaSeconds)
{
    m_pImpl->UpdateNative(deltaSeconds);
}

void AppRunner::UpdateUiViews(float deltaSeconds)
{
    m_pImpl->UpdateUiViews(deltaSeconds);
}

void AppRunner::StopUpdatingNativeBeforeTeardown()
{
    m_pImpl->StopUpdatingNativeBeforeTeardown();
}

void AppRunner::DestroyApplicationUi()
{
    m_pImpl->DestroyApplicationUi();
}

void AppRunner::RespondToResize()
{
    m_pImpl->RespondToResize();
}

void AppRunner::RespondToSize(int width, int height)
{
    m_pImpl->RespondToSize(width, height);
}

void* AppRunner::GetMainRenderSurfaceSharePointer()
{
    return m_pImpl->GetMainRenderSurfaceSharePointer();
}

bool AppRunner::ShouldStartFullscreen() const
{
    return m_pImpl->ShouldStartFullscreen();
}

void AppRunner::SetFullscreen(bool fullscreen)
{
    m_pImpl->SetFullscreen(fullscreen);
}
