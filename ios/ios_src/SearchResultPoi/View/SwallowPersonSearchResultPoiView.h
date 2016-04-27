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
    
    bool m_isPinned;
    float m_labelsSectionWidth;
    
    UIImage* m_pRemovePinButtonBackgroundImage;
    UIImage* m_pRemovePinHighlightButtonBackgroundImage;
    UIImage* m_pAddPinButtonBackgroundImage;
    UIImage* m_pAddPinHighlightButtonBackgroundImage;
}

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned;

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

@property (nonatomic, retain) UIView* pCloseButtonContainer;
@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIButton* pPinButton;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pHeadlineContainer;
@property (nonatomic, retain) UIView* pContentSeparator;
@property (nonatomic, retain) UIView* pContentContainer;
@property (nonatomic, retain) UIScrollView* pLabelsContainer;
@property (nonatomic, retain) UILabel* pJobTitleLabel;
@property (nonatomic, retain) UILabel* pWorkingGroupLabel;
@property (nonatomic, retain) UILabel* pOfficeLocationLabel;
@property (nonatomic, retain) UILabel* pDeskCodeLabel;
@property (nonatomic, retain) UIImageView* pProfileImageContainer;
@property (nonatomic, retain) UIImage* pPlaceholderImage;
@property (nonatomic, retain) UIActivityIndicatorView* pProfileImageActivityIndicator;
@property (nonatomic, retain) UILabel* pNameLabel;

@end
