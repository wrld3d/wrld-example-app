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
#include "EegeoJsonParser.h"
#include "EegeoSearchResultPoiView.h"
#include "App.h"
#import "UIButton+DefaultStates.h"

@interface EegeoSearchResultPoiView()<UIGestureRecognizerDelegate>
{
}
@end

const int PhoneAlertViewTag = 1;
const int DeletePinAlertViewTag = 2;

@implementation EegeoSearchResultPoiView

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;
{
    self = [super init];
    
    if(self)
    {
        m_pController = [UIViewController alloc];
        [m_pController setView:self];
        
        self->m_pRemovePinButtonBackgroundImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_remove_pin_off") retain];
        self->m_pRemovePinHighlightButtonBackgroundImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_remove_pin_on") retain];
        self->m_pAddPinButtonBackgroundImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_add_pin_off") retain];
        self->m_pAddPinHighlightButtonBackgroundImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_add_pin_on") retain];
        
        m_pInterop = pInterop;
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        self.pControlContainer.clipsToBounds = YES;
        [self addSubview: self.pControlContainer];
        
        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        self.pLabelsContainer.delegate = self;
        [self.pControlContainer addSubview: self.pLabelsContainer];
        
        self.pPreviewImageContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImageContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pLabelsContainer addSubview: self.pPreviewImageContainer];
        
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
        self.pTitleCardContainer.clipsToBounds = YES;
        [self.pControlContainer addSubview: self.pTitleCardContainer];
        
        self.pTagIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTagIconContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pTitleCardContainer addSubview: self.pTagIconContainer];
        
        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextTitleColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pTitleCardContainer addSubview: self.pTitleLabel];
        
        self.pSubtitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextTitleColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pTitleCardContainer addSubview: self.pSubtitleLabel];
        
        self.pTitleCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview:self.pTitleCardHeaderLine];
        
        self.pPreviewCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pPreviewImageContainer addSubview:self.pPreviewCardHeaderLine];
        
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
        [self.pPinButton setTitle:@"Drop Pin" forState:UIControlStateNormal];
        [self.pPinButton setTitleColor:ExampleApp::Helpers::ColorPalette::UiBorderColor forState:UIControlStateHighlighted];
        [self.pPinButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
        [self.pPinButton addTarget:self action:@selector(handlePinButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pDropPinContainer addSubview: self.pPinButton];
        
        self.pPreviewImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImage.clipsToBounds = YES;
        [self.pPreviewImageContainer addSubview: self.pPreviewImage];
        
        self.pPoiImageLoadingSpinner = [[[SearchResultPoiSpinner alloc] init] autorelease];
        self.pPoiImageLoadingSpinner.center = CGPointMake(0.0f, 0.0f);
        [self.pPreviewImage addSubview: self.pPoiImageLoadingSpinner];
        
        self.pAddressContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pDetailsCardContainer addSubview: self.pAddressContent];
        
        self.pDescriptionContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pDescriptionCardContainer addSubview: self.pDescriptionContent];
        
        self.pTagsContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pTagsCardContainer addSubview: self.pTagsContent];
        
        self.pPhoneContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextLinkColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        UITapGestureRecognizer* phoneTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnPhone:)];
        [self.pPhoneContent setUserInteractionEnabled:YES];
        [self.pPhoneContent addGestureRecognizer:phoneTappedGesture];
        [self.pDetailsCardContainer addSubview: self.pPhoneContent];
        
        self.pWebContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextLinkColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        UITapGestureRecognizer* webTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnLink:)];
        [self.pWebContent setUserInteractionEnabled:YES];
        [self.pWebContent addGestureRecognizer:webTappedGesture];
        [self.pDetailsCardContainer addSubview: self.pWebContent];
        
        self.pFacebookIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        UITapGestureRecognizer* facebookTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnFacebookLink:)];
        self.pFacebookIconContainer.image = [UIImage imageNamed:@"contact_icon_facebook"];
        [self.pFacebookIconContainer setUserInteractionEnabled:YES];
        [self.pFacebookIconContainer addGestureRecognizer:facebookTappedGesture];
        [self.pDetailsCardContainer addSubview: self.pFacebookIconContainer];
        
        self.pTwitterIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        UITapGestureRecognizer* twitterTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnTwitterLink:)];
        self.pTwitterIconContainer.image = [UIImage imageNamed:@"contact_icon_twitter"];
        [self.pTwitterIconContainer setUserInteractionEnabled:YES];
        [self.pTwitterIconContainer addGestureRecognizer:twitterTappedGesture];
        [self.pDetailsCardContainer addSubview: self.pTwitterIconContainer];
        
        self.pEmailIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        UITapGestureRecognizer* emailTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnEmailLink:)];
        self.pEmailIconContainer.image = [UIImage imageNamed:@"contact_icon_email"];
        [self.pEmailIconContainer setUserInteractionEnabled:YES];
        [self.pEmailIconContainer addGestureRecognizer:emailTappedGesture];
        [self.pDetailsCardContainer addSubview: self.pEmailIconContainer];
        
        self.pAddressIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pAddressIconContainer.image = [UIImage imageNamed:@"poi_address"];
        [self.pDetailsCardContainer addSubview: self.pAddressIconContainer];
        
        self.pPhoneIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPhoneIconContainer.image = [UIImage imageNamed:@"poi_phone_active"];
        [self.pDetailsCardContainer addSubview: self.pPhoneIconContainer];
        
        self.pWebIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pWebIconContainer.image = [UIImage imageNamed:@"detail_icon_web_link_active"];
        [self.pDetailsCardContainer addSubview: self.pWebIconContainer];
        
        self.pTagsIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTagsIconContainer.image = [UIImage imageNamed:@"poi_tag"];
        [self.pTagsCardContainer addSubview: self.pTagsIconContainer];
        
        self.pDescriptionIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionIconContainer.image =  [UIImage imageNamed:@"detail_icon_description"];
        [self.pDescriptionCardContainer addSubview: self.pDescriptionIconContainer];
        
        self.pFadeContainer = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"SearchResults_Fade"]] autorelease];
        self.pFadeContainer.hidden = NO;
        [self.pControlContainer addSubview: self.pFadeContainer];
        
        self.pFooterSpace = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pFooterSpace.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pFooterSpace];
        
        self.pWebView = [[[UIWebView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pWebView.scalesPageToFit = YES;
        self.pWebView.delegate = self;
        
        [self setTouchExclusivity: self];
        
        m_poiImageLoadedSuccessfully = true;
        m_htmlLoaded = true;
        m_webPageLoaded = false;
        m_webPageHeightSpecified = false;
    }
    
    return self;
}

- (void)dealloc
{
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pCloseButtonContainer removeFromSuperview];
    [self.pCloseButtonContainer release];
    
    [self.pPinButton removeFromSuperview];
    [self.pPinButton release];
    
    [self.pDropPinContainer removeFromSuperview];
    [self.pDropPinContainer release];
    
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];
    
    [self.pTitleCardContainer removeFromSuperview];
    [self.pTitleCardContainer release];
    
    [self.pDetailsCardContainer removeFromSuperview];
    [self.pDetailsCardContainer release];
    
    [self.pTagsCardContainer removeFromSuperview];
    [self.pTagsCardContainer release];
    
    [self.pLabelsContainer removeFromSuperview];
    [self.pLabelsContainer release];
    
    [self.pDescriptionCardContainer removeFromSuperview];
    [self.pDescriptionCardContainer release];
    
    [self.pTagIconContainer removeFromSuperview];
    [self.pTagIconContainer release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pSubtitleLabel removeFromSuperview];
    [self.pSubtitleLabel release];
    
    [self.pAddressContent removeFromSuperview];
    [self.pAddressContent release];
    
    [self.pPhoneContent removeFromSuperview];
    [self.pPhoneContent release];
    
    [self.pTagsContent removeFromSuperview];
    [self.pTagsContent release];
    
    [self.pPreviewImage removeFromSuperview];
    [self.pPreviewImage release];
    
    [self.pPoiImageLoadingSpinner removeFromSuperview];
    [self.pPoiImageLoadingSpinner release];
    
    [self.pWebContent removeFromSuperview];
    [self.pWebContent release];
    
    [self.pDescriptionContent removeFromSuperview];
    [self.pDescriptionContent release];
    
    [self.pAddressIconContainer removeFromSuperview];
    [self.pAddressIconContainer release];
    
    [self.pPhoneIconContainer removeFromSuperview];
    [self.pPhoneIconContainer release];
    
    [self.pWebIconContainer removeFromSuperview];
    [self.pWebIconContainer release];
    
    [self.pTagsIconContainer removeFromSuperview];
    [self.pTagsIconContainer release];
    
    [self.pDescriptionIconContainer removeFromSuperview];
    [self.pDescriptionIconContainer release];
    
    [self.pFacebookIconContainer removeFromSuperview];
    [self.pFacebookIconContainer release];
    
    [self.pTwitterIconContainer removeFromSuperview];
    [self.pTwitterIconContainer release];
    
    [self.pEmailIconContainer removeFromSuperview];
    [self.pEmailIconContainer release];
    
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
    
    [self.pPreviewImageContainer removeFromSuperview];
    [self.pPreviewImageContainer release];
    
    [self.pWebView removeFromSuperview];
    [self.pWebView release];
    
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
    const float boundsOccupyMultiplier = 0.9f;
    const float mainWindowWidth = std::min(boundsWidth * boundsOccupyMultiplier, 348.f);
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplier;
    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    const float headlineHeight = 50.f;
    const float pinButtonSectionHeight = 64.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - 46.f;
    const float contentSectionHeight = mainWindowHeight - (pinButtonSectionHeight + headlineHeight);
    
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
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    self.pControlContainer.frame = CGRectMake(0.f,
                                              0.f,
                                              mainWindowWidth,
                                              mainWindowHeight);
    
    self.pTitleCardContainer.frame = CGRectMake(sideMargin,
                                                currentCardYPos,
                                                cardContainerWidth,
                                                titleCardContainerHeight);
    
    currentCardYPos += titleCardContainerHeight + cardMargin;
    
    self.pLabelsContainer.frame = CGRectMake(sideMargin,
                                             currentCardYPos,
                                             cardContainerWidth,
                                             contentSectionHeight);
    
    m_labelsSectionWidth = cardContainerWidth;
    
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
                                         closeButtonSectionOffsetY - bottomMargin - 19.f,
                                         cardContainerWidth,
                                         19.f);
    
    self.pFooterLine.frame = CGRectMake(sideMargin,
                                        closeButtonSectionOffsetY - bottomMargin - 20.f,
                                        cardContainerWidth,
                                        headerLineThickness);
    
    self.pDropPinContainer.frame = CGRectMake(sideMargin,
                                              closeButtonSectionOffsetY - bottomMargin,
                                              cardContainerWidth,
                                              42.f);
    
    
    self.pPinButton.frame = CGRectMake(0.f,
                                       0.f,
                                       cardContainerWidth,
                                       42.f);
    
    self.pFadeContainer.frame = CGRectMake(sideMargin,
                                           closeButtonSectionOffsetY - 15.f - 60.f,
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
    
    if(self.pSubtitleLabel.text.length == 0)
    {
        self.pTitleLabel.frame = CGRectMake(titleCardImageSize + titlePadding,
                                            0.f,
                                            cardContainerWidth - titleCardImageSize * 2 - titlePadding * 2,
                                            titleCardImageSize);
        self.pTitleLabel.textAlignment = NSTextAlignmentLeft;
        self.pTitleLabel.lineBreakMode = NSLineBreakByTruncatingTail;
        self.pTitleLabel.font = [UIFont systemFontOfSize:22.0f];
        self.pSubtitleLabel.hidden = YES;
    }
    else
    {
        self.pTitleLabel.frame = CGRectMake(titleCardImageSize + titlePadding,
                                            0.f,
                                            cardContainerWidth - titleCardImageSize * 2 - titlePadding * 2,
                                            26.f);
        self.pTitleLabel.textAlignment = NSTextAlignmentLeft;
        self.pTitleLabel.lineBreakMode = NSLineBreakByTruncatingTail;
        self.pTitleLabel.font = [UIFont systemFontOfSize:22.0f];
        self.pSubtitleLabel.hidden = NO;
    }
    
    self.pSubtitleLabel.frame = CGRectMake(titleCardImageSize + titlePadding,
                                           26.f,
                                           cardContainerWidth - titleCardImageSize * 2 - titlePadding * 2,
                                           14.f);
    self.pSubtitleLabel.textAlignment = NSTextAlignmentLeft;
    self.pSubtitleLabel.font = [UIFont systemFontOfSize:12.0f];
    self.pSubtitleLabel.lineBreakMode = NSLineBreakByTruncatingTail;
    self.pSubtitleLabel.textColor = ExampleApp::Helpers::ColorPalette::TwitterDarkGrey;
}

- (void) performDynamicContentLayout
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const float boundsOccupyMultiplier = 0.9f;
    const float mainWindowWidth = std::min(boundsWidth * boundsOccupyMultiplier, 348.f);
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplier;
    const float labelYSpacing = 8.f;
    const float headerTextPadding = 3.0f;
    const float detailsImageSize = 18.f;
    const float detailsImageToTextMargin = 6.f;
    const float headerMargin = 10.f;
    const float sideMargin = 15.f;
    const float cardContainerWidth = mainWindowWidth - sideMargin * 2;
    const float cardTextHorizontalSpace = cardContainerWidth - detailsImageSize * 2 - headerMargin * 2.f;
    const float optionalPadding = 8.f;
    const float headerLineThickness = 1.f;
    
    const float headlineHeight = 50.f;
    const float pinButtonSectionHeight = 64.f;
    const float contentSectionHeight = mainWindowHeight - (pinButtonSectionHeight + headlineHeight);
    
    float currentLabelY = 0.f;
    
    float detailsCardY = 0.f;
    
    if(!m_eegeoModel.GetCustomViewUrl().empty())
    {
        NSString *errorMessage = [NSString stringWithCString:m_eegeoModel.GetCustomViewUrl().c_str()
                                                    encoding:[NSString defaultCStringEncoding]];
        int webViewHeight = cardContainerWidth;
        if(m_eegeoModel.GetCustomViewHeight() != -1)
        {
            m_webPageHeightSpecified = true;
            webViewHeight = m_eegeoModel.GetCustomViewHeight();
        }
        [self createWebViewWithHTML:CGRectMake(0, currentLabelY, cardContainerWidth, webViewHeight):errorMessage ];
        currentLabelY += self.pWebView.frame.size.height + headerMargin;
        self.pPreviewImage.frame = CGRectMake(0, 0, 0, 0);
    }
    else if(!m_eegeoModel.GetImageUrl().empty())
    {
        self.pPreviewImage.frame = CGRectMake(0.0f,
                                              currentLabelY,
                                              cardContainerWidth,
                                              cardContainerWidth *2.f/3.f);
        
        currentLabelY += (cardContainerWidth *2.f/3.f + headerMargin);
        
        self.pPreviewCardHeaderLine.frame = CGRectMake(0.f,
                                                       currentLabelY,
                                                       cardContainerWidth,
                                                       headerLineThickness);
        currentLabelY += headerMargin;
        if(!m_poiImageLoadedSuccessfully)
        {
            self.pPreviewImage.frame = CGRectMake(0.f, 0.f, 0.f, 0.f);
            currentLabelY -= (cardContainerWidth *2.f/3.f + headerMargin * 2);
        }
    }
    
    self.pDetailsCardContainer.frame = CGRectMake(0.f,
                                                  currentLabelY,
                                                  cardContainerWidth,
                                                  500.f);
    
    if(!m_eegeoModel.GetAddress().empty())
    {
        self.pAddressContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                                detailsCardY,
                                                cardTextHorizontalSpace,
                                                35.f);
        self.pAddressContent.text = @"";
        self.pAddressContent.numberOfLines = 0.f;
        self.pAddressContent.adjustsFontSizeToFitWidth = NO;
        self.pAddressContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string addressText = m_eegeoModel.GetAddress();
        Eegeo::Helpers::SearchReplace(addressText,", ", "\n");
        self.pAddressContent.text = [NSString stringWithUTF8String:addressText.c_str()];
        self.pAddressContent.hidden = false;
        [self.pAddressContent sizeToFit];
        
        self.pAddressIconContainer.frame = CGRectMake(headerTextPadding,
                                                      detailsCardY,
                                                      detailsImageSize,
                                                      detailsImageSize);
        
        detailsCardY += labelYSpacing + self.pAddressContent.frame.size.height;
        currentLabelY += labelYSpacing + self.pAddressContent.frame.size.height;
    }
    
    if(!m_eegeoModel.GetPhone().empty())
    {
        self.pPhoneContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                              detailsCardY,
                                              cardTextHorizontalSpace,
                                              35.f);
        self.pPhoneContent.lineBreakMode = NSLineBreakByTruncatingTail;
        self.pPhoneContent.adjustsFontSizeToFitWidth = YES;
        self.pPhoneContent.numberOfLines = 0;
        self.pPhoneContent.text = [NSString stringWithUTF8String:m_eegeoModel.GetPhone().c_str()];
        self.pPhoneContent.hidden = false;
        [self.pPhoneContent sizeToFit];
        
        self.pPhoneIconContainer.frame = CGRectMake(headerTextPadding,
                                                    detailsCardY,
                                                    detailsImageSize,
                                                    detailsImageSize);
        
        detailsCardY += labelYSpacing + self.pPhoneContent.frame.size.height;
        currentLabelY += labelYSpacing + self.pPhoneContent.frame.size.height;
    }
    
    if(!m_eegeoModel.GetWebUrl().empty())
    {
        self.pWebContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                            detailsCardY,
                                            cardTextHorizontalSpace,
                                            detailsImageSize);
        self.pWebContent.text = [NSString stringWithUTF8String:m_eegeoModel.GetWebUrl().c_str()];
        self.pWebContent.numberOfLines = 1;
        self.pWebContent.lineBreakMode = NSLineBreakByTruncatingTail;
        self.pWebContent.hidden = false;
        
        self.pWebIconContainer.frame = CGRectMake(headerTextPadding,
                                                  detailsCardY,
                                                  detailsImageSize,
                                                  detailsImageSize);
        
        detailsCardY += labelYSpacing + self.pWebContent.frame.size.height;
        currentLabelY += labelYSpacing + self.pWebContent.frame.size.height;
    }
    
    const float iconSize = 36.f;
    const float contactIconSpacing = 20.f;
    float contactIconCurrentXPos = headerTextPadding + detailsImageSize + detailsImageToTextMargin;

    if(!m_eegeoModel.GetEmail().empty() || !m_eegeoModel.GetFacebookUrl().empty() || !m_eegeoModel.GetTwitterUrl().empty())
    {
        currentLabelY += optionalPadding ;
        detailsCardY += optionalPadding;
    }
    
    if(!m_eegeoModel.GetEmail().empty())
    {
        self.pEmailIconContainer.frame = CGRectMake(contactIconCurrentXPos,
                                                    detailsCardY,
                                                    iconSize,
                                                    iconSize);
        
        contactIconCurrentXPos += iconSize + contactIconSpacing;
    }
    
    if(!m_eegeoModel.GetFacebookUrl().empty())
    {
        self.pFacebookIconContainer.frame = CGRectMake(contactIconCurrentXPos,
                                                       detailsCardY,
                                                       iconSize,
                                                       iconSize);
        
        contactIconCurrentXPos += iconSize + contactIconSpacing;
    }
    
    if(!m_eegeoModel.GetTwitterUrl().empty())
    {
        self.pTwitterIconContainer.frame = CGRectMake(contactIconCurrentXPos,
                                                      detailsCardY,
                                                      iconSize,
                                                      iconSize);
        
        contactIconCurrentXPos += iconSize + contactIconSpacing;
    }
    

    if(!m_eegeoModel.GetEmail().empty() || !m_eegeoModel.GetFacebookUrl().empty() || !m_eegeoModel.GetTwitterUrl().empty() || !m_eegeoModel.GetWebUrl().empty() || !m_eegeoModel.GetAddress().empty() || !m_eegeoModel.GetPhone().empty())
    {
        if(!m_eegeoModel.GetEmail().empty() || !m_eegeoModel.GetFacebookUrl().empty() || !m_eegeoModel.GetTwitterUrl().empty())
        {
            currentLabelY += labelYSpacing + iconSize + optionalPadding ;
            detailsCardY += labelYSpacing + iconSize + optionalPadding;
        }
        
        self.pDetailsCardHeaderLine.frame = CGRectMake(0.f,
                                                       detailsCardY,
                                                       cardContainerWidth,
                                                       1.f);
        currentLabelY += headerMargin;
    }
    
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
    
    if(!m_eegeoModel.GetDescription().empty())
    {
        self.pDescriptionContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                                    currentLabelY,
                                                    cardTextHorizontalSpace,
                                                    85.f);
        self.pDescriptionContent.text = @"";
        self.pDescriptionContent.numberOfLines = 0;
        self.pDescriptionContent.adjustsFontSizeToFitWidth = NO;
        self.pDescriptionContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string descriptionText = m_eegeoModel.GetDescription();
        self.pDescriptionContent.text = [NSString stringWithUTF8String:descriptionText.c_str()];
        self.pDescriptionContent.hidden = false;
        [self.pDescriptionContent sizeToFit];
        
        self.pDescriptionIconContainer.frame = CGRectMake(headerTextPadding,
                                                          currentLabelY,
                                                          detailsImageSize,
                                                          detailsImageSize);
        
        currentLabelY += labelYSpacing + self.pDescriptionContent.frame.size.height + 20.f;
    }
    
    [self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, currentLabelY + 15.f)];
    
    if (self.pLabelsContainer.contentSize.height < contentSectionHeight)
    {
        self.pFadeContainer.hidden = YES;
    }
}

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    m_webPageLoaded = true;
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    if(!m_webPageHeightSpecified)
    {
        CGRect frame = self.pWebView.frame;
        frame.size.height = 1;
        self.pWebView.frame = frame;
        CGSize fittingSize = [self.pWebView sizeThatFits:CGSizeZero];
        float minHeight = 300.f;
        float newHeight = std::max((float)fittingSize.height, minHeight);
        frame.size.height = newHeight;
        self.pWebView.frame = frame;
        self.pWebView.scalesPageToFit = YES;
        
        [self performDynamicContentLayout];
    }
}

- (void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    NSString* path = [[NSBundle mainBundle] pathForResource:@"page_not_found" ofType:@"html"];
    NSString* html = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:NULL];
    [webView loadHTMLString:html baseURL:nil];
}

- (void) createWebViewWithHTML:(CGRect)frame :(NSString*)url
{
     if(!m_webPageLoaded)
     {
        self.pWebView.frame = frame;

        [self.pWebView setBackgroundColor:[UIColor clearColor]];

        [self.pWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:url]]];
        
        [self.pLabelsContainer addSubview:self.pWebView];
     }
}

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    m_eegeoModel = ExampleApp::Search::EegeoPois::SdkModel::TransformToEegeoSearchResult(m_model);
    
    m_isPinned = isPinned;
    [self updatePinnedButtonState];
    
    self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];
    self.pSubtitleLabel.text = [NSString stringWithUTF8String:pModel->GetSubtitle().c_str()];
    
    [self.pTagIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
    std::string tagIcon = ExampleApp::Helpers::IconResources::GetSmallIconForTag(pModel->GetIconKey());
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pTagIconContainer, tagIcon, ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.pAddressContent.hidden = true;
    self.pWebContent.hidden = true;
    self.pPreviewImage.hidden = true;
    self.pTagsContent.hidden = true;
    self.pDescriptionContent.hidden = true;
    
    [self performDynamicContentLayout];
    
    if(!m_eegeoModel.GetImageUrl().empty())
    {
        self.pPreviewImage.hidden = NO;
        self.pPoiImageLoadingSpinner.center = CGPointMake(self.pPreviewImage.frame.size.width/2.f,
                                                          self.pPreviewImage.frame.size.height/2.f);
        [self.pPreviewImage setImage:nil];
        [self.pPoiImageLoadingSpinner startAnimating];
    }
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
    if(url == m_eegeoModel.GetImageUrl())
    {
        [self.pPoiImageLoadingSpinner stopAnimating];
        
        if(success)
        {
            m_poiImageLoadedSuccessfully = true;
            NSData* imageData = [NSData dataWithBytes:&bytes->at(0) length:bytes->size()];
            UIImage *image = [UIImage imageWithData:imageData];
            [self.pPreviewImage setImage:image];
            
            CGRect frame = self.pPreviewImage.frame;
            const CGFloat initialFrameHeight = frame.size.height;
            frame.size = image.size;
            frame.origin.x = self.frame.size.width * 0.5f - frame.size.width * 0.5f;
            self.pPreviewImage.frame = frame;
            self.pPreviewImage.contentMode = UIViewContentModeScaleAspectFill;
            
            [self.pPreviewImage.layer removeAllAnimations];
            
            const CGFloat imageContentHeightDifference = (image.size.height - initialFrameHeight);
            const CGFloat newContentHeight = self.pLabelsContainer.contentSize.height + imageContentHeightDifference;
            [self.pLabelsContainer setContentSize:CGSizeMake(self.pLabelsContainer.contentSize.width, newContentHeight)];
            
            [self performDynamicContentLayout];
        }
        else
        {
            m_poiImageLoadedSuccessfully = false;
            self.pPreviewImage.frame = CGRectMake(0, 0, 0, 0);
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
    NSString* preFormattedUrlString = [NSString stringWithUTF8String:m_eegeoModel.GetWebUrl().c_str()];
    
    NSString* webUrlString = ([preFormattedUrlString rangeOfString:@"://"].location != NSNotFound)
    ? preFormattedUrlString
    : [NSString stringWithFormat:@"http://%@", preFormattedUrlString];
    
    NSURL *url = [NSURL URLWithString:webUrlString];
    if (![[UIApplication sharedApplication] openURL:url])
    {
        NSLog(@"%@%@",@"Failed to open url:",[url description]);
    }
}


- (void) userTappedOnFacebookLink:(UITapGestureRecognizer *)recognizer
{
    [self handleFacebookLinkClicked];
}

- (void) handleFacebookLinkClicked
{
    NSString* preFormattedUrlString = [NSString stringWithUTF8String:m_eegeoModel.GetFacebookUrl().c_str()];
    
    NSString* webUrlString = ([preFormattedUrlString rangeOfString:@"http"].location != NSNotFound)
    ? preFormattedUrlString
    : [NSString stringWithFormat:@"http://%@", preFormattedUrlString];
    
    NSURL *url = [NSURL URLWithString:webUrlString];
    if (![[UIApplication sharedApplication] openURL:url])
    {
        NSLog(@"%@%@",@"Failed to open url:",[url description]);
    }
}


- (void) userTappedOnTwitterLink:(UITapGestureRecognizer *)recognizer
{
    [self handleTwitterLinkClicked];
}

- (void) handleTwitterLinkClicked
{
    NSString* preFormattedUrlString = [NSString stringWithUTF8String:m_eegeoModel.GetTwitterUrl().c_str()];
    
    NSString* webUrlString = ([preFormattedUrlString rangeOfString:@"http"].location != NSNotFound)
    ? preFormattedUrlString
    : [NSString stringWithFormat:@"http://%@", preFormattedUrlString];
    
    NSURL *url = [NSURL URLWithString:webUrlString];
    if (![[UIApplication sharedApplication] openURL:url])
    {
        NSLog(@"%@%@",@"Failed to open url:",[url description]);
    }
}

- (void) userTappedOnEmailLink:(UITapGestureRecognizer *)recognizer
{
    [self handleEmailLinkClicked];
}

- (void) handleEmailLinkClicked
{
    NSString *toEmail=[NSString stringWithUTF8String:m_eegeoModel.GetEmail().c_str()];
    NSString *subject=@"";
    NSString *body = @"";
    NSString *email = [NSString stringWithFormat:@"mailto:%@?subject=%@&body=%@", toEmail,subject,body];
    email = [email stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:email]];
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
        [self.pPinButton setImage:self->m_pRemovePinButtonBackgroundImage forState:UIControlStateNormal];
        [self.pPinButton setImage:self->m_pRemovePinHighlightButtonBackgroundImage forState:UIControlStateHighlighted];
        [self.pPinButton setTitle:@"Remove Pin" forState:UIControlStateNormal];
    }
    else
    {
        [self.pPinButton setImage:self->m_pAddPinButtonBackgroundImage forState:UIControlStateNormal];
        [self.pPinButton setImage:self->m_pAddPinHighlightButtonBackgroundImage forState:UIControlStateHighlighted];
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
