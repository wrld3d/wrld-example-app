// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "VectorMath.h"
#include "CustomTableView.h"
#include "MenuViewIncludes.h"
#include "ViewPositionAnimator.h"

@class MenuView;

@interface MenuView : UIView
{
    ExampleApp::Menu::View::MenuViewInterop* m_pInterop;
    CustomTableDataProvider* m_pDataProvider;
    UIColor* m_pColour;
    
    ExampleApp::Helpers::UIAnimation::ViewPositionAnimator* m_offscreenAnimator;
    ExampleApp::Helpers::UIAnimation::ViewPositionAnimator* m_closedAnimator;
    ExampleApp::Helpers::UIAnimation::ViewPositionAnimator* m_openAnimator;
    
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;

    float m_stateChangeAnimationTimeSeconds;
    float m_offscreenX, m_offscreenY;
    float m_closedX, m_closedY;
    float m_openX, m_openY;

    float m_mainContainerVisibleOnScreenWhenClosedX;
    float m_mainContainerVisibleOnScreenWhenClosedY;
    float m_mainContainerOffscreenOffsetX;
    float m_mainContainerOffscreenOffsetY;
    float m_mainContainerX;
    float m_mainContainerY;
    float m_mainContainerOnScreenWidth;
    float m_mainContainerOnScreenHeight;
    float m_mainContainerWidth;
    float m_mainContainerHeight;

    float m_dragTabX;
    float m_dragTabY;
    float m_dragTabWidth;
    float m_dragTabOffset;
    float m_dragTabHeight;

    float m_searchBoxOffsetIntoContainer;
    float m_searchBoxX;
    float m_searchBoxY;
    float m_searchBoxWidth;
    float m_searchBoxHeight;

    float m_tableOffsetIntoContainerX;
    float m_tableOffsetIntoContainerY;
    float m_tableX;
    float m_tableY;
    float m_tableWidth;
    float m_tableHeight;

    CGPoint m_dragStartPos;
    CGPoint m_controlStartPos;

    bool m_animating;
    Eegeo::v2 m_animationStartPos;
    Eegeo::v2 m_animationCurrentPos;
    Eegeo::v2 m_animationEndPos;
    bool m_isFirstAnimationCeremony;
}

- (id) initWithParams:(float)width
    :(float)height
    :(float)pixelScale
    :(size_t)numberOfSections
    :(size_t)numberOfCells
    :(CustomTableDataProvider*)dataProvider;

- (ExampleApp::Menu::View::MenuViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) animateToRemovedFromScreen:(float)normalizedOffset;

- (void) animateToClosedOnScreen:(float)normalizedOffset;

- (void) animateToOpenOnScreen:(float)normalizedOffset;

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState;

- (void) setOpenStateToIntermediateValue:(float)openState;

- (void) beginDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity;

- (void) updateDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity;

- (void) completeDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity;

- (void) updateAnimation:(float)deltaSeconds;

- (BOOL) isAnimating;

- (float) onScreenOpenState;

- (void) setOffscreenPartsHiddenState:(bool)hidden;

- (void) initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells;

- (void) dragTabGesture:(UIPanGestureRecognizer *)recognizer;

- (void) tapTabGesture:(UITapGestureRecognizer *)recognizer;

- (void) refreshTableHeights;

- (void) setCanInteract:(BOOL)canInteract;

- (BOOL) canInteract;

@property (nonatomic, retain) UIView* pMenuContainer;
@property (nonatomic, retain) UIView* pDragTab;
@property (nonatomic, retain) UIView* pMenuHeaderStub;
@property (nonatomic, retain) CustomTableView* pTableview;
@property (nonatomic, retain) UIScrollView* pTableviewContainer;

@end
