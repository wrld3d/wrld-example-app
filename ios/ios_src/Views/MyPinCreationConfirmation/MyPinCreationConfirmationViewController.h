// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreationConfirmationViewIncludes.h"
#include "Rendering.h"
#include "UiToNativeMessageBus.h"

@class MyPinCreationConfirmationView;

@interface MyPinCreationConfirmationViewController : UIViewController
{
    ExampleApp::ExampleAppMessaging::UiToNativeMessageBus* m_pUiToNativeMessageBus;
    ExampleApp::MyPinCreation::IMyPinCreationConfirmationViewModel* m_pViewModel;
    ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModel* m_pDetailsViewModel;
    ExampleApp::MyPinCreation::MyPinCreationConfirmationViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*)pUiToNativeMessageBus
                    :(ExampleApp::MyPinCreation::IMyPinCreationConfirmationViewModel*)pViewModel
                    :(ExampleApp::MyPinCreation::IMyPinCreationCompositeViewModel*)pCompositeViewModel
                    :(ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModel*)pDetailsViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties;

- (void) handleScreenStateChanged:(float)onScreenState;

- (void) handleCloseButtonSelected;

- (void) handleConfirmButtonSelected;

@property (nonatomic, retain) MyPinCreationConfirmationView* pMyPinCreationConfirmationView;

@end
