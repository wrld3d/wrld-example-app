// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InteriorsExplorerViewIncludes.h"
#include <string>
#include <vector>

@class InteriorsExplorerView;

@interface InteriorsExplorerView : UIView <UITableViewDelegate, UITableViewDataSource>
{
    ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop* m_pInterop;
    
    float m_width;
    float m_height;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_inactiveFloorListXPosition;
    float m_inactiveDetailPaneYPosition;
    
    float m_onScreenParam;
    float m_stateChangeAnimationTimeSeconds;
    
    float m_detailsPanelHeight;
    
    BOOL m_touchEnabled;
    
    std::vector<std::string> m_tableViewFloorNames;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale;

- (ExampleApp::InteriorsExplorer::View::InteriorsExplorerViewInterop*) getInterop;

- (BOOL)consumesTouch:(UITouch *)touch;

- (void) show;

- (void) hide;

- (void) setFloorName:(const std::string*)name;

- (void) updateFloors: (const std::vector<std::string>&) floorNumbers withCurrentFloor: (int) currentlySelectedFloor;

- (void) setFullyOnScreen;

- (void) setFullyOffScreen;

- (void) setOnScreenStateToIntermediateValue:(float)openState;

- (void) animateTo:(float)t;

- (int) reverseIndex:(int)floorIndex;

- (void) setTouchEnabled:(BOOL)enabled;

@property(nonatomic, retain) UIView* pFloorPanel;
@property(nonatomic, retain) UIImageView* pFloorPanelTop;
@property(nonatomic, retain) UIImageView* pFloorPanelBottom;
@property(nonatomic, retain) UITableView* pFloorList;

@property(nonatomic, retain) UIView* pDetailsPanel;
@property(nonatomic, retain) UIImageView* pDetailsPanelBackground;
@property(nonatomic, retain) UIImageView* pDetailsPanelRight;

@property(nonatomic, retain) UIButton* pDismissButton;
@property(nonatomic, retain) UIImageView* pDismissButtonBackground;
@property(nonatomic, retain) UILabel* pFloorNameLabel;

@end