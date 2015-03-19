// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Options.h"

@interface OptionsCacheClearSubView : UIView <UIGestureRecognizerDelegate>
{
    SEL m_confirmedHandler;
    UIView* m_pConfirmedHandlerInstance;
    bool m_displayed;
    double m_cacheClearDialogMinimumEndTimeSeconds;
}

- (id) init;

- (bool) isDisplayed;

- (void) displayWarning:(UIView*)pConfirmedHandlerInstance :(SEL)confirmedHandler;

- (void) conclude;

@property (nonatomic, retain) UIView* pDarkBackgroundPanel;
@property (nonatomic, retain) UIView* pOptionButtonsContainer;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIButton* pConfirmButton;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pHeadlineContainer;
@property (nonatomic, retain) UIView* pContentContainer;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UILabel* pMessageContent;
@property (nonatomic, retain) UIActivityIndicatorView* pSpinner;

@end
