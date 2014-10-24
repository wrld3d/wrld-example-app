// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "PoiCreation.h"
#include "PoiCreationButtonViewIncludes.h"
#include "Rendering.h"

@class PoiCreationButtonView;

@interface PoiCreationButtonViewController : UIViewController
{
    ExampleApp::PoiCreation::IPoiCreationModel* m_pModel;
    ExampleApp::PoiCreation::IPoiCreationButtonViewModel* m_pViewModel;
    ExampleApp::PoiCreation::PoiCreationButtonViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::PoiCreation::IPoiCreationModel*)pModel
                    :(ExampleApp::PoiCreation::IPoiCreationButtonViewModel*)pViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties;

- (void) handleScreenStateChanged:(float)onScreenState;

- (void) setSelected:(BOOL)selected;

@property (nonatomic, retain) PoiCreationButtonView* pPoiCreationButtonView;

@end
