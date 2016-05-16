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
#include "YelpSearchJsonParser.h"
#include "UIHelpers.h"

#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"

@interface YelpSearchResultPoiView()<UIGestureRecognizerDelegate>
{
}
@end

namespace
{
    const bool AllowPinning = false;
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
        
        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview: self.pCloseButtonContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
        [self.pCloseButton addTarget:self action:@selector(handleClosedButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];
        
	if(AllowPinning)
        {
          self.pPinButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
          [self.pPinButton setDefaultStates];
          [self.pPinButton addTarget:self action:@selector(handlePinButtonSelected) forControlEvents:UIControlEventTouchUpInside];
          [self.pCloseButtonContainer addSubview: self.pPinButton];
        }
        
        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pContentContainer];
        
        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentContainer addSubview: self.pLabelsContainer];
        
        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pHeadlineContainer];
        
        self.pCategoryIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoryIconContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pHeadlineContainer addSubview: self.pCategoryIconContainer];
        
        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextTitleColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pHeadlineContainer addSubview: self.pTitleLabel];
        
        self.pPreviewImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelsContainer addSubview: self.pPreviewImage];
        
        self.pPreviewImageSpinner = [[[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImageSpinner.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        self.pPreviewImageSpinner.center = CGPointZero;
        [self.pPreviewImage addSubview: self.pPreviewImageSpinner];
        
        self.pPlaceholderImage = [UIImage imageNamed: @"poi_placeholder.png"];
        
        self.pRatingImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelsContainer addSubview: self.pRatingImage];
        
        self.pReviewCountLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pReviewCountLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pReviewCountLabel.textAlignment = NSTextAlignmentLeft;
        self.pReviewCountLabel.font = [UIFont systemFontOfSize:12.0];
        self.pReviewCountLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelsContainer addSubview: self.pReviewCountLabel];
        
        self.pAddressHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pAddressHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview: self.pAddressHeaderContainer];
        
        self.pAddressHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextHeaderColor :ExampleApp::Helpers::ColorPalette::UiBorderColor];
        [self.pAddressHeaderContainer addSubview: self.pAddressHeaderLabel];
        
        self.pAddressContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pAddressContent];
        
        self.pPhoneHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPhoneHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        
        [self.pLabelsContainer addSubview: self.pPhoneHeaderContainer];
        
        self.pPhoneHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextHeaderColor :ExampleApp::Helpers::ColorPalette::UiBorderColor];
        [self.pPhoneHeaderContainer addSubview: self.pPhoneHeaderLabel];
        
        self.pPhoneContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextLinkColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        UITapGestureRecognizer* phoneTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnPhone:)];
        [self.pPhoneContent setUserInteractionEnabled:YES];
        [self.pPhoneContent addGestureRecognizer:phoneTappedGesture];
        
        [self.pLabelsContainer addSubview: self.pPhoneContent];
        
        self.pCategoriesHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoriesHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview: self.pCategoriesHeaderContainer];
        
        self.pCategoriesHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextHeaderColor :ExampleApp::Helpers::ColorPalette::UiBorderColor];
        [self.pCategoriesHeaderContainer addSubview: self.pCategoriesHeaderLabel];
        
        self.pCategoriesContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pCategoriesContent];
        
        self.pReviewsHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pReviewsHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview: self.pReviewsHeaderContainer];
        
        self.pReviewsHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextHeaderColor :ExampleApp::Helpers::ColorPalette::UiBorderColor];
        [self.pReviewsHeaderContainer addSubview: self.pReviewsHeaderLabel];
        
        self.pReviewsContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pReviewsContent];
        
        m_pGradientMask = [[CAGradientLayer layer] retain];
        m_pGradientMask.colors = @[(id)[UIColor clearColor].CGColor,
                                   (id)[UIColor colorWithRed:0.0f green:0.0f blue:0.0f alpha:0.5f].CGColor];
        m_pGradientMask.locations = @[@0.8, @1.0];
        [self.pPreviewImage.layer addSublayer:m_pGradientMask];
        
        [self setTouchExclusivity: self];
        
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
    
    if(AllowPinning)
    {
        [self.pPinButton removeFromSuperview];
        [self.pPinButton release];
    }
    
    [self.pCloseButtonContainer removeFromSuperview];
    [self.pCloseButtonContainer release];
    
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];
    
    [self.pHeadlineContainer removeFromSuperview];
    [self.pHeadlineContainer release];
    
    [self.pLabelsContainer removeFromSuperview];
    [self.pLabelsContainer release];
    
    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];
    
    [self.pCategoryIconContainer removeFromSuperview];
    [self.pCategoryIconContainer release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pAddressHeaderLabel removeFromSuperview];
    [self.pAddressHeaderLabel release];
    
    [self.pAddressHeaderContainer removeFromSuperview];
    [self.pAddressHeaderContainer release];
    
    [self.pAddressContent removeFromSuperview];
    [self.pAddressContent release];
    
    [self.pPhoneHeaderLabel removeFromSuperview];
    [self.pPhoneHeaderLabel release];
    
    [self.pPhoneHeaderContainer removeFromSuperview];
    [self.pPhoneHeaderContainer release];
    
    [self.pPhoneContent removeFromSuperview];
    [self.pPhoneContent release];
    
    [self.pCategoriesHeaderContainer removeFromSuperview];
    [self.pCategoriesHeaderContainer release];
    
    [self.pCategoriesHeaderLabel removeFromSuperview];
    [self.pCategoriesHeaderLabel release];
    
    [self.pCategoriesContent removeFromSuperview];
    [self.pCategoriesContent release];
    
    [self.pReviewsHeaderContainer removeFromSuperview];
    [self.pReviewsHeaderContainer release];
    
    [self.pReviewsHeaderLabel removeFromSuperview];
    [self.pReviewsHeaderLabel release];
    
    [self.pReviewsContent removeFromSuperview];
    [self.pReviewsContent release];
    
    [self.pPlaceholderImage release];
    
    [self.pPreviewImage removeFromSuperview];
    [self.pPreviewImage release];
    
    [self.pPreviewImageSpinner removeFromSuperview];
    [self.pPreviewImageSpinner release];
    
    [self.pRatingImage removeFromSuperview];
    [self.pRatingImage release];
    
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
    const float boundsOccupyMultiplierHeight = 0.9f;
    const float mainWindowWidth = std::min(boundsWidth, 348.f);
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplierHeight;
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
    const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + headlineHeight);
    
    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                               0.f,
                                               mainWindowWidth,
                                               headlineHeight);
    
    self.pContentContainer.frame = CGRectMake(0.f,
                                              headlineHeight,
                                              mainWindowWidth,
                                              contentSectionHeight);
    
    const float labelsSectionOffsetX = 0.f;
    m_labelsSectionWidth = mainWindowWidth - (2.f * labelsSectionOffsetX);
    
    self.pLabelsContainer.frame = CGRectMake(labelsSectionOffsetX,
                                             0.f,
                                             m_labelsSectionWidth,
                                             contentSectionHeight);
    
    
    self.pCloseButtonContainer.frame = CGRectMake(0.f,
                                                  closeButtonSectionOffsetY,
                                                  mainWindowWidth,
                                                  closeButtonSectionHeight);
    
    self.pCloseButton.frame = CGRectMake(mainWindowWidth - closeButtonSectionHeight,
                                         0.f,
                                         closeButtonSectionHeight,
                                         closeButtonSectionHeight);
    
    if(AllowPinning)
    {
        self.pPinButton.frame = CGRectMake(0.f,
                                           0.f,
                                           closeButtonSectionHeight,
                                           closeButtonSectionHeight);
    }
    
    self.pCategoryIconContainer.frame = CGRectMake(0.f, 0.f, headlineHeight, headlineHeight);
    const float titlePadding = 10.0f;
    self.pTitleLabel.frame = CGRectMake(headlineHeight + titlePadding,
                                        0.f,
                                        mainWindowWidth - (headlineHeight + titlePadding),
                                        headlineHeight);
    self.pTitleLabel.font = [UIFont systemFontOfSize:24.0f];
    
    self->m_pVendorBrandingImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"yelp_logo_100x50", true) retain];
    self.pVendorBrandingImageContainer = [[[UIImageView alloc] initWithImage:self->m_pVendorBrandingImage] autorelease];
    //[self.pCloseButtonContainer addSubview:self.pVendorBrandingImageContainer];
    
    CGRect frame = self.pVendorBrandingImageContainer.frame;
    frame.origin.x = (self.pCloseButtonContainer.frame.size.width * 0.5f) - (frame.size.width * 0.5f);
    frame.origin.y = (self.pCloseButtonContainer.frame.size.height * 0.5f) - (frame.size.height * 0.5f);
    self.pVendorBrandingImageContainer.frame = frame;
}

- (void) performDynamicContentLayout
{
    const float headerLabelHeight = 20.f;
    const float labelYSpacing = 8.f;
    const float headerTextPadding = 3.0f;
    
    float currentLabelY = 8.f;
    const bool hasImage = !m_yelpModel.GetImageUrl().empty();
    const bool hasReviewBar = !self.pReviewCountLabel.hidden;
    
    if(!m_yelpModel.GetImageUrl().empty())
    {
        currentLabelY = 0.f;
        const CGFloat imageX = (self.frame.size.width * 0.5f - m_imageWidth * 0.5f);
        self.pPreviewImage.frame = CGRectMake(imageX, currentLabelY, m_imageWidth, m_imageHeight);
        self.pPreviewImageSpinner.center = [self.pPreviewImage convertPoint:self.pPreviewImage.center fromView:self.pPreviewImage.superview];
        const CGFloat imageBottomPadding = 8.0;
        currentLabelY += (m_imageHeight + imageBottomPadding);
    }
    
    const float reviewCountWidth = 40.0f;
    const float reviewCountHeight = 17.0f;
    const float yelpButtonWidth = 115.0f;
    const float yelpButtonHeight = 25.0f;
    const float reviewSpacing = 4.0f;
    
    const float fullRatingsWidth = (m_ratingsImageWidth + reviewSpacing + reviewCountWidth);
    const CGFloat barButtonCentredX = (self.frame.size.width * 0.5f - yelpButtonWidth * 0.5f);
    const CGFloat reviewBarOffsetX = (self.frame.size.width * 0.5f - (yelpButtonWidth + fullRatingsWidth) * 0.5f);
    const CGFloat yelpButtonOffsetX = reviewBarOffsetX + fullRatingsWidth;
    
    const CGFloat rateBarOriginX = hasImage ? barButtonCentredX : reviewBarOffsetX;
    const CGFloat yelpButtonX = (hasImage || !hasReviewBar) ? barButtonCentredX : yelpButtonOffsetX;
    const CGFloat imageBottomPadding = 8.0;
    
    if(!m_yelpModel.GetRatingImageUrl().empty())
    {
        UIImage* image = ExampleApp::Helpers::ImageHelpers::LoadImage(m_yelpModel.GetRatingImageUrl());
        [self.pRatingImage setImage:image];

        m_ratingsImageWidth = image.size.width;
        m_ratingsImageHeight = image.size.height;

        const CGFloat imageX = hasImage ? (self.frame.size.width * 0.5f) - m_ratingsImageWidth*0.5f : roundf(rateBarOriginX);
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
        
        self.pReviewCountLabel.frame = CGRectMake(imageX + frame.size.width + reviewSpacing, imageY, reviewCountWidth, reviewCountHeight);
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
        
        UIImage* pButtonImage = ExampleApp::Helpers::ImageHelpers::LoadImage(@"reviewsFromYelpRED");
        self.pVendorWebLinkButton = [[[UIButton alloc] initWithFrame:CGRectMake(roundf(yelpButtonX),
                                                                                roundf(currentLabelY),
                                                                                pButtonImage.size.width,
                                                                                pButtonImage.size.height)] autorelease];
        self.pVendorWebLinkButton.frame = CGRectIntegral(self.pVendorWebLinkButton.frame);
        
        // Set kCAFilterNearest for point filtering on link button, as button has baked text so needs to be pixel perfect.
        self.pVendorWebLinkButton.imageView.layer.minificationFilter = kCAFilterNearest;
        self.pVendorWebLinkButton.imageView.layer.magnificationFilter = kCAFilterNearest;
        
        [self.pVendorWebLinkButton setImage:pButtonImage forState:UIControlStateNormal];
        [self.pVendorWebLinkButton addTarget:self action:@selector(handleLinkClicked) forControlEvents:UIControlEventTouchUpInside];
        [self.pLabelsContainer addSubview: self.pVendorWebLinkButton];
        
        currentLabelY += (yelpButtonHeight + imageBottomPadding);
    }
    
    
    if(!m_yelpModel.GetPhone().empty())
    {
        self.pPhoneHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);
        self.pPhoneHeaderContainer.hidden = false;
        
        self.pPhoneHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, m_labelsSectionWidth - headerTextPadding, headerLabelHeight);
        self.pPhoneHeaderLabel.text = @"Phone";
        self.pPhoneHeaderLabel.hidden = false;
        currentLabelY += labelYSpacing + self.pPhoneHeaderContainer.frame.size.height;
        
        self.pPhoneContent.frame = CGRectMake(headerTextPadding, currentLabelY, m_labelsSectionWidth - headerTextPadding, 32.f);
        self.pPhoneContent.text = [NSString stringWithUTF8String:m_yelpModel.GetPhone().c_str()];
        self.pPhoneContent.hidden = false;
        [self.pPhoneContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pPhoneContent.frame.size.height;
    }
    
    if(!m_model.GetSubtitle().empty())
    {
        self.pAddressHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);
        self.pAddressHeaderContainer.hidden = false;
        
        self.pAddressHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, m_labelsSectionWidth - headerTextPadding, headerLabelHeight);
        self.pAddressHeaderLabel.text = @"Address";
        self.pAddressHeaderLabel.hidden = false;
        currentLabelY += labelYSpacing + self.pAddressHeaderContainer.frame.size.height;
        
        self.pAddressContent.frame = CGRectMake(headerTextPadding, currentLabelY, m_labelsSectionWidth - headerTextPadding, 85.f);
        self.pAddressContent.text = @"";
        self.pAddressContent.numberOfLines = 0;
        self.pAddressContent.adjustsFontSizeToFitWidth = NO;
        self.pAddressContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string addressText = m_model.GetSubtitle();
        Eegeo::Helpers::SearchReplace(addressText,", ", "\n");
        self.pAddressContent.text = [NSString stringWithUTF8String:addressText.c_str()];
        self.pAddressContent.hidden = false;
        [self.pAddressContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pAddressContent.frame.size.height;
    }
    
    if(!m_model.GetHumanReadableCategories().empty())
    {
        self.pCategoriesHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);
        self.pCategoriesHeaderContainer.hidden = false;
        
        self.pCategoriesHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, m_labelsSectionWidth - headerTextPadding, headerLabelHeight);
        self.pCategoriesHeaderLabel.text = @"Categories";
        self.pCategoriesHeaderLabel.hidden = false;
        currentLabelY += labelYSpacing + self.pCategoriesHeaderContainer.frame.size.height;
        
        self.pCategoriesContent.frame = CGRectMake(headerTextPadding, currentLabelY, m_labelsSectionWidth - headerTextPadding, 85.f);
        self.pCategoriesContent.text = @"";
        self.pCategoriesContent.numberOfLines = 0;
        self.pCategoriesContent.adjustsFontSizeToFitWidth = NO;
        self.pCategoriesContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string categoriesText;
        const std::vector<std::string>& categoriesList(m_model.GetHumanReadableCategories());
        for(size_t i = 0; i < categoriesList.size()-1; ++i)
        {
            categoriesText += categoriesList[i] + "\n";
        }
        categoriesText += categoriesList.back();
        
        self.pCategoriesContent.text = [NSString stringWithUTF8String:categoriesText.c_str()];
        self.pCategoriesContent.hidden = false;
        [self.pCategoriesContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pCategoriesContent.frame.size.height;
    }
    
    if(!m_yelpModel.GetReviews().empty())
    {
        self.pReviewsHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);
        self.pReviewsHeaderContainer.hidden = false;
        
        self.pReviewsHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, m_labelsSectionWidth - headerTextPadding, headerLabelHeight);
        self.pReviewsHeaderLabel.text = @"Review Snippet";
        self.pReviewsHeaderLabel.hidden = false;
        currentLabelY += labelYSpacing + self.pReviewsHeaderContainer.frame.size.height;
        
        self.pReviewsContent.frame = CGRectMake(headerTextPadding, currentLabelY, m_labelsSectionWidth - headerTextPadding, 85.f);
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
        
        self.pReviewsContent.text = [NSString stringWithUTF8String:reviewsText.c_str()];
        self.pReviewsContent.hidden = false;
        [self.pReviewsContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pReviewsContent.frame.size.height;
    }
    
    [self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, currentLabelY)];
}

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    
    m_yelpModel = ExampleApp::Search::Yelp::SdkModel::TransformToYelpSearchResult(m_model);
    
    m_isPinned = isPinned;
    [self updatePinnedButtonState];
    
    if(!AllowPinning && m_isPinned)
    {
        [self togglePinState];
    }
    
    self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];
    
    [self.pCategoryIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
    std::string categoryIcon = ExampleApp::Helpers::IconResources::GetSmallIconForCategory(pModel->GetCategory());
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pCategoryIconContainer, categoryIcon, ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.pAddressHeaderContainer.hidden = true;
    self.pAddressContent.hidden = true;
    self.pPhoneHeaderContainer.hidden = true;
    self.pPhoneContent.hidden = true;
    self.pPreviewImage.hidden = true;
    self.pCategoriesHeaderContainer.hidden = true;
    self.pCategoriesContent.hidden = true;
    self.pReviewsHeaderContainer.hidden = true;
    self.pReviewsContent.hidden = true;
    self.pVendorWebLinkButton.hidden = true;
    self.pReviewCountLabel.hidden = true;
    
    const CGFloat previewImagePlaceholderSize = 64.f;
    m_imageWidth = m_imageHeight = previewImagePlaceholderSize;
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
        [self.pPreviewImage setImage:self.pPlaceholderImage];
        [self.pPreviewImageSpinner startAnimating];
    }
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
    if(url == m_yelpModel.GetImageUrl())
    {
        [self.pPreviewImageSpinner stopAnimating];
        
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
            self.pPreviewImage.hidden = false;
            
            
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
                NSString * phoneUrlString = [NSString stringWithFormat:@"tel://%@", self.pPhoneContent.text];
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
    if(AllowPinning)
    {
      if(m_isPinned)
      {
        [self.pPinButton setImage:self->m_pRemovePinButtonImage forState:UIControlStateNormal];
        [self.pPinButton setImage:self->m_pRemovePinButtonHighlightImage forState:UIControlStateHighlighted];
      }
      else
      {
        [self.pPinButton setImage:self->m_pAddPinButtonImage forState:UIControlStateNormal];
        [self.pPinButton setImage:self->m_pAddPinButtonHighlightImage forState:UIControlStateHighlighted];
      }
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

@end
