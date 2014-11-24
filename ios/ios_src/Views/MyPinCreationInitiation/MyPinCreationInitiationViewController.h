// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "MyPinCreation.h"
#include "MyPinCreationInitiationViewIncludes.h"
#include "Rendering.h"
#include "UiToNativeMessageBus.h"

@class MyPinCreationInitiationView;

@interface MyPinCreationInitiationViewController : UIViewController
{
    ExampleApp::ExampleAppMessaging::UiToNativeMessageBus* m_pUiToNativeMessageBus;
    ExampleApp::MyPinCreation::IMyPinCreationInitiationViewModel* m_pViewModel;
    ExampleApp::MyPinCreation::IMyPinCreationConfirmationViewModel* m_pConfirmationViewModel;
    ExampleApp::MyPinCreation::MyPinCreationInitiationViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*) pUiToNativeMessageBus
                    :(ExampleApp::MyPinCreation::IMyPinCreationInitiationViewModel*)pViewModel
                    :(ExampleApp::MyPinCreation::IMyPinCreationConfirmationViewModel*) pConfirmationViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties;

- (void) handleScreenStateChanged:(float)onScreenState;

- (void) setSelected:(BOOL)selected;

@property (nonatomic, retain) MyPinCreationInitiationView* pMyPinCreationInitiationView;

@end
