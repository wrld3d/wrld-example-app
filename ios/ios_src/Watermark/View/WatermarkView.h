// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#import <UIKit/UIKit.h>
#include "WatermarkViewIncludes.h"

@class WatermarkView;

@interface WatermarkView : UIButton
{
    ExampleApp::Watermark::View::WatermarkViewInterop* m_pInterop;
    UIViewController* m_pController;

    UIColor* m_pColour;

    float m_width;
    float m_height;

    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_yPosActive;
    float m_yPosInactive;

    float m_stateChangeAnimationTimeSeconds;
    
    std::string m_imageAssetName;
    std::string m_popupTitle;
    std::string m_popupBody;
    std::string m_webUrl;
    bool m_shouldShowShadow;
}

- (ExampleApp::Watermark::View::WatermarkViewInterop*) getInterop;

- (id) initWithDimensions:(float)width
                         :(float)height
                         :(float)pixelScale
                         :(const ExampleApp::Watermark::View::WatermarkData&) watermarkData;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateToY:(float)y;

- (void) updateWatermarkData: (const ExampleApp::Watermark::View::WatermarkData&) watermarkData;

@end
