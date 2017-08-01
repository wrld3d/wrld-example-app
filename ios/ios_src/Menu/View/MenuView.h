// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "VectorMath.h"
#include "CustomTableView.h"
#include "MenuViewIncludes.h"
#include "IMenuView.h"
#include "ViewAnimationController.h"

@class MenuView;

enum MenuState
{
    OFF_SCREEN,
    CLOSED_ON_SCREEN,
    OPEN_ON_SCREEN,
    ANIMATING
};

@interface MenuView : UIView
{
    CustomTableDataProvider* m_pDataProvider;
    
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_onScreenAnimationController;
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_openAnimationController;
    
    float m_stateChangeAnimationTimeSeconds;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    float m_tableSpacing;
    
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
    
    float m_menuContainerWidth;
    float m_menuContainerHeight;
    float m_menuContainerOffScreenX;
    float m_menuContainerOffScreenY;
    float m_menuContainerClosedOnScreenX;
    float m_menuContainerClosedOnScreenY;
    float m_menuContainerOpenOnScreenX;
    float m_menuContainerOpenOnScreenY;
    
    MenuState m_menuState;
}

- (id) initWithParams:(float)width
                     :(float)height
                     :(float)pixelScale
                     :(CustomTableDataProvider*)dataProvider
                     :(int)tableCount;

- (ExampleApp::Menu::View::MenuViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) initializeAnimators;

- (void) animateToRemovedFromScreen;

- (void) animateToClosedOnScreen;

- (void) animateToOpenOnScreen;

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState;

- (void) updateAnimation:(float)deltaSeconds;

- (void) updateTableAnimation:(float)deltaSeconds;

- (void) onTableAnimationUpdated;

- (BOOL) isAnimating;

- (BOOL) isTableAnimating;

- (float) openOnScreenState;

- (void) setOffscreenPartsHiddenState:(bool)hidden;

- (void) initializeViews;

- (void) refreshTableHeights;

- (float) getHeightForTable:(CustomTableView*)tableView;

- (void) setTableCanInteract:(BOOL)canInteract;

- (BOOL) canInteract;

- (void)updateMenuSections:(ExampleApp::Menu::View::TSections*)sections;

- (void) toggleSection:(int)sectionIndex;

@property (nonatomic, retain) UIButton* pDragTab;
@property (nonatomic, retain) UIView* pTitleContainer;
@property (nonatomic, retain) UIView* pMenuContainer;
@property (nonatomic, retain) UIView* pTopTableSeparator;
@property (nonatomic, retain) NSMutableDictionary* pTableViewMap;
@property (nonatomic, retain) UIScrollView* pTableViewContainer;

@end
