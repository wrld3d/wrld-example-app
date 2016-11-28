// Copyright eeGeo Ltd (2012-2014), All Rights Reserved
#include "ApplicationConfig.h"
#pragma once

#import <UIKit/UIKit.h>

namespace ExampleApp
{
    namespace Metrics
    {
        class iOSFlurryMetricsService;
    }
    
    namespace ApplicationConfig
    {
        class ApplicationConfiguration;
    }
}

@interface AppDelegate : UIResponder <UIApplicationDelegate> {
    ExampleApp::ApplicationConfig::SdkModel::IApplicationConfigurationVersionProvider* _pIOSVersionProvider;
}

- (void) LoadAppConfig:(NSURL*) deepLinkUrl;
- (void) OnLoadAppConfig:(const ExampleApp::ApplicationConfig::ApplicationConfiguration&) appConfig;

@property (strong, nonatomic) UIWindow *window;

@property (nonatomic) ExampleApp::Metrics::iOSFlurryMetricsService* metricsService;

@property (nonatomic) ExampleApp::ApplicationConfig::ApplicationConfiguration* applicationConfiguration;

@property (nonatomic, readonly) NSURL* launchUrl;

@end
