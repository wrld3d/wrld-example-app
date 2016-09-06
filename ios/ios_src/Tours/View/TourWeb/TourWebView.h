// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
#pragma once

#import <UIKit/UIKit.h>
#include <string>

@interface TourWebView : UIView<UIGestureRecognizerDelegate, UIWebViewDelegate>
{
    UITapGestureRecognizer* m_tapGestureRecogniser;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_yPosActive;
    float m_yPosInactive;
    
    CGRect m_frameOn;
    CGRect m_frameOff;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale;

- (void) show:(const std::string&)urlString;

- (void) hide;

- (void) updateButtons;

@property (nonatomic, retain) UIWebView* pWebView;
@property (nonatomic, retain) UIButton* pForwardButton;
@property (nonatomic, retain) UIButton* pBackButton;

@end
