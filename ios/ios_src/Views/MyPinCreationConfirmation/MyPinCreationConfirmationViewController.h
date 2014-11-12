// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "MyPinCreationConfirmationViewIncludes.h"
#include "Rendering.h"

@class MyPinCreationConfirmationView;

@interface MyPinCreationConfirmationViewController : UIViewController
{
    ExampleApp::MyPinCreation::IMyPinCreationModel* m_pModel;
    ExampleApp::MyPinCreation::IMyPinCreationConfirmationViewModel* m_pViewModel;
    ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModel* m_pDetailsViewModel;
    ExampleApp::MyPinCreation::MyPinCreationConfirmationViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::MyPinCreation::IMyPinCreationModel*)pModel
                    :(ExampleApp::MyPinCreation::IMyPinCreationConfirmationViewModel*)pViewModel
                    :(ExampleApp::MyPinCreation::IMyPinCreationCompositeViewModel*)pCompositeViewModel
                    :(ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModel*)pDetailsViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties;

- (void) handleScreenStateChanged:(float)onScreenState;

- (void) handleCloseButtonSelected;

- (void) handleConfirmButtonSelected;

@property (nonatomic, retain) MyPinCreationConfirmationView* pMyPinCreationConfirmationView;

@end
