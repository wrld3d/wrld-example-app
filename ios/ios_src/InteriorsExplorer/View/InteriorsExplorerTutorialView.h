// Copyright eeGeo Ltd (2016), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InteriorsExplorerViewIncludes.h"

@class InteriorsExplorerTutorialView;

@interface InteriorsExplorerTutorialView : UIView <UIGestureRecognizerDelegate>
{
    float m_screenWidth;
    float m_screenHeight;
    float m_pixelScale;
    
    UITapGestureRecognizer* m_tapGestureRecogniser;
    
    float m_animationTimeSeconds;
    
    bool m_showChangeFloorDialog;
    
    float m_arrowLength;
    float m_arrowWidth;
    
    int m_iconPaddingTop;
    int m_iconPaddingLeft;
    int m_iconSize;
}

- (id) initWithParams: (float) width : (float) height : (float) pixelScale;

- (BOOL) consumesTouch;

- (void) repositionTutorialDialogs: (float) newPositionX
                                  : (float) dismissButtonPositionY
                                  : (float) dismissButtonHeight
                                  : (float) floorChangeButtonPositionY
                                  : (float) floorChangeButtonHeight
                                  : (bool) showFloorChangeDialog;

- (void) animateTo: (float) t;

- (void) show: (bool) showExitDialog : (bool) showChangeFloorDialog;

- (void) hide;

@property (nonatomic, retain) UIView* pExitDialogContainer;
@property (nonatomic, retain) UIView* pExitDialogOutlineArrow;
@property (nonatomic, retain) UIView* pExitDialogLabel;
@property (nonatomic, retain) UIView* pExitDialogArrow;
@property (nonatomic, retain) UIView* pExitDialogIcon;
@property (nonatomic, retain) UILabel* pExitDialogTitle;
@property (nonatomic, retain) UITextView* pExitDialogDescription;

@property (nonatomic, retain) UIView* pChangeFloorDialogContainer;
@property (nonatomic, retain) UIView* pChangeFloorDialogOutlineArrow;
@property (nonatomic, retain) UIView* pChangeFloorDialogLabel;
@property (nonatomic, retain) UIView* pChangeFloorDialogArrow;
@property (nonatomic, retain) UIView* pChangeFloorDialogIcon;
@property (nonatomic, retain) UILabel* pChangeFloorDialogTitle;
@property (nonatomic, retain) UITextView* pChangeFloorDialogDescription;

@end