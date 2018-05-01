// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "MyPinModel.h"
#include "MyPinDetailsViewIncludes.h"

@class MyPinDetailsView;

@interface MyPinDetailsView : UIView <UIAlertViewDelegate>
{
    ExampleApp::MyPinDetails::View::MyPinDetailsViewInterop* m_pInterop;
    UIViewController* m_pController;

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

- (id)initWithParams:(float)screenWidth :(float)screenHeight;

- (ExampleApp::MyPinDetails::View::MyPinDetailsViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const std::string&)title :(const std::string&)description :(const std::string&)imagePath;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

@property (nonatomic, retain) UIImageView* pPinIconImageView;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIView* pHeaderView;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UIView* pHeaderSeparator;

@property (nonatomic, retain) UIView* pContentSeperator;
@property (nonatomic, retain) UIScrollView* pContentScrollView;
@property (nonatomic, retain) UIView* pContentView;
@property (nonatomic, retain) UILabel* pDescriptionTitleLabel;
@property (nonatomic, retain) UILabel* pDescriptionContentLabel;
@property (nonatomic, retain) UIImageView* pPoiImageView;

@property (nonatomic, retain) UIView* pFooterSeperator;
@property (nonatomic, retain) UIView* pFooterContainer;
@property (nonatomic, retain) UIButton* pDeleteButton;

@end
