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

@class EegeoSearchResultPoiView;

@interface EegeoSearchResultPoiView : UIView<SearchResultPoiView>
{
    UIViewController* m_pController;
    
    float m_stateChangeAnimationTimeSeconds;
    ExampleApp::Search::SdkModel::SearchResultModel m_model;
    ExampleApp::Search::EegeoPois::SdkModel::EegeoSearchResultModel m_eegeoModel;
    ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* m_pInterop;
    
    bool m_isPinned;
    float m_labelsSectionWidth;
    
    UIImage* m_pRemovePinButtonBackgroundImage;
    UIImage* m_pRemovePinHighlightButtonBackgroundImage;
    UIImage* m_pAddPinButtonBackgroundImage;
    UIImage* m_pAddPinHighlightButtonBackgroundImage;
    
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


@property (nonatomic, retain) UIButton* pCloseButton;
@property (nonatomic, retain) UIView* pCloseButtonContainer;
@property (nonatomic, retain) UIButton* pPinButton;
@property (nonatomic, retain) UIView* pDropPinContainer;
@property (nonatomic, retain) UILabel* pDropPinLabel;
@property (nonatomic, retain) UIView* pControlContainer;
@property (nonatomic, retain) UIView* pTitleCardContainer;
@property (nonatomic, retain) UIView* pDetailsCardContainer;
@property (nonatomic, retain) UIView* pTagsCardContainer;
@property (nonatomic, retain) UIView* pDescriptionCardContainer;
@property (nonatomic, retain) UIScrollView* pLabelsContainer;
@property (nonatomic, retain) UIView* pTagIconContainer;
@property (nonatomic, retain) UILabel* pTitleLabel;
@property (nonatomic, retain) UILabel* pAddressContent;
@property (nonatomic, retain) UILabel* pPhoneContent;
@property (nonatomic, retain) UILabel* pTagsContent;
@property (nonatomic, retain) UIImageView* pPreviewImage;
@property (nonatomic, retain) UIActivityIndicatorView* pPreviewImageSpinner;
@property (nonatomic, retain) UILabel* pWebContent;
@property (nonatomic, retain) UILabel* pDescriptionContent;

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
@property (nonatomic, retain) UIView* pDetailsCardHeaderLine;
@property (nonatomic, retain) UIView* pTagsCardHeaderLine;
@property (nonatomic, retain) UIView* pDescriptionCardHeaderLine;

@end
