// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "SearchResultPoiView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "StringHelpers.h"
#include "YelpSearchResultPoiView.h"
#include "App.h"
#include "UIHelpers.h"
#include "YelpParsingHelpers.h"

#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"

@interface YelpSearchResultPoiView()<UIGestureRecognizerDelegate>
{
}
@end

namespace
{
    const float RatingImageWidth = 100.f;
    const float RatingImageHeight = 30.f;
    const int PhoneAlertViewTag = 1;
    const int DeletePinAlertViewTag = 2;
}

@implementation YelpSearchResultPoiView

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;
{
    self = [super init];
    
    if(self)
    {
        self->m_pRemovePinButtonImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_remove_pin_off") retain];
        self->m_pRemovePinButtonHighlightImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_remove_pin_on") retain];
        self->m_pAddPinButtonImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_add_pin_off") retain];
        self->m_pAddPinButtonHighlightImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_add_pin_on") retain];
        
        m_pController = [UIViewController alloc];
        [m_pController setView:self];
        
        m_pInterop = pInterop;
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pControlContainer];
        
        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        self.pLabelsContainer.delegate = self;
        [self.pControlContainer addSubview: self.pLabelsContainer];
        
        self.pPreviewImageContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImageContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pLabelsContainer addSubview: self.pPreviewImageContainer];
        
        self.pReviewsCardContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pReviewsCardContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pLabelsContainer addSubview: self.pReviewsCardContainer];
        
        self.pDetailsCardContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDetailsCardContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pLabelsContainer addSubview: self.pDetailsCardContainer];
        
        self.pTagsCardContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTagsCardContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pLabelsContainer addSubview: self.pTagsCardContainer];
        
        self.pDescriptionCardContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionCardContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pLabelsContainer addSubview: self.pDescriptionCardContainer];
        
        
        self.pTitleCardContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleCardContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pTitleCardContainer];
        
        self.pTagIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTagIconContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pTitleCardContainer addSubview: self.pTagIconContainer];
        
        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextTitleColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pTitleCardContainer addSubview: self.pTitleLabel];
        
        self.pTitleCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview:self.pTitleCardHeaderLine];
        
        self.pPreviewCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pPreviewImageContainer addSubview:self.pPreviewCardHeaderLine];
        
        self.pReviewsCardHeaderLine = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pReviewsCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pReviewsCardContainer addSubview:self.pReviewsCardHeaderLine];
        
        self.pDetailsCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDetailsCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pDetailsCardContainer addSubview:self.pDetailsCardHeaderLine];
        
        self.pTagsCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTagsCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pTagsCardContainer addSubview:self.pTagsCardHeaderLine];
        
        self.pFooterLine = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pFooterLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview:self.pFooterLine];
        
        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pTitleCardContainer addSubview: self.pCloseButtonContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButton.contentMode = UIViewContentModeScaleAspectFit;
        self.pCloseButton.clipsToBounds = YES;
        [self.pCloseButton setDefaultStatesWithImageNames:@"exit_blue_x_button" :@"exit_dark_blue_x_button"];
        [self.pCloseButton addTarget:self action:@selector(handleClosedButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];
        
        self.pDropPinContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDropPinContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview:self.pDropPinContainer];
        
        self.pPinButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pPinButton setTitle:@"Save Location" forState:UIControlStateNormal];
        [self.pPinButton setTitleColor:ExampleApp::Helpers::ColorPalette::UiBorderColor forState:UIControlStateHighlighted];
        [self.pPinButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
        [self.pPinButton addTarget:self action:@selector(handlePinButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pDropPinContainer addSubview: self.pPinButton];
        
        self.pPreviewImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImage.clipsToBounds = YES;
        [self.pLabelsContainer addSubview: self.pPreviewImage];
        
        self.pPoiImageLoadingSpinner = [[[SearchResultPoiSpinner alloc] init] autorelease];
        self.pPoiImageLoadingSpinner.center = CGPointMake(0.0f, 0.0f);
        [self.pPreviewImage addSubview: self.pPoiImageLoadingSpinner];
        
        self.pAddressContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pDetailsCardContainer addSubview: self.pAddressContent];
        
        self.pTagsContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pTagsCardContainer addSubview: self.pTagsContent];
        
        self.pPhoneContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextLinkColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        UITapGestureRecognizer* phoneTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnPhone:)];
        [self.pPhoneContent setUserInteractionEnabled:YES];
        [self.pPhoneContent addGestureRecognizer:phoneTappedGesture];
        [self.pDetailsCardContainer addSubview: self.pPhoneContent];
        
        self.pRatingImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelsContainer addSubview: self.pRatingImage];
        
        self.pReviewCountLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pReviewCountLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pReviewCountLabel.textAlignment = NSTextAlignmentLeft;
        self.pReviewCountLabel.font = [UIFont systemFontOfSize:12.0];
        self.pReviewCountLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelsContainer addSubview: self.pReviewCountLabel];
        
        self.pAddressIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pAddressIconContainer.image = [UIImage imageNamed:@"poi_address"];
        [self.pDetailsCardContainer addSubview: self.pAddressIconContainer];
        
        self.pPhoneIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPhoneIconContainer.image = [UIImage imageNamed:@"poi_phone_active"];
        [self.pDetailsCardContainer addSubview: self.pPhoneIconContainer];
        
        self.pTagsIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTagsIconContainer.image = [UIImage imageNamed:@"poi_tag"];
        [self.pTagsCardContainer addSubview: self.pTagsIconContainer];
        
        self.pFadeContainer = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"SearchResults_Fade"]] autorelease];
        self.pFadeContainer.hidden = NO;
        [self.pControlContainer addSubview: self.pFadeContainer];
        
        self.pAddressContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pDetailsCardContainer addSubview: self.pAddressContent];
        
        self.pTagsContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pTagsCardContainer addSubview: self.pTagsContent];
        
        self.pDescriptionIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionIconContainer.image =  [UIImage imageNamed:@"detail_icon_description"];
        [self.pDescriptionCardContainer addSubview: self.pDescriptionIconContainer];
        
        self.pReviewsContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pDescriptionCardContainer addSubview: self.pReviewsContent];
        
        self.pFooterSpace = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pFooterSpace.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pFooterSpace];
        
        m_pGradientMask = [[CAGradientLayer layer] retain];
        m_pGradientMask.colors = @[(id)[UIColor clearColor].CGColor,
                                   (id)[UIColor colorWithRed:0.0f green:0.0f blue:0.0f alpha:0.5f].CGColor];
        m_pGradientMask.locations = @[@0.8, @1.0];
        [self.pPreviewImage.layer addSublayer:m_pGradientMask];
        
        [self setTouchExclusivity: self];
        
        m_poiImageLoadedSuccessfully = true;
        
        self.alpha = 0.f;
    }
    
    return self;
}

- (void)dealloc
{
    [m_pGradientMask release];
    m_pGradientMask = nil;
    
    [self->m_pVendorBrandingImage release];
    self->m_pVendorBrandingImage = nil;
    
    [self.pVendorBrandingImageContainer removeFromSuperview];
    [self.pVendorBrandingImageContainer release];
    
    [self.pVendorWebLinkButton removeFromSuperview];
    [self.pVendorWebLinkButton release];
    
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];

    [self.pPinButton removeFromSuperview];
    [self.pPinButton release];
    
    [self.pDropPinContainer removeFromSuperview];
    [self.pDropPinContainer release];
    
    [self.pCloseButtonContainer removeFromSuperview];
    [self.pCloseButtonContainer release];
    
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];
    
    [self.pLabelsContainer removeFromSuperview];
    [self.pLabelsContainer release];
    
    [self.pTitleCardContainer removeFromSuperview];
    [self.pTitleCardContainer release];
    
    [self.pDetailsCardContainer removeFromSuperview];
    [self.pDetailsCardContainer release];
    
    [self.pTagsCardContainer removeFromSuperview];
    [self.pTagsCardContainer release];
    
    [self.pPreviewImageContainer removeFromSuperview];
    [self.pPreviewImageContainer release];
    
    [self.pDescriptionCardContainer removeFromSuperview];
    [self.pDescriptionCardContainer release];
    
    [self.pTagIconContainer removeFromSuperview];
    [self.pTagIconContainer release];
    
    [self.pDescriptionIconContainer removeFromSuperview];
    [self.pDescriptionIconContainer release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pAddressContent removeFromSuperview];
    [self.pAddressContent release];
    
    [self.pPhoneContent removeFromSuperview];
    [self.pPhoneContent release];
    
    [self.pTagsContent removeFromSuperview];
    [self.pTagsContent release];
    
    [self.pReviewsContent removeFromSuperview];
    [self.pReviewsContent release];
    
    [self.pReviewsCardContainer removeFromSuperview];
    [self.pReviewsCardContainer release];
    
    [self.pAddressIconContainer removeFromSuperview];
    [self.pAddressIconContainer release];
    
    [self.pPhoneIconContainer removeFromSuperview];
    [self.pPhoneIconContainer release];
    
    [self.pTagsIconContainer removeFromSuperview];
    [self.pTagsIconContainer release];
    
    [self.pTitleCardHeaderLine removeFromSuperview];
    [self.pTitleCardHeaderLine release];
    
    [self.pPreviewCardHeaderLine removeFromSuperview];
    [self.pPreviewCardHeaderLine release];
    
    [self.pDetailsCardHeaderLine removeFromSuperview];
    [self.pDetailsCardHeaderLine release];
    
    [self.pTagsCardHeaderLine removeFromSuperview];
    [self.pTagsCardHeaderLine release];
    
    [self.pFooterLine removeFromSuperview];
    [self.pFooterLine release];
    
    [self.pFooterSpace removeFromSuperview];
    [self.pFooterSpace release];
    
    [self.pFadeContainer removeFromSuperview];
    [self.pFadeContainer release];
    
    [self.pPreviewImage removeFromSuperview];
    [self.pPreviewImage release];
    
    [self.pRatingImage removeFromSuperview];
    [self.pRatingImage release];
    
    [self.pReviewCountLabel removeFromSuperview];
    [self.pReviewCountLabel release];
    
    [self.pPoiImageLoadingSpinner removeFromSuperview];
    [self.pPoiImageLoadingSpinner release];
    
    [self->m_pRemovePinButtonImage release];
    [self->m_pRemovePinButtonHighlightImage release];
    [self->m_pAddPinButtonImage release];
    [self->m_pAddPinButtonHighlightImage release];
    
    [m_pController release];
    [self removeFromSuperview];
    [super dealloc];
}

- (void) layoutSubviews
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const float boundsOccupyMultiplier = 0.9f;
    const float mainWindowWidth = std::min(boundsWidth * boundsOccupyMultiplier, 348.f);
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplier;
    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    self.pControlContainer.frame = CGRectMake(0.f,
                                              0.f,
                                              mainWindowWidth,
                                              mainWindowHeight);
    
    const float headlineHeight = 50.f;
    const float closeButtonSectionHeight = 64.f;
    const float pinButtonSectionOffsetY = mainWindowHeight - 46.f;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + headlineHeight);
    
    const float topMargin = 15.f;
    const float bottomMargin = 15.f;
    const float sideMargin = 15.f;
    const float cardMargin = 10.f;
    
    const float cardContainerWidth = mainWindowWidth - sideMargin * 2;
    
    const float titleCardImageSize = 36.f;
    const float titleCardContainerHeight = 46.f;
    
    const float detailsCardHeight = 170.f;
    const float headerLineThickness = 1.f;
    
    float currentCardYPos = 0.f;
    
    currentCardYPos += topMargin;
    
    self.pTitleCardContainer.frame = CGRectMake(sideMargin,
                                                currentCardYPos,
                                                cardContainerWidth,
                                                titleCardContainerHeight);
    
    currentCardYPos += titleCardContainerHeight + cardMargin;
    
    self.pLabelsContainer.frame = CGRectMake(sideMargin,
                                             currentCardYPos,
                                             cardContainerWidth,
                                             contentSectionHeight);
    
    currentCardYPos += detailsCardHeight + cardMargin;

    self.pCloseButtonContainer.frame = CGRectMake(cardContainerWidth - titleCardImageSize,
                                                  0,
                                                  titleCardImageSize,
                                                  titleCardImageSize);
    
    self.pCloseButton.frame = CGRectMake(0.f,
                                         0.f,
                                         titleCardImageSize,
                                         titleCardImageSize);
    
    self.pTitleCardHeaderLine.frame = CGRectMake(sideMargin,
                                                 titleCardContainerHeight + topMargin,
                                                 cardContainerWidth,
                                                 headerLineThickness);
    
    self.pFooterSpace.frame = CGRectMake(sideMargin,
                                         pinButtonSectionOffsetY - bottomMargin - 19.f,
                                         cardContainerWidth,
                                         19.f);
    
    self.pFooterLine.frame = CGRectMake(sideMargin,
                                        pinButtonSectionOffsetY - bottomMargin - 20.f,
                                        cardContainerWidth,
                                        headerLineThickness);
    
    self.pDropPinContainer.frame = CGRectMake(sideMargin,
                                              pinButtonSectionOffsetY - bottomMargin,
                                              cardContainerWidth,
                                              42.f);
    
    
    self.pPinButton.frame = CGRectMake(0.f,
                                       0.f,
                                       cardContainerWidth,
                                       42.f);
    
    self.pFadeContainer.frame = CGRectMake(sideMargin,
                                           pinButtonSectionOffsetY - 15.f - 60.f,
                                           cardContainerWidth,
                                           40.f);
    
    [self.pPinButton setImageEdgeInsets:UIEdgeInsetsMake(2.f, -20.f, 2.f, 0.f)];
    [self.pPinButton setTitleEdgeInsets:UIEdgeInsetsMake(2.f, -10.f, 2.f, 0.f)];
    
    self.pPinButton.titleLabel.font = [UIFont systemFontOfSize:21.0f];
    
    self.pTagIconContainer.frame = CGRectMake(0.f,
                                              0.f,
                                              titleCardImageSize,
                                              titleCardImageSize);
    const float titlePadding = 10.0f;
    self.pTitleLabel.frame = CGRectMake(titleCardImageSize + titlePadding,
                                        0.f,
                                        cardContainerWidth - titleCardImageSize * 2 - titlePadding * 2,
                                        titleCardImageSize);
    
    self.pTitleLabel.textAlignment = NSTextAlignmentLeft;
    self.pTitleLabel.font = [UIFont systemFontOfSize:22.0f];
    self.pTitleLabel.lineBreakMode = NSLineBreakByTruncatingTail;
    
    self->m_pVendorBrandingImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"yelp_logo_100x50", true) retain];
    self.pVendorBrandingImageContainer = [[[UIImageView alloc] initWithImage:self->m_pVendorBrandingImage] autorelease];
    
    CGRect frame = self.pVendorBrandingImageContainer.frame;
    frame.origin.x = (self.pCloseButtonContainer.frame.size.width * 0.5f) - (frame.size.width * 0.5f);
    frame.origin.y = (self.pCloseButtonContainer.frame.size.height * 0.5f) - (frame.size.height * 0.5f);
    self.pVendorBrandingImageContainer.frame = frame;
}

- (void) performDynamicContentLayout
{
    const float labelYSpacing = 8.f;
    const float headerTextPadding = 3.0f;
    
    const bool hasImage = !m_yelpModel.GetImageUrl().empty();
    const bool hasReviewBar = !self.pReviewCountLabel.hidden;
    
    float currentLabelY = 0.f;
    float detailsCardY = 0.f;
    
    
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const float boundsOccupyMultiplier = 0.9f;
    const float mainWindowWidth = std::min(boundsWidth * boundsOccupyMultiplier, 348.f);
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplier;
    const float detailsImageSize = 18.f;
    const float detailsImageToTextMargin = 6.f;
    const float headerMargin = 10.f;
    const float sideMargin = 15.f;
    const float cardContainerWidth = mainWindowWidth - sideMargin * 2;
    const float cardTextHorizontalSpace = cardContainerWidth - detailsImageSize * 2 - headerMargin * 2.f;
    
    const float headlineHeight = 50.f;
    const float pinButtonSectionHeight = 64.f;
    const float contentSectionHeight = mainWindowHeight - (pinButtonSectionHeight + headlineHeight);
    
    const float reviewCountWidth = 40.0f;
    const float reviewCountHeight = 17.0f;
    const float yelpButtonWidth = 138.0f;
    const float yelpButtonHeight = 25.0f;
    const float reviewSpacing = 4.0f;
    
    const float fullRatingsWidth = (m_ratingsImageWidth + reviewSpacing + reviewCountWidth);
    const CGFloat barButtonCentredX = (cardContainerWidth * 0.5f - yelpButtonWidth * 0.5f);
    CGFloat reviewBarOffsetX = (cardContainerWidth * 0.5f) - fullRatingsWidth;
    
    bool reviewBarIsOffScreen = reviewBarOffsetX < 0;
    if(reviewBarIsOffScreen)
    {
        reviewBarOffsetX = 0.f;
    }
    float yelpButtonOffsetX = fullRatingsWidth;
  
    bool yelpButtonIsOffScreen = (yelpButtonOffsetX + yelpButtonWidth) > cardContainerWidth;
    if(yelpButtonIsOffScreen)
    {
        yelpButtonOffsetX = yelpButtonOffsetX + (cardContainerWidth - (yelpButtonOffsetX + yelpButtonWidth));
    }
    
    const CGFloat rateBarOriginX = hasImage ? barButtonCentredX : reviewBarOffsetX;
    const CGFloat yelpButtonX = (hasImage || !hasReviewBar) ? barButtonCentredX : yelpButtonOffsetX;
    const CGFloat imageBottomPadding = 8.0;
    
    if(hasImage)
    {
        currentLabelY = 0.f;
        self.pPreviewImage.frame = CGRectMake(0,
                                              currentLabelY,
                                              cardContainerWidth,
                                              cardContainerWidth * 2.f/3.f);
        m_pGradientMask.frame = self.pPreviewImage.bounds;
        
        self.pPoiImageLoadingSpinner.center = CGPointMake(self.pPreviewImage.frame.size.width/2.f, self.pPreviewImage.frame.size.height/2.f);
        m_pGradientMask.frame = self.pPreviewImage.bounds;
        const CGFloat imageBottomPadding = 8.0;
        currentLabelY += (cardContainerWidth * 2.f/3.f + imageBottomPadding);
    }

    
    if(!m_yelpModel.GetRatingImageUrl().empty())
    {
        UIImage* image = ExampleApp::Helpers::ImageHelpers::LoadImage(m_yelpModel.GetRatingImageUrl());
        [self.pRatingImage setImage:image];
        
        m_ratingsImageWidth = image.size.width;
        m_ratingsImageHeight = image.size.height;
        
        const CGFloat imageX = hasImage ? (cardContainerWidth * 0.5f) - m_ratingsImageWidth*0.5f : roundf(rateBarOriginX);
        const CGFloat imageY = hasImage
        ? self.pPreviewImage.frame.origin.y + self.pPreviewImage.frame.size.height - yelpButtonHeight - reviewSpacing
        : currentLabelY + (yelpButtonHeight*0.5f) - (m_ratingsImageHeight*0.5f);
        self.pRatingImage.frame = CGRectMake(imageX, imageY, m_ratingsImageWidth, m_ratingsImageHeight);
        
        CGRect frame = self.pRatingImage.frame;
        const CGFloat initialFrameHeight = frame.size.height;
        frame.size = image.size;
        frame.origin.x = imageX;
        frame.origin.y = imageY;
        self.pRatingImage.frame = frame;
        self.pRatingImage.hidden = false;
        
        self.pReviewCountLabel.frame = CGRectMake(imageX + frame.size.width + reviewSpacing,
                                                  imageY,
                                                  reviewCountWidth,
                                                  reviewCountHeight);
        
        self.pReviewCountLabel.textColor = hasImage ? ExampleApp::Helpers::ColorPalette::UiTextHeaderColor : ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        
        const CGFloat imageContentHeightDifference = (image.size.height - initialFrameHeight);
        const CGFloat newContentHeight = self.pLabelsContainer.contentSize.height + imageContentHeightDifference;
        [self.pLabelsContainer setContentSize:CGSizeMake(self.pLabelsContainer.contentSize.width, newContentHeight)];
        
        self.pRatingImage.hidden = self.pReviewCountLabel.hidden;
        
    }
    
    if(!m_yelpModel.GetWebUrl().empty())
    {
        if(self.pVendorWebLinkButton != nil)
        {
            [self.pVendorWebLinkButton removeFromSuperview];
            self.pVendorWebLinkButton = nil;
        }
        
        UIImage* pButtonImage = ExampleApp::Helpers::ImageHelpers::LoadImage(@"yelp_review_btn_light");
        self.pVendorWebLinkButton = [[[UIButton alloc] initWithFrame:CGRectMake(0.f,
                                                                                0.f ,
                                                                                pButtonImage.size.width,
                                                                                pButtonImage.size.height)] autorelease];
        self.pVendorWebLinkButton.frame = CGRectIntegral(self.pVendorWebLinkButton.frame);
        
        // Set kCAFilterNearest for point filtering on link button, as button has baked text so needs to be pixel perfect.
        self.pVendorWebLinkButton.imageView.layer.minificationFilter = kCAFilterNearest;
        self.pVendorWebLinkButton.imageView.layer.magnificationFilter = kCAFilterNearest;
        
        [self.pVendorWebLinkButton setImage:pButtonImage forState:UIControlStateNormal];
        [self.pVendorWebLinkButton addTarget:self action:@selector(handleLinkClicked) forControlEvents:UIControlEventTouchUpInside];
        [self.pReviewsCardContainer addSubview: self.pVendorWebLinkButton];
        self.pReviewsCardContainer.frame = CGRectMake(roundf(yelpButtonX),
                                                      roundf(currentLabelY),
                                                      pButtonImage.size.width,
                                                      pButtonImage.size.height);
        
        currentLabelY += (yelpButtonHeight + imageBottomPadding + headerMargin);
        
        self.pReviewsCardHeaderLine.frame = CGRectMake(0.f,
                                                       currentLabelY,
                                                       cardContainerWidth,
                                                       1.f);
        
        self.pPreviewCardHeaderLine.frame = CGRectMake(0.f,
                                                       currentLabelY,
                                                       cardContainerWidth,
                                                       1.f);
        
        currentLabelY += headerMargin;
        
        self.pDetailsCardContainer.frame = CGRectMake(0.f, currentLabelY, cardContainerWidth, 500.f);
    }
    
    if(!m_model.GetSubtitle().empty())
    {
        self.pAddressContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                                detailsCardY,
                                                cardTextHorizontalSpace,
                                                35.f);
        self.pAddressContent.text = @"";
        self.pAddressContent.numberOfLines = 0;
        self.pAddressContent.adjustsFontSizeToFitWidth = NO;
        self.pAddressContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string addressText = m_model.GetSubtitle();
        Eegeo::Helpers::SearchReplace(addressText,", ", "\n");
        self.pAddressContent.text = [NSString stringWithUTF8String:addressText.c_str()];
        self.pAddressContent.hidden = false;
        [self.pAddressContent sizeToFit];
        
        self.pAddressIconContainer.frame = CGRectMake(headerTextPadding, detailsCardY, detailsImageSize, detailsImageSize);
        
        detailsCardY += labelYSpacing + self.pAddressContent.frame.size.height;
        currentLabelY += labelYSpacing + self.pAddressContent.frame.size.height;
    }
    
    if(!m_yelpModel.GetPhone().empty())
    {
        self.pPhoneContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                              detailsCardY,
                                              cardTextHorizontalSpace,
                                              35.f);
        
        self.pPhoneContent.lineBreakMode = NSLineBreakByTruncatingTail;
        self.pPhoneContent.adjustsFontSizeToFitWidth = YES;
        self.pPhoneContent.numberOfLines = 0;
        self.pPhoneContent.text = [NSString stringWithUTF8String:m_yelpModel.GetPhone().c_str()];
        self.pPhoneContent.hidden = false;
        [self.pPhoneContent sizeToFit];
        
        self.pPhoneIconContainer.frame = CGRectMake(headerTextPadding,
                                                    detailsCardY,
                                                    detailsImageSize,
                                                    detailsImageSize);
        
        detailsCardY += labelYSpacing + self.pPhoneContent.frame.size.height;
        currentLabelY += labelYSpacing + self.pPhoneContent.frame.size.height;
    }
    
    self.pDetailsCardHeaderLine.frame = CGRectMake(0.f,
                                                   detailsCardY,
                                                   cardContainerWidth,
                                                   1.f);
    currentLabelY += headerMargin;
    
    if(!m_model.GetHumanReadableTags().empty())
    {
        self.pTagsContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                             currentLabelY,
                                             cardTextHorizontalSpace - headerMargin * 2,
                                             85.f);
        self.pTagsContent.text = @"";
        self.pTagsContent.numberOfLines = 0;
        self.pTagsContent.adjustsFontSizeToFitWidth = NO;
        self.pTagsContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string tagsText;
        const std::vector<std::string>& tagsList(m_model.GetHumanReadableTags());
        for(size_t i = 0; i < tagsList.size()-1; ++i)
        {
            tagsText += tagsList[i] + ", ";
        }
        tagsText += tagsList.back();
        
        self.pTagsContent.text = [NSString stringWithUTF8String:tagsText.c_str()];
        self.pTagsContent.hidden = false;
        [self.pTagsContent sizeToFit];
        
        self.pTagsIconContainer.frame = CGRectMake(headerTextPadding,
                                                   currentLabelY,
                                                   detailsImageSize,
                                                   detailsImageSize);
        
        currentLabelY += labelYSpacing + self.pTagsContent.frame.size.height;
        
        self.pTagsCardHeaderLine.frame = CGRectMake(0.f,
                                                    currentLabelY,
                                                    cardContainerWidth,
                                                    1.f);
        currentLabelY += headerMargin;
    }
    
    if(!m_yelpModel.GetReviews().empty())
    {
        self.pReviewsContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                                currentLabelY,
                                                cardTextHorizontalSpace,
                                                85.f);
        self.pReviewsContent.text = @"";
        self.pReviewsContent.numberOfLines = 0;
        self.pReviewsContent.adjustsFontSizeToFitWidth = NO;
        self.pReviewsContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string reviewsText;
        const std::vector<std::string>& reviewsList(m_yelpModel.GetReviews());
        for(std::vector<std::string>::const_iterator it = reviewsList.begin(); it != reviewsList.end(); ++it)
        {
            reviewsText += (*it) + "\n";
        }
        
        self.pDescriptionIconContainer.frame = CGRectMake(headerTextPadding,
                                                          currentLabelY,
                                                          detailsImageSize,
                                                          detailsImageSize);
        
        self.pReviewsContent.text = [NSString stringWithUTF8String:reviewsText.c_str()];
        self.pReviewsContent.hidden = false;
        [self.pReviewsContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pReviewsContent.frame.size.height + 20.f;
    }
    
    [self.pLabelsContainer setContentSize:CGSizeMake(cardContainerWidth, currentLabelY + 15.f)];
    
    if (self.pLabelsContainer.contentSize.height < contentSectionHeight)
    {
        self.pFadeContainer.hidden = YES;
    }
}

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    
    m_yelpModel = ExampleApp::Search::Yelp::SdkModel::Helpers::TransformToYelpSearchResult(m_model);
    
    m_isPinned = isPinned;
    [self updatePinnedButtonState];
    
    self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];
    
    [self.pTagIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
    std::string tagIconKey = ExampleApp::Helpers::IconResources::GetSmallIconForTag(pModel->GetIconKey());
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pTagIconContainer, tagIconKey, ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.pAddressContent.hidden = true;
    self.pPhoneContent.hidden = true;
    self.pTagsContent.hidden = true;
    self.pReviewsContent.hidden = true;
    self.pVendorWebLinkButton.hidden = true;
    self.pReviewCountLabel.hidden = true;
    
    m_ratingsImageWidth = RatingImageWidth;
    m_ratingsImageHeight = RatingImageHeight;
    
    if(m_yelpModel.GetReviewCount() > 0)
    {
        self.pReviewCountLabel.hidden = false;
        self.pReviewCountLabel.text = [NSString stringWithFormat:@"(%d)", m_yelpModel.GetReviewCount()];
    }
    
    
    
    [self performDynamicContentLayout];
    
    if(!m_yelpModel.GetImageUrl().empty())
    {
        [self.pPoiImageLoadingSpinner startAnimating];
    }
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
    if(url == m_yelpModel.GetImageUrl())
    {
        [self.pPoiImageLoadingSpinner stopAnimating];
        
        if(success)
        {
            NSData* imageData = [NSData dataWithBytes:&bytes->at(0) length:bytes->size()];
            UIImage *image = [UIImage imageWithData:imageData];
            [self.pPreviewImage setImage:image];
            
            CGRect frame = self.pPreviewImage.frame;
            const CGFloat initialFrameHeight = frame.size.height;
            frame.size = image.size;
            frame.origin.x = self.frame.size.width * 0.5f - frame.size.width * 0.5f;
            self.pPreviewImage.frame = frame;
            self.pPreviewImage.contentMode = UIViewContentModeScaleAspectFill;
            
            m_pGradientMask.frame = self.pPreviewImage.bounds;
            [m_pGradientMask removeAllAnimations];
            [self.pPreviewImage.layer removeAllAnimations];
            
            const CGFloat imageContentHeightDifference = (image.size.height - initialFrameHeight);
            const CGFloat newContentHeight = self.pLabelsContainer.contentSize.height + imageContentHeightDifference;
            [self.pLabelsContainer setContentSize:CGSizeMake(self.pLabelsContainer.contentSize.width, newContentHeight)];
            
            m_imageWidth = image.size.width;
            m_imageHeight = image.size.height;
            [self performDynamicContentLayout];
        }
        else
        {
            m_imageWidth = 0.f;
            m_imageHeight = 0.f;
            
            m_pGradientMask.frame = CGRectMake(0, 0, 0, 0);
            
            [self performDynamicContentLayout];
        }
    }
}

- (void) setFullyActive
{
    [m_pController setView:self];
    if(self.alpha == 1.f)
    {
        return;
    }
    
    [self animateToAlpha:1.f];
}

- (void) setFullyInactive
{
    [m_pController setView:nil];
    if(self.alpha == 0.f)
    {
        return;
    }
    
    [self animateToAlpha:0.f];
}

- (void) setActiveStateToIntermediateValue:(float)openState
{
    self.alpha = openState;
}

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)getInterop
{
    return m_pInterop;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    return self.alpha > 0.f;
}

- (void) animateToAlpha:(float)alpha
{
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.alpha = alpha;
     }];
}

- (UILabel*) createLabel:(UIColor*)textColor :(UIColor*)backgroundColor
{
    UILabel* pLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    pLabel.textColor = textColor;
    pLabel.backgroundColor = backgroundColor;
    pLabel.textAlignment = NSTextAlignmentLeft;
    return pLabel;
}

- (void) userTappedOnLink:(UITapGestureRecognizer *)recognizer
{
    [self handleLinkClicked];
}

- (void) handleLinkClicked
{
    NSString* preFormattedUrlString = [NSString stringWithUTF8String:m_yelpModel.GetWebUrl().c_str()];
    
    NSString* webUrlString = ([preFormattedUrlString rangeOfString:@"http"].location != NSNotFound)
    ? preFormattedUrlString
    : [NSString stringWithFormat:@"http://%@", preFormattedUrlString];
    
    NSURL *url = [NSURL URLWithString:webUrlString];
    if (![[UIApplication sharedApplication] openURL:url])
    {
        NSLog(@"%@%@",@"Failed to open url:",[url description]);
    }
}

-(void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    switch (alertView.tag)
    {
        case PhoneAlertViewTag:
            if (buttonIndex == 1)
            { 
                NSString * phoneUrlString = [NSString stringWithFormat:@"tel:%@", [self.pPhoneContent.text stringByAddingPercentEscapesUsingEncoding: NSUTF8StringEncoding]];
                NSURL *url = [NSURL URLWithString:phoneUrlString];
                if (![[UIApplication sharedApplication] openURL:url])
                {
                    NSLog(@"%@%@",@"Failed to open phone link:",[url description]);
                }
            }
            break;
        case DeletePinAlertViewTag:
        {
            alertView.delegate = nil;
            
            if (buttonIndex == 1)
            {
                [self togglePinState];
            }
        }break;
        default:
            break;
    }
}

- (void) userTappedOnPhone:(UITapGestureRecognizer *)recognizer
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:[NSString stringWithFormat:@"Call %@?", self.pPhoneContent.text] delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Call", nil];
    [alert show];
    alert.tag = PhoneAlertViewTag;
    [alert release];
}

- (void) handleClosedButtonSelected
{
    m_pInterop->HandleCloseClicked();
}

- (void) handlePinButtonSelected
{
    if(m_isPinned)
    {
        [self performPinRemoveWarningCeremony];
    }
    else
    {
        [self togglePinState];
    }
}

- (void) togglePinState
{
    m_isPinned = !m_isPinned;
    m_pInterop->HandlePinToggleClicked(m_model);
    [self updatePinnedButtonState];
}

- (void) updatePinnedButtonState
{
    if(m_isPinned)
    {
        [self.pPinButton setImage:self->m_pRemovePinButtonImage forState:UIControlStateNormal];
        [self.pPinButton setImage:self->m_pRemovePinButtonHighlightImage forState:UIControlStateHighlighted];
        [self.pPinButton setTitle:@"Remove Pin" forState:UIControlStateNormal];
    }
    else
    {
        [self.pPinButton setImage:self->m_pAddPinButtonImage forState:UIControlStateNormal];
        [self.pPinButton setImage:self->m_pAddPinButtonHighlightImage forState:UIControlStateHighlighted];
        [self.pPinButton setTitle:@"Drop Pin" forState:UIControlStateNormal];
    }
}

- (void) performPinRemoveWarningCeremony
{
    NSString* alertTitle = @"Remove Pin";
    NSString* alertMessage = @"Are you sure you want to remove this pin?";
    NSString* keepButtonText = @"No, keep it";
    NSString* deleteButtonText = @"Yes, delete it";
    
    if([UIAlertController class])
    {
        UIAlertController* alert = [UIAlertController alertControllerWithTitle:alertTitle
                                                                       message:alertMessage
                                                                preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:keepButtonText
                                                                style:UIAlertActionStyleDefault
                                                              handler:^(UIAlertAction * action) {}];
        
        UIAlertAction* removePinAction = [UIAlertAction actionWithTitle:deleteButtonText
                                                                  style:UIAlertActionStyleDefault
                                                                handler: ^(UIAlertAction * action)
                                          {
                                              [self togglePinState];
                                          }];
        
        [alert addAction:defaultAction];
        [alert addAction:removePinAction];
        [m_pController presentViewController:alert animated:YES completion:nil];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:self
                                              cancelButtonTitle:keepButtonText
                                              otherButtonTitles:deleteButtonText, nil];
        
        [alert show];
        alert.tag = DeletePinAlertViewTag;
        [alert release];
    }
}

-(void)scrollViewDidScroll: (UIScrollView*)scrollView
{
    if(self.pLabelsContainer.contentOffset.y + self.pLabelsContainer.frame.size.height >= self.pLabelsContainer.contentSize.height)
    {
        self.pFadeContainer.hidden = YES;
    }
    else
    {
        self.pFadeContainer.hidden = NO;
    }
}

@end
