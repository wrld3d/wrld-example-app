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
        AndroidNativeState* pNativeState
    );
    ~AppRunner();

    void Pause();
    void Resume();
    void ActivateSurface();
    void UpdateNative(float deltaSeconds);
    void UpdateUiViews(float deltaSeconds);
    void StopUpdatingNativeBeforeTeardown();
    void DestroyApplicationUi();
    void HandleUrlOpenEvent(const AppInterface::UrlData& data);

    void HandleTouchEvent(const Eegeo::Android::Input::TouchInputEvent& message);

private:
    AndroidNativeState* m_pNativeState;
    AppHost* m_pAppHost;
    bool m_updatingNative;
    bool m_isPaused;

    GlDisplayService m_displayService;
    void ReleaseDisplay();
    bool TryBindDisplay();
    void CreateAppHost();
};
