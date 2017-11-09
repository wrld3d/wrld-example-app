// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Graphics.h"
#include "AppHost.h"
#include "GlDisplayService.h"
#include "Types.h"

@class ViewController;

class AppRunner : Eegeo::NonCopyable
{
public:
    AppRunner(
        ViewController& pViewController,
        UIView* pView,
        const ExampleApp::ApplicationConfig::ApplicationConfiguration& applicationConfiguration,
        ExampleApp::Metrics::iOSFlurryMetricsService& metricsService
    );
    ~AppRunner();

    bool IsRunning();

    void Pause();
    void Resume();
    void Update(float deltaSeconds);


    void NotifyViewLayoutChanged();

    bool ShouldAutoRotateToInterfaceOrientation(UIInterfaceOrientation interfaceOrientation);
    
    void HandleUrlOpen(const AppInterface::UrlData& data);
    void RequestLocationPermission();

private:
    ViewController& m_viewController;
    UIView* m_pView;
    const ExampleApp::ApplicationConfig::ApplicationConfiguration& m_applicationConfiguration;
    ExampleApp::Metrics::iOSFlurryMetricsService& m_metricsService;

    GlDisplayService m_displayService;
    void ReleaseDisplay();
    bool TryBindDisplay();

    AppHost* m_pAppHost;
    void CreateAppHost();
};

