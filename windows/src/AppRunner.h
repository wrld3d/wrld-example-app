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
        WindowsNativeState* pNativeState
    );
    ~AppRunner();

    void Pause();
    void Resume();
    bool ActivateSurface();
    void UpdateNative(float deltaSeconds);
    void UpdateUiViews(float deltaSeconds);
    void StopUpdatingNativeBeforeTeardown();
    void DestroyApplicationUi();

    void HandleTouchEvent(const Eegeo::Windows::Input::TouchInputEvent& message);
    void HandlePanStartEvent(int x, int y);
    void HandlePanEndEvent(int x, int y);
    void HandleMouseMoveEvent(int x, int y);
    void HandleRotateStartEvent(int x, int y);
    void HandleRotateEndEvent(int x, int y);
    void HandleZoomEvent(short scrollWheelDirection, int zoomDistance, int x, int y);
    void HandleKeyboardDownEvent(char keyCode);
    void HandleKeyboardUpEvent(char keyCode);
    void HandleTiltStart(int x, int y);
    void HandleTiltEnd(int x, int y);

    void ActivateSharedSurface();
    void* GetMainRenderSurfaceSharePointer();

    bool IsRunning();
    void Exit();

    void SetAllInputEventsToPointerUp(int x, int y);
    void RespondToResize();
    void RespondToSize(int width, int height);

private:
    WindowsNativeState* m_pNativeState;
    AppHost* m_pAppHost;
    bool m_updatingNative;
    bool m_isPaused;
    bool m_appRunning;

    GlDisplayService m_displayService;
    void ReleaseDisplay();
    bool TryBindDisplay();
    void CreateAppHost();
};
