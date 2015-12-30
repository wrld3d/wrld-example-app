// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "VectorMath.h"
#include "CustomTableView.h"
#include "MenuViewIncludes.h"
#include "ViewAnimationController.h"

@class MenuView;

@interface MenuView : UIView
{
    CustomTableDataProvider* m_pDataProvider;
    
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_onScreenAnimationController;
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_openAnimationController;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_dragTabOffsetX;
    float m_dragTabWidth;
    float m_dragTabHeight;
    float m_dragTabOffScreenX;
    float m_dragTabOffScreenY;
    float m_dragTabClosedOnScreenX;
    float m_dragTabClosedOnScreenY;
    float m_dragTabOpenOnScreenX;
    float m_dragTabOpenOnScreenY;
    
    float m_titleContainerOffScreenWidth;
    float m_titleContainerOffScreenHeight;
    float m_titleContainerOffScreenX;
    float m_titleContainerOffScreenY;
    float m_titleContainerClosedOnScreenWidth;
    float m_titleContainerClosedOnScreenHeight;
    float m_titleContainerClosedOnScreenX;
    float m_titleContainerClosedOnScreenY;
    float m_titleContainerOpenOnScreenWidth;
    float m_titleContainerOpenOnScreenHeight;
    float m_titleContainerOpenOnScreenX;
    float m_titleContainerOpenOnScreenY;
    
    float m_tableViewContainerOffsetY;
    float m_tableViewContainerWidth;
    float m_tableViewContainerHeight;
    float m_tableViewContainerOffScreenX;
    float m_tableViewContainerOffScreenY;
    float m_tableViewContainerClosedOnScreenX;
    float m_tableViewContainerClosedOnScreenY;
    float m_tableViewContainerOpenOnScreenX;
    float m_tableViewContainerOpenOnScreenY;

    float m_tableOffsetIntoContainerX;
    float m_tableOffsetIntoContainerY;
    float m_tableX;
    float m_tableY;
    float m_tableWidth;
    float m_tableHeight;
}

- (id) initWithParams:(float)width
    :(float)height
    :(float)pixelScale
    :(CustomTableDataProvider*)dataProvider;

- (ExampleApp::Menu::View::MenuViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) initializeAnimators;

- (void) animateToRemovedFromScreen;

- (void) animateToClosedOnScreen;

- (void) animateToOpenOnScreen;

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState;

- (void) updateAnimation:(float)deltaSeconds;

- (BOOL) isAnimating;

- (float) openOnScreenState;

- (void) setOffscreenPartsHiddenState:(bool)hidden;

- (void) initializeViews;

- (void) refreshTableHeights;

- (void) setTableCanInteract:(BOOL)canInteract;

- (BOOL) canInteract;

@property (nonatomic, retain) UIView* pDragTab;
@property (nonatomic, retain) UIView* pTitleContainer;
@property (nonatomic, retain) CustomTableView* pTableView;
@property (nonatomic, retain) UIScrollView* pTableViewContainer;

@end
