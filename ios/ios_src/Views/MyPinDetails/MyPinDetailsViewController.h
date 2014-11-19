// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "MyPinDetailsView.h"
#include "SearchResultModel.h"
#include "IMyPinDetailsViewModel.h"

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
}

- (id)initWithParams:(ExampleApp::MyPinDetails::IMyPinDetailsViewModel*)pMyPinDetailsViewModel;

- (void) openWithModel:(const ExampleApp::MyPins::MyPinModel&)myPinModel;

- (void) close;

@property (nonatomic, retain) MyPinDetailsView* pMyPinDetailsView;

@end
