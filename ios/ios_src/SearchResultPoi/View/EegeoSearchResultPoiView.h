// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <vector>
#include "Types.h"
#include "AppRunner.h"
#include "SearchResultModel.h"
#include "SearchResultPoiViewInterop.h"
#include "SearchResultPoiView.h"
#include "EegeoSearchResultModel.h"
#include "SearchResultPoiSpinner.h"

@class EegeoSearchResultPoiView;

@interface EegeoSearchResultPoiView : UIView<SearchResultPoiView, UIScrollViewDelegate, UIWebViewDelegate>
{
    UIViewController* m_pController;
    
    float m_stateChangeAnimationTimeSeconds;
    ExampleApp::Search::SdkModel::SearchResultModel m_model;
    ExampleApp::Search::EegeoPois::SdkModel::EegeoSearchResultModel m_eegeoModel;
    ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* m_pInterop;
    
    bool m_isPinned;
    float m_labelsSectionWidth;
    bool m_poiImageLoadedSuccessfully;
    bool m_htmlLoaded;
    bool m_webPageLoaded;
    bool m_webPageHeightSpecified;
    
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
@property (nonatomic, retain) UIView* pDropPinContainer;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pTitleCardContainer;
@property (nonatomic, retain) UIView* pDetailsCardContainer;
@property (nonatomic, retain) UIView* pTagsCardContainer;
@property (nonatomic, retain) UIView* pPreviewImageContainer;
@property (nonatomic, retain) UIView* pDescriptionCardContainer;
@property (nonatomic, retain) UIScrollView* pLabelsContainer;
@property (nonatomic, retain) UIView* pTagIconContainer;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UILabel* pSubtitleLabel;
@property (nonatomic, retain) UILabel* pAddressContent;
@property (nonatomic, retain) UILabel* pPhoneContent;
@property (nonatomic, retain) UILabel* pTagsContent;
@property (nonatomic, retain) UILabel* pWebContent;
@property (nonatomic, retain) UILabel* pDescriptionContent;
@property (nonatomic, retain) UIImageView* pPreviewImage;
@property (nonatomic, retain) UIView* pFooterSpace;
@property (nonatomic, retain) SearchResultPoiSpinner* pPoiImageLoadingSpinner;

@property (nonatomic, retain) UIImageView* pAddressIconContainer;
@property (nonatomic, retain) UIImageView* pPhoneIconContainer;
@property (nonatomic, retain) UIImageView* pWebIconContainer;
@property (nonatomic, retain) UIImageView* pTagsIconContainer;
@property (nonatomic, retain) UIImageView* pDescriptionIconContainer;
@property (nonatomic, retain) UIImageView* pFacebookIconContainer;
@property (nonatomic, retain) UIImageView* pTwitterIconContainer;
@property (nonatomic, retain) UIImageView* pEmailIconContainer;
@property (nonatomic, retain) UIImageView* pFadeContainer;

@property (nonatomic, retain) UIView* pTitleCardHeaderLine;
@property (nonatomic, retain) UIView* pPreviewCardHeaderLine;
@property (nonatomic, retain) UIView* pDetailsCardHeaderLine;
@property (nonatomic, retain) UIView* pTagsCardHeaderLine;
@property (nonatomic, retain) UIView* pFooterLine;

@property (nonatomic, retain) UIWebView* pWebView;

@end
