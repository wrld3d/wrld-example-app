// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "MyPinDetailsView.h"
#include "SearchResultModel.h"
#include "IMyPinDetailsViewModel.h"
#include "UiToNativeMessageBus.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		class MyPinDetailsViewControllerInterop;
	}
}

@interface MyPinDetailsViewController : UIViewController
{
	ExampleApp::MyPinDetails::IMyPinDetailsViewModel* m_pMyPinDetailsViewModel;
	ExampleApp::MyPinDetails::MyPinDetailsViewControllerInterop* m_pInterop;
    ExampleApp::ExampleAppMessaging::UiToNativeMessageBus* m_pUiToNativeMessageBus;
}

- (id)initWithParams:(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*) pUiToNativeMessageBus
                    :(ExampleApp::MyPinDetails::IMyPinDetailsViewModel*) pMyPinDetailsViewModel;

- (void) openWithModel:(const ExampleApp::MyPins::MyPinModel&)myPinModel;

- (void) close;

- (void) handleCloseButtonPressed;

- (void) handleRemovePinButtonPressed;

@property (nonatomic, retain) MyPinDetailsView* pMyPinDetailsView;

@end
