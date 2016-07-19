// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Graphics.h"
#include "AppHost.h"
#include "GlDisplayService.h"
#include "Types.h"

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
    void SetAllTouchInputEventsToPointerUp(int touchId);
    void RespondToResize();
    void RespondToSize(int width, int height);

    bool ShouldStartFullscreen() const;

    void SetFullscreen(bool fullscreen);

private:
    WindowsNativeState* m_pNativeState;
    AppHost* m_pAppHost;
    bool m_updatingNative;
    bool m_isPaused;
    bool m_appRunning;
    bool m_hasNativeTouch;
    int m_maxDeviceTouchCount;

    GlDisplayService m_displayService;
    void ReleaseDisplay();
    bool TryBindDisplay();
    void CreateAppHost();

    WINDOWPLACEMENT m_wpPrev;
};
