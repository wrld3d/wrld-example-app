// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "FlattenButton.h"
#include "FlattenButtonViewIncludes.h"

@class FlattenButtonView;

@interface FlattenButtonViewController : UIViewController
{
    ExampleApp::FlattenButton::IFlattenButtonModel* m_pModel;
    ExampleApp::FlattenButton::IFlattenButtonViewModel* m_pViewModel;
    ExampleApp::FlattenButton::FlattenButtonViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::FlattenButton::IFlattenButtonViewModel*)pViewModel
                    :(ExampleApp::FlattenButton::IFlattenButtonModel*)pModel
                    :(FlattenButtonView*)pButtonView;

- (void) setSelected:(BOOL)selected;

- (void) handleScreenStateChanged:(float)onScreenState;

- (void) handleModelStateChanged:(BOOL)flattened;

@property (nonatomic, retain) FlattenButtonView* pButtonView;

@end
