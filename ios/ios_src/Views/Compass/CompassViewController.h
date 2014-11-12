// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "Compass.h"
#include "CompassViewIncludes.h"
#include "Rendering.h"
#include "NativeToUiMessageBus.h"
#include "UiToNativeMessageBus.h"

@class CompassView;

@interface CompassViewController : UIViewController
{
	ExampleApp::Compass::ICompassViewModel* m_pViewModel;
	ExampleApp::Compass::CompassViewControllerInterop* m_pInterop;
	ExampleApp::ExampleAppMessaging::UiToNativeMessageBus* m_pUiToNativeMessageBus;
}

- (id)initWithParams:(ExampleApp::Compass::ICompassViewModel*)pViewModel
    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties
    :(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*)pUiToNativeMessageBus
    :(ExampleApp::ExampleAppMessaging::NativeToUiMessageBus*)pNativeToUiMessageBus;

- (void) handleGpsModeChanged:(ExampleApp::Compass::GpsMode::Values)value;

- (void) updateHeading:(float)angleRadians;

- (void) handleScreenStateChanged:(float)onScreenState;

@property (nonatomic, retain) CompassView* pCompassView;

@end
