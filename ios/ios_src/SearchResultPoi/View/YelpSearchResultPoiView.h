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

@class YelpSearchResultPoiView;

@interface YelpSearchResultPoiView : UIView<SearchResultPoiView>
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
@property (nonatomic, retain) UIView* pAddressHeaderContainer;
@property (nonatomic, retain) UILabel* pAddressHeaderLabel;
@property (nonatomic, retain) UILabel* pAddressContent;
@property (nonatomic, retain) UIView* pPhoneHeaderContainer;
@property (nonatomic, retain) UILabel* pPhoneHeaderLabel;
@property (nonatomic, retain) UILabel* pPhoneContent;
@property (nonatomic, retain) UIView* pCategoriesHeaderContainer;
@property (nonatomic, retain) UILabel* pCategoriesHeaderLabel;
@property (nonatomic, retain) UILabel* pCategoriesContent;
@property (nonatomic, retain) UIView* pReviewsHeaderContainer;
@property (nonatomic, retain) UILabel* pReviewsHeaderLabel;
@property (nonatomic, retain) UILabel* pReviewsContent;
@property (nonatomic, retain) UIImageView* pPreviewImage;
@property (nonatomic, retain) UIImage* pPlaceholderImage;
@property (nonatomic, retain) UIActivityIndicatorView* pPreviewImageSpinner;
@property (nonatomic, retain) UIImageView* pRatingImage;
@property (nonatomic, retain) UILabel* pReviewCountLabel;
@property (nonatomic, retain) UIButton* pVendorWebLinkButton;
@property (nonatomic, retain) UIImageView* pVendorBrandingImageContainer;

@end
