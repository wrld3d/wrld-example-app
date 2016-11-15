// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <vector>
#include "Types.h"
#include "AppRunner.h"
#include "SearchResultModel.h"
#include "SearchResultPoiViewInterop.h"
#include "SearchResultPoiView.h"
#include "YelpSearchResultModel.h"
#include "SearchResultPoiSpinner.h"

@class YelpSearchResultPoiView;

@interface YelpSearchResultPoiView : UIView<SearchResultPoiView, UIScrollViewDelegate>
{
    UIViewController* m_pController;
    
    float m_stateChangeAnimationTimeSeconds;
    ExampleApp::Search::SdkModel::SearchResultModel m_model;
    ExampleApp::Search::Yelp::SdkModel::YelpSearchResultModel m_yelpModel;
    ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* m_pInterop;
    
    bool m_isPinned;
    float m_labelsSectionWidth;
    
    UIImage* m_pRemovePinButtonImage;
    UIImage* m_pRemovePinButtonHighlightImage;
    UIImage* m_pAddPinButtonImage;
    UIImage* m_pAddPinButtonHighlightImage;
    UIImage* m_pVendorBrandingImage;
    
    CAGradientLayer* m_pGradientMask;
    
    float m_imageWidth;
    float m_imageHeight;
    float m_ratingsImageWidth;
    float m_ratingsImageHeight;
    bool m_poiImageLoadedSuccessfully;
}

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned;

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;


@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIView* pCloseButtonContainer;
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
@property (nonatomic, retain) UILabel* pAddressContent;
@property (nonatomic, retain) UILabel* pPhoneContent;
@property (nonatomic, retain) UILabel* pTagsContent;
@property (nonatomic, retain) UILabel* pReviewsContent;
@property (nonatomic, retain) UIView* pReviewsCardContainer;
@property (nonatomic, retain) UIImageView* pPreviewImage;
@property (nonatomic, retain) UIImageView* pRatingImage;
@property (nonatomic, retain) UILabel* pReviewCountLabel;
@property (nonatomic, retain) UIButton* pVendorWebLinkButton;
@property (nonatomic, retain) UIImageView* pVendorBrandingImageContainer;
@property (nonatomic, retain) UIView* pFooterSpace;
@property (nonatomic, retain) SearchResultPoiSpinner* pPoiImageLoadingSpinner;

@property (nonatomic, retain) UIImageView* pAddressIconContainer;
@property (nonatomic, retain) UIImageView* pPhoneIconContainer;
@property (nonatomic, retain) UIImageView* pTagsIconContainer;
@property (nonatomic, retain) UIImageView* pDescriptionIconContainer;
@property (nonatomic, retain) UIImageView* pFadeContainer;

@property (nonatomic, retain) UIView* pReviewsCardHeaderLine;
@property (nonatomic, retain) UIView* pTitleCardHeaderLine;
@property (nonatomic, retain) UIView* pPreviewCardHeaderLine;
@property (nonatomic, retain) UIView* pDetailsCardHeaderLine;
@property (nonatomic, retain) UIView* pTagsCardHeaderLine;
@property (nonatomic, retain) UIView* pFooterLine;

@end