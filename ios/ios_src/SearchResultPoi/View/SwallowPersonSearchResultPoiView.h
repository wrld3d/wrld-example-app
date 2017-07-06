// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <vector>
#include "Types.h"
#include "AppRunner.h"
#include "SearchResultModel.h"
#include "SearchResultPoiViewInterop.h"
#include "SearchResultPoiView.h"
#include "SwallowPersonResultModel.h"

@class SwallowPersonSearchResultPoiView;

@interface SwallowPersonSearchResultPoiView : UIView<SearchResultPoiView>
{
    float m_stateChangeAnimationTimeSeconds;
    ExampleApp::Search::SdkModel::SearchResultModel m_model;
    ExampleApp::Search::Swallow::SdkModel::SwallowPersonResultModel m_swallowPersonModel;
    ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* m_pInterop;
    
    float m_labelsSectionWidth;
    
    float m_imageWidth;
    float m_imageHeight;
}

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel;

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pHeadlineContainer;
@property (nonatomic, retain) UIView* pContentContainer;
@property (nonatomic, retain) UIScrollView* pLabelsContainer;
@property (nonatomic, retain) UIView* pCategoryIconContainer;
@property (nonatomic, retain) UILabel* pJobTitleLabel;
@property (nonatomic, retain) UILabel* pWorkingGroupLabel;
@property (nonatomic, retain) UILabel* pOfficeLocationLabel;
@property (nonatomic, retain) UILabel* pDeskCodeLabel;
@property (nonatomic, retain) UIImageView* pDescriptionIconContainer;
@property (nonatomic, retain) UIView* pDescriptionDivider;
@property (nonatomic, retain) UILabel* pCategoriesContent;
@property (nonatomic, retain) UIView* pCategoriesDivider;
@property (nonatomic, retain) UIImageView* pCategoriesIconContainer;
@property (nonatomic, retain) UIImageView* pProfileImageContainer;
@property (nonatomic, retain) UIImage* pPlaceholderImage;
@property (nonatomic, retain) UIActivityIndicatorView* pProfileImageActivityIndicator;
@property (nonatomic, retain) UIView* pImageDivider;
@property (nonatomic, retain) UILabel* pNameLabel;

@end
