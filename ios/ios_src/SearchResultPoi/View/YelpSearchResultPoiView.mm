// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "SearchResultPoiView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "StringHelpers.h"
#import "UIView+TouchExclusivity.h"
#include "YelpSearchResultPoiView.h"
#include "App.h"

@interface YelpSearchResultPoiView()<UIGestureRecognizerDelegate>
{
}
@end

const float RatingImageWidth = 100.f;
const float RatingImageHeight = 30.f;
const int PhoneAlertViewTag = 1;
const int DeletePinAlertViewTag = 2;

@implementation YelpSearchResultPoiView

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;
{
    self = [super init];
    
    if(self)
    {
        m_pController = [UIViewController alloc];
        [m_pController setView:self];
        
        self->m_pRemovePinButtonBackgroundImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_remove_pin_off") retain];
        self->m_pAddPinButtonBackgroundImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_add_pin_off") retain];
        
        m_pInterop = pInterop;
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;
        [self addSubview: self.pControlContainer];
        
        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pControlContainer addSubview: self.pCloseButtonContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_close_off") forState:UIControlStateNormal];
        [self.pCloseButton addTarget:self action:@selector(handleClosedButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];
        
        self.pPinButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pPinButton addTarget:self action:@selector(handlePinButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pPinButton];
        
        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pControlContainer addSubview: self.pContentContainer];
        
        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pContentContainer addSubview: self.pLabelsContainer];
        
        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pControlContainer addSubview: self.pHeadlineContainer];
        
        self.pCategoryIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoryIconContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pHeadlineContainer addSubview: self.pCategoryIconContainer];
        
        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pHeadlineContainer addSubview: self.pTitleLabel];
        
        self.pPreviewImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelsContainer addSubview: self.pPreviewImage];
        
        self.pPreviewImageSpinner = [[[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImageSpinner.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        self.pPreviewImageSpinner.center = CGPointZero;
        [self.pPreviewImage addSubview: self.pPreviewImageSpinner];
        
        self.pRatingImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelsContainer addSubview: self.pRatingImage];
        
        self.pAddressHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pAddressHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pLabelsContainer addSubview: self.pAddressHeaderContainer];
        
        self.pAddressHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
        [self.pAddressHeaderContainer addSubview: self.pAddressHeaderLabel];
        
        self.pAddressContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pAddressContent.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        [self.pLabelsContainer addSubview: self.pAddressContent];
        
        self.pPhoneHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPhoneHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        
        [self.pLabelsContainer addSubview: self.pPhoneHeaderContainer];
        
        self.pPhoneHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
        [self.pPhoneHeaderContainer addSubview: self.pPhoneHeaderLabel];
        
        self.pPhoneContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pPhoneContent.textColor = ExampleApp::Helpers::ColorPalette::LinkTone;
        UITapGestureRecognizer* phoneTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnPhone:)];
        [self.pPhoneContent setUserInteractionEnabled:YES];
        [self.pPhoneContent addGestureRecognizer:phoneTappedGesture];
        
        [self.pLabelsContainer addSubview: self.pPhoneContent];
        
        self.pWebHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pWebHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pLabelsContainer addSubview: self.pWebHeaderContainer];
        
        self.pWebHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
        [self.pWebHeaderContainer addSubview: self.pWebHeaderLabel];
        
        self.pCategoriesHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoriesHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pLabelsContainer addSubview: self.pCategoriesHeaderContainer];
        
        self.pCategoriesHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
        [self.pCategoriesHeaderContainer addSubview: self.pCategoriesHeaderLabel];
        
        self.pCategoriesContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pCategoriesContent.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        [self.pLabelsContainer addSubview: self.pCategoriesContent];
        
        self.pReviewsHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pReviewsHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pLabelsContainer addSubview: self.pReviewsHeaderContainer];
        
        self.pReviewsHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
        [self.pReviewsHeaderContainer addSubview: self.pReviewsHeaderLabel];
        
        self.pReviewsContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pReviewsContent.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        [self.pLabelsContainer addSubview: self.pReviewsContent];
        
        [self setTouchExclusivity: self];
        
        self.alpha = 0.f;
    }
    
    return self;
}

- (void)dealloc
{
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
    
    [self.pWebHeaderLabel removeFromSuperview];
    [self.pWebHeaderLabel release];
    
    [self.pWebHeaderContainer removeFromSuperview];
    [self.pWebHeaderContainer release];
    
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
    
    [self.pPreviewImage removeFromSuperview];
    [self.pPreviewImage release];
    
    [self.pPreviewImageSpinner removeFromSuperview];
    [self.pPreviewImageSpinner release];
    
    [self.pRatingImage removeFromSuperview];
    [self.pRatingImage release];
    
    [self->m_pRemovePinButtonBackgroundImage release];
    [self->m_pRemovePinHighlightButtonBackgroundImage release];
    [self->m_pAddPinButtonBackgroundImage release];
    [self->m_pAddPinHighlightButtonBackgroundImage release];
    
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
    
    self.pPinButton.frame = CGRectMake(0.f,
                                       0.f,
                                       closeButtonSectionHeight,
                                       closeButtonSectionHeight);
    
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
    
    if(!m_model.GetImageUrl().empty())
    {
        currentLabelY = 0.f;
        const CGFloat imageX = (self.frame.size.width * 0.5f - m_imageWidth * 0.5f);
        self.pPreviewImage.frame = CGRectMake(imageX, currentLabelY, m_imageWidth, m_imageHeight);
        self.pPreviewImageSpinner.center = [self.pPreviewImage convertPoint:self.pPreviewImage.center fromView:self.pPreviewImage.superview];
        const CGFloat imageBottomPadding = 8.0;
        currentLabelY += (m_imageHeight + imageBottomPadding);
    }
    
    if(!m_model.GetRatingImageUrl().empty())
    {
        const CGFloat imageX = (self.frame.size.width * 0.5f - m_ratingsImageWidth * 0.5f);
        self.pRatingImage.frame = CGRectMake(imageX, currentLabelY, m_ratingsImageWidth, m_ratingsImageHeight);
        const CGFloat imageBottomPadding = 8.0;
        currentLabelY += (m_ratingsImageHeight + imageBottomPadding);
        
        UIImage* image = ExampleApp::Helpers::ImageHelpers::LoadImage(m_model.GetRatingImageUrl());
        [self.pRatingImage setImage:image];
        
        CGRect frame = self.pRatingImage.frame;
        const CGFloat initialFrameHeight = frame.size.height;
        frame.size = image.size;
        frame.origin.x = self.frame.size.width * 0.5f - frame.size.width * 0.5f;
        self.pRatingImage.frame = frame;
        self.pRatingImage.hidden = false;
        
        const CGFloat imageContentHeightDifference = (image.size.height - initialFrameHeight);
        const CGFloat newContentHeight = self.pLabelsContainer.contentSize.height + imageContentHeightDifference;
        [self.pLabelsContainer setContentSize:CGSizeMake(self.pLabelsContainer.contentSize.width, newContentHeight)];
        
        m_ratingsImageWidth = image.size.width;
        m_ratingsImageHeight = image.size.height;
    }
    
    if(!m_model.GetPhone().empty())
    {
        self.pPhoneHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);
        self.pPhoneHeaderContainer.hidden = false;
        
        self.pPhoneHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, m_labelsSectionWidth - headerTextPadding, headerLabelHeight);
        self.pPhoneHeaderLabel.text = @"Phone";
        self.pPhoneHeaderLabel.hidden = false;
        currentLabelY += labelYSpacing + self.pPhoneHeaderContainer.frame.size.height;
        
        self.pPhoneContent.frame = CGRectMake(headerTextPadding, currentLabelY, m_labelsSectionWidth - headerTextPadding, 32.f);
        self.pPhoneContent.text = [NSString stringWithUTF8String:m_model.GetPhone().c_str()];
        self.pPhoneContent.hidden = false;
        [self.pPhoneContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pPhoneContent.frame.size.height;
    }
    
    if(!m_model.GetWebUrl().empty())
    {
        if(self.pVendorWebLinkButton != nil)
        {
            [self.pVendorWebLinkButton removeFromSuperview];
            self.pVendorWebLinkButton = nil;
        }
        
        self.pWebHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);
        
        self.pWebHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, m_labelsSectionWidth - headerTextPadding, headerLabelHeight);
        self.pWebHeaderLabel.text = @"Web";
        currentLabelY += labelYSpacing + self.pWebHeaderContainer.frame.size.height;
        
        self.pWebHeaderContainer.hidden = false;
        UIImage* pButtonImage = ExampleApp::Helpers::ImageHelpers::LoadImage(@"reviewsFromYelpRED");
        
        const CGFloat buttonX = roundf((self.pCloseButtonContainer.frame.size.width * 0.5f - pButtonImage.size.width * 0.5f));
        self.pVendorWebLinkButton = [[[UIButton alloc] initWithFrame:CGRectMake(buttonX,
                                                                                roundf(currentLabelY),
                                                                                pButtonImage.size.width,
                                                                                pButtonImage.size.height)] autorelease];
        
        // Set kCAFilterNearest for point filtering on link button, as button has baked text so needs to be pixel perfect.
        self.pVendorWebLinkButton.imageView.layer.minificationFilter = kCAFilterNearest;
        self.pVendorWebLinkButton.imageView.layer.magnificationFilter = kCAFilterNearest;
        
        [self.pVendorWebLinkButton setImage:pButtonImage forState:UIControlStateNormal];
        [self.pVendorWebLinkButton addTarget:self action:@selector(handleLinkClicked) forControlEvents:UIControlEventTouchUpInside];
        
        [self.pLabelsContainer addSubview: self.pVendorWebLinkButton];
        
        currentLabelY += labelYSpacing + pButtonImage.size.height;
    }
    
    if(!m_model.GetAddress().empty())
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
        
        std::string addressText = m_model.GetAddress();
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
        for(std::vector<std::string>::const_iterator it = categoriesList.begin(); it != categoriesList.end(); ++it)
        {
            categoriesText += (*it) + "\n";
        }
        
        self.pCategoriesContent.text = [NSString stringWithUTF8String:categoriesText.c_str()];
        self.pCategoriesContent.hidden = false;
        [self.pCategoriesContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pCategoriesContent.frame.size.height;
    }
    
    if(!m_model.GetReviews().empty())
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
        const std::vector<std::string>& reviewsList(m_model.GetReviews());
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
    m_isPinned = isPinned;
    [self updatePinnedButtonState];
    
    self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];
    
    [self.pCategoryIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
    std::string categoryIcon = ExampleApp::Helpers::IconResources::GetSmallIconForCategory(pModel->GetCategory());
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pCategoryIconContainer, categoryIcon, ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.pAddressHeaderContainer.hidden = true;
    self.pAddressContent.hidden = true;
    self.pPhoneHeaderContainer.hidden = true;
    self.pPhoneContent.hidden = true;
    self.pWebHeaderContainer.hidden = true;
    self.pPreviewImage.hidden = true;
    self.pCategoriesHeaderContainer.hidden = true;
    self.pCategoriesContent.hidden = true;
    self.pReviewsHeaderContainer.hidden = true;
    self.pReviewsContent.hidden = true;
    
    const CGFloat previewImagePlaceholderSize = 64.f;
    m_imageWidth = m_imageHeight = previewImagePlaceholderSize;
    m_ratingsImageWidth = RatingImageWidth;
    m_ratingsImageHeight = RatingImageHeight;
    
    [self performDynamicContentLayout];
    
    if(!pModel->GetImageUrl().empty())
    {
        [self.pPreviewImage setImage:nil];
        [self.pPreviewImageSpinner startAnimating];
    }
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
    if(url == m_model.GetImageUrl())
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
            
            [self performDynamicContentLayout];
        }
    }
}

- (void) setFullyActive
{
    if(self.alpha == 1.f)
    {
        return;
    }
    
    [self animateToAlpha:1.f];
}

- (void) setFullyInactive
{
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
    NSString* preFormattedUrlString = [NSString stringWithUTF8String:m_model.GetWebUrl().c_str()];
        
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
    if(m_isPinned)
    {
        [self.pPinButton setBackgroundImage:self->m_pRemovePinButtonBackgroundImage forState:UIControlStateNormal];
        [self.pPinButton setBackgroundImage:self->m_pRemovePinHighlightButtonBackgroundImage forState:UIControlStateHighlighted];
    }
    else
    {
        [self.pPinButton setBackgroundImage:self->m_pAddPinButtonBackgroundImage forState:UIControlStateNormal];
        [self.pPinButton setBackgroundImage:self->m_pAddPinHighlightButtonBackgroundImage forState:UIControlStateHighlighted];
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
