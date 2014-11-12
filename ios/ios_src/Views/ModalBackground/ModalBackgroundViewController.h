// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "ModalBackgroundViewModule.h"

@class ModalBackgroundViewController;
class ModalBackgroundViewControllerInterop;

@interface ModalBackgroundViewController : UIViewController
{
	ExampleApp::Modality::IModalityModel* m_pModalityModel;
	ModalBackgroundViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::Modality::IModalityModel *)pModalityModel;

- (void) handleOpenStateChanged:(float)openState;

@property (nonatomic, retain) ModalBackgroundView* pModalBackgroundView;

@end
