// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <vector>
#include "Types.h"
#include "AppRunner.h"
#include "SearchResultModel.h"
#include "SwallowMeetingRoomResultModel.h"
#include "SearchResultPoiViewInterop.h"
#include "SearchResultPoiView.h"

@class SwallowMeetingRoomSearchResultPoiView;

@interface SwallowMeetingRoomSearchResultPoiView : UIView<SearchResultPoiView>
{
    UIViewController* m_pController;
    
    float m_stateChangeAnimationTimeSeconds;
    ExampleApp::Search::SdkModel::SearchResultModel m_model;
    ExampleApp::Search::Swallow::SdkModel::SwallowMeetingRoomResultModel m_meetingRoomModel;
    ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* m_pInterop;
    
    bool m_isPinned;
    float m_labelsSectionWidth;
    
    UIImage* m_pRemovePinButtonBackgroundImage;
    UIImage* m_pRemovePinHighlightButtonBackgroundImage;
    UIImage* m_pAddPinButtonBackgroundImage;
    UIImage* m_pAddPinHighlightButtonBackgroundImage;
    
    float m_imageWidth;
    float m_imageHeight;
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
@property (nonatomic, retain) UIView* pContentContainer;
@property (nonatomic, retain) UIScrollView* pLabelsContainer;
@property (nonatomic, retain) UIView* pCategoryIconContainer;
@property (nonatomic, retain) UILabel* pTitleLabel;

@property (nonatomic, retain) UIView* pAvailableHeaderContainer;
@property (nonatomic, retain) UILabel* pAvailableHeaderLabel;
@property (nonatomic, retain) UILabel* pAvailableContent;

@property (nonatomic, retain) UIView* pCategoriesHeaderContainer;
@property (nonatomic, retain) UILabel* pCategoriesHeaderLabel;
@property (nonatomic, retain) UILabel* pCategoriesContent;

@property (nonatomic, retain) UIImageView* pPreviewImage;
@property (nonatomic, retain) UIActivityIndicatorView* pPreviewImageSpinner;
@end
