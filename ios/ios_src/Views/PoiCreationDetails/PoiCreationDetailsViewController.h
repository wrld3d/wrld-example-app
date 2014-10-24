// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <Foundation/Foundation.h>
#include "PoiCreationDetails.h"
#include "PoiCreation.h"
#include "PoiCreationDetailsViewIncludes.h"

@class PoiCreationDetailsView;

@interface PoiCreationDetailsViewController : UIViewController
{
    ExampleApp::PoiCreation::IPoiCreationModel* m_pModel;
    ExampleApp::PoiCreationDetails::IPoiCreationDetailsViewModel* m_pViewModel;
    ExampleApp::PoiCreationDetails::PoiCreationDetailsViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(ExampleApp::PoiCreation::IPoiCreationModel*)pModel
                    :(ExampleApp::PoiCreationDetails::IPoiCreationDetailsViewModel*)pViewModel;

- (void) open;

- (void) close;

- (void) handleClosedButtonPressed;

- (void) handleConfirmButtonPressed:(NSString*) title
                                   :(NSString*) description
                                   :(UIImage*)image
                                   :(BOOL)shouldShare;

@property (nonatomic, retain) PoiCreationDetailsView* pPoiCreationDetailsView;

@end
