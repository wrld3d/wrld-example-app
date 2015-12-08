// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"
#include "WorldPinOnMapViewIncludes.h"
#include "ColorHelpers.h"
#include "WorldPinOnMapView.h"
#include "IWorldPinsInFocusModel.h"

@class TourHovercardView;
@class ImageStore;

@interface TwitterTourHovercard : UIView <UIGestureRecognizerDelegate, WorldPinOnMapView>
{
    UIImage* m_pPlayIconImage;
}

- (id) initWithParams:(float)pinDiameter :(float)pixelScale :(ImageStore*)pImageStore  :(ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*)interop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel;

- (void) setFullyActive :(float)modality;

- (void) setFullyInactive;

- (void) updatePosition:(float)x :(float)y;

@property (nonatomic, retain) UIView* pMainControlContainer;
@property (nonatomic, retain) UIView* pMainControlShadowContainer;
@property (nonatomic, retain) UIView* pMainShape;
@property (nonatomic, retain) UIView* pTopStrip;
@property (nonatomic, retain) UIView* pLabelBack;
@property (nonatomic, retain) UIImageView* pArrowContainer;
@property (nonatomic, retain) UIImageView* pImage;
@property (nonatomic, retain) UIImageView* pVideoArrowImage;
@property (nonatomic, retain) UIActivityIndicatorView* pImageLoadingSpinner;

@end
