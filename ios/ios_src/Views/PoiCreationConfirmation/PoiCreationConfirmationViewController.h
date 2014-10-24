// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "PoiCreation.h"
#include "PoiCreationDetails.h"
#include "PoiCreationConfirmationViewIncludes.h"
#include "Rendering.h"

@class PoiCreationConfirmationView;

@interface PoiCreationConfirmationViewController : UIViewController
{
    ExampleApp::PoiCreation::IPoiCreationModel* m_pModel;
    ExampleApp::PoiCreation::IPoiCreationConfirmationViewModel* m_pViewModel;
    ExampleApp::PoiCreationDetails::IPoiCreationDetailsViewModel* m_pDetailsViewModel;
    ExampleApp::PoiCreation::PoiCreationConfirmationViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::PoiCreation::IPoiCreationModel*)pModel
                    :(ExampleApp::PoiCreation::IPoiCreationConfirmationViewModel*)pViewModel
                    :(ExampleApp::PoiCreation::IPoiCreationCompositeViewModel*)pCompositeViewModel
                    :(ExampleApp::PoiCreationDetails::IPoiCreationDetailsViewModel*)pDetailsViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties;

- (void) handleScreenStateChanged:(float)onScreenState;

//- (void) setSelected:(BOOL)selected;

- (void) handleCloseButtonSelected;

- (void) handleConfirmButtonSelected;

@property (nonatomic, retain) PoiCreationConfirmationView* pPoiCreationConfirmationView;

@end
