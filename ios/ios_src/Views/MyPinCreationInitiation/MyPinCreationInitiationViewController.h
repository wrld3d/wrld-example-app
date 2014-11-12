// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "MyPinCreation.h"
#include "MyPinCreationInitiationViewIncludes.h"
#include "Rendering.h"

@class MyPinCreationInitiationView;

@interface MyPinCreationInitiationViewController : UIViewController
{
    ExampleApp::MyPinCreation::IMyPinCreationModel* m_pModel;
    ExampleApp::MyPinCreation::IMyPinCreationInitiationViewModel* m_pViewModel;
    ExampleApp::MyPinCreation::MyPinCreationInitiationViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::MyPinCreation::IMyPinCreationModel*)pModel
                    :(ExampleApp::MyPinCreation::IMyPinCreationInitiationViewModel*)pViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties;

- (void) handleScreenStateChanged:(float)onScreenState;

- (void) setSelected:(BOOL)selected;

@property (nonatomic, retain) MyPinCreationInitiationView* pMyPinCreationInitiationView;

@end
