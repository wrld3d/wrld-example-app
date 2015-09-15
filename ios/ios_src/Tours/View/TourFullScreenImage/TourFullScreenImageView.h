// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"
#include "TourFullScreenImageViewIncludes.h"

@class TourFullScreenImageView;

@interface TourFullScreenImageView : UIView <UIGestureRecognizerDelegate>

- (id) initWithParams:(float)width :(float)height :(float)pixelScale;

- (ExampleApp::Tours::View::TourFullScreenImage::TourFullScreenImageViewInterop*) getInterop;

- (void) beginCeremony:(const std::string&)asset :(const std::string&)message;

- (void) endCeremony;

- (BOOL) consumesTouch:(UITouch *)touch;

@property (nonatomic, retain) UIView* pMainControlContainer;
@property (nonatomic, retain) UIImageView* pBackgroundImage;
@property (nonatomic, retain) UILabel* pMessage;

@end
