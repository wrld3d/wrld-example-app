// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "IosInteriorViewIncludes.h"
#include <string>

@class IosInteriorView;

@interface IosInteriorView : UIView <UITableViewDelegate, UITableViewDataSource>
{
    ExampleApp::Interiors::View::IosInteriorViewInterop* m_pInterop;
    
    float m_width;
    float m_height;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_inactiveFloorListXPosition;
    float m_inactiveDetailPaneYPosition;
    
    int m_floorCount;
    
    float m_onScreenParam;
    float m_stateChangeAnimationTimeSeconds;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale;

- (ExampleApp::Interiors::View::IosInteriorViewInterop*) getInterop;

- (BOOL)consumesTouch:(UITouch *)touch;

- (void) show;

- (void) hide;

- (void) setFloorName:(const std::string*)name;

- (void) setFloorCount:(int)floors;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateTo:(float)t;

@property(nonatomic, retain) UIView* pFloorPanel;
@property(nonatomic, retain) UIImageView* pFloorPanelTop;
@property(nonatomic, retain) UIImageView* pFloorPanelBottom;
@property(nonatomic, retain) UITableView* pFloorList;

@property(nonatomic, retain) UIView* pDetailsPanel;
@property(nonatomic, retain) UIButton* pDismissButton;
@property(nonatomic, retain) UILabel* pFloorNameLabel;

@end