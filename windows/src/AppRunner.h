// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "MouseInputEvent.h"
#include "TouchScreenInputEvent.h"
#include "Types.h"

class AppRunnerImpl;

class AppRunner : Eegeo::NonCopyable
{
public:
    AppRunner(
        WindowsNativeState* pNativeState,
        bool hasNativeTouchInput,
        int maxDeviceTouchCount
    );
    ~AppRunner();

    void Pause();
    void Resume();
    bool ActivateSurface();
    void UpdateNative(float deltaSeconds);
    void UpdateUiViews(float deltaSeconds);
    void StopUpdatingNativeBeforeTeardown();
    void DestroyApplicationUi();

    void HandleMouseEvent(const Eegeo::Windows::Input::MouseInputEvent& message);
    void HandleKeyboardDownEvent(char keyCode);
    void HandleKeyboardUpEvent(char keyCode);
    void HandleTouchEvent(const Eegeo::Windows::Input::TouchScreenInputEvent& message);

    void ActivateSharedSurface();
    void* GetMainRenderSurfaceSharePointer();

    bool IsRunning();
    void Exit();

    void SetAllInputEventsToPointerUp(int x, int y);
    void SetTouchInputEventToPointerUp(int touchId);
    void PopAllTouchEvents();
    void RespondToResize();
    void RespondToSize(int width, int height);

    bool ShouldStartFullscreen() const;

    void SetFullscreen(bool fullscreen);

private:
    AppRunnerImpl* m_pImpl;
};