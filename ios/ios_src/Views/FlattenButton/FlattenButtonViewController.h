// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "FlattenButton.h"
#include "FlattenButtonViewIncludes.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"

@class FlattenButtonView;

@interface FlattenButtonViewController : UIViewController
{
	ExampleApp::FlattenButton::IFlattenButtonModel* m_pModel;
	ExampleApp::FlattenButton::IFlattenButtonViewModel* m_pViewModel;
	ExampleApp::FlattenButton::FlattenButtonViewControllerInterop* m_pInterop;
	ExampleApp::ExampleAppMessaging::UiToNativeMessageBus* m_pUiToNativeMessageBus;
}

- (id)initWithParams:(ExampleApp::FlattenButton::IFlattenButtonViewModel*)pViewModel
    :(ExampleApp::FlattenButton::IFlattenButtonModel*)pModel
    :(FlattenButtonView*)pButtonView
    :(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*)pUiToNativeMessageBus
    :(ExampleApp::ExampleAppMessaging::NativeToUiMessageBus*)pNativeToUiMessageBus;

- (void) setSelected:(BOOL)selected;

- (void) handleScreenStateChanged:(float)onScreenState;

- (void) handleModelStateChanged:(BOOL)flattened;

@property (nonatomic, retain) FlattenButtonView* pButtonView;

@end
