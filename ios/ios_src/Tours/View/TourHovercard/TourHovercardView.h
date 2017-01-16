// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"
#include "ColorHelpers.h"
#include "IWorldPinsInFocusModel.h"

@class TourHovercardView;
@class ImageStore;

@interface TourHovercardView : UIView <UIGestureRecognizerDelegate>
{
}

- (id) initWithParams:(float)pinDiameter :(float)pixelScale :(ImageStore*)pImageStore;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel;

- (void) setFullyActive :(float)modality;

- (void) setFullyInactive;

- (void) updatePosition:(float)x :(float)y;

- (void) setPresentationColors :(ExampleApp::Helpers::ColorHelpers::Color)baseColor :(ExampleApp::Helpers::ColorHelpers::Color)textColor;

@property (nonatomic, retain) UIView* pMainControlContainer;
@property (nonatomic, retain) UIView* pMainControlShadowContainer;
@property (nonatomic, retain) UIView* pMainShape;
@property (nonatomic, retain) UIView* pTopStrip;
@property (nonatomic, retain) UIView* pLabelBack;
@property (nonatomic, retain) UIImageView* pArrowContainer;
@property (nonatomic, retain) UILabel* pNameLabel;
@property (nonatomic, retain) UILabel* pInfoLabel;

@end
