// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "SearchResultModel.h"

@class SearchResultPoiView;
@class SearchResultPoiViewController;

@interface SearchResultPoiView : UIView
{
	__weak SearchResultPoiViewController* m_pController;
	float m_stateChangeAnimationTimeSeconds;
}

- (id) initWithController:(SearchResultPoiViewController *)controller;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::Search::SearchResultModel*)pModel;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

@property (nonatomic, retain) UIView* pCloseButtonContainer;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIView* pShadowContainer;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pHeadlineContainer;
@property (nonatomic, retain) UIView* pContentContainer;
@property (nonatomic, retain) UIScrollView* pLabelsContainer;
@property (nonatomic, retain) UIView* pCategoryIconContainer;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UIView* pAddressHeaderContainer;
@property (nonatomic, retain) UILabel* pAddressHeaderLabel;
@property (nonatomic, retain) UILabel* pAddressContent;
@property (nonatomic, retain) UIView* pPhoneHeaderContainer;
@property (nonatomic, retain) UILabel* pPhoneHeaderLabel;
@property (nonatomic, retain) UILabel* pPhoneContent;
@property (nonatomic, retain) UIView* pWebHeaderContainer;
@property (nonatomic, retain) UILabel* pWebHeaderLabel;
@property (nonatomic, retain) UILabel* pWebContent;

@end
