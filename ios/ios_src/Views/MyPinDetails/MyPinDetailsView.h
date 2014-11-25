// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "MyPinModel.h"

@class MyPinDetailsView;
@class MyPinDetailsViewController;

@interface MyPinDetailsView : UIView <UIAlertViewDelegate>
{
	__weak MyPinDetailsViewController* m_pController;
	float m_stateChangeAnimationTimeSeconds;
    float m_labelsSectionWidth;
    float m_maxContentSize;
    float m_descriptionContentY;
    float m_maxImageWidth;
    float m_scrollContentWidth;
    float m_scrollContentBottomMargin;
    float m_headerLabelHeight;
    float m_headerTextPadding;
    float m_labelYSpacing;
    bool m_hasImage;
}

- (id) initWithController:(MyPinDetailsViewController *)controller;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::MyPins::MyPinModel*)pModel;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

@property (nonatomic, retain) UIView* pCloseButtonContainer;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIButton* pRemovePinButton;
@property (nonatomic, retain) UIView* pShadowContainer;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pHeadlineContainer;
@property (nonatomic, retain) UIImageView* pHeadlineShadow;
@property (nonatomic, retain) UIView* pContentContainer;
@property (nonatomic, retain) UIScrollView* pLabelsContainer;
@property (nonatomic, retain) UIImageView* pContentShadow;
@property (nonatomic, retain) UIView* pIconContainer;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UIView* pDescriptionHeaderContainer;
@property (nonatomic, retain) UILabel* pDescriptionHeaderLabel;
@property (nonatomic, retain) UILabel* pDescriptionContent;
@property (nonatomic, retain) UIView* pImageHeaderContainer;
@property (nonatomic, retain) UILabel* pImageHeaderLabel;
@property (nonatomic, retain) UIImageView* pImageContent;



@end
