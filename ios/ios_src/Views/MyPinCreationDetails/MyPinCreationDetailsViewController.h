// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "MyPinCreationDetails.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetailsViewIncludes.h"

@class MyPinCreationDetailsView;

@interface MyPinCreationDetailsViewController : UIViewController
{
    ExampleApp::MyPinCreation::IMyPinCreationModel* m_pModel;
    ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModel* m_pViewModel;
    ExampleApp::MyPinCreationDetails::MyPinCreationDetailsViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::MyPinCreation::IMyPinCreationModel*)pModel
                    :(ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModel*)pViewModel;

- (void) open;

- (void) close;

- (void) handleClosedButtonPressed;

- (void) handleConfirmButtonPressed:(NSString*) title
                                   :(NSString*) description
                                   :(UIImage*)image
                                   :(BOOL)shouldShare;

@property (nonatomic, retain) MyPinCreationDetailsView* pMyPinCreationDetailsView;

@end
