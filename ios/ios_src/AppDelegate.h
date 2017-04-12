// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#import <HockeySDK/HockeySDK.h>

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
}
	

@property (strong, nonatomic) UIWindow *window;

@property (nonatomic) ExampleApp::Metrics::iOSFlurryMetricsService* metricsService;

@property (nonatomic) ExampleApp::ApplicationConfig::ApplicationConfiguration* applicationConfiguration;

@property (nonatomic, readonly) NSURL* launchUrl;

@end
