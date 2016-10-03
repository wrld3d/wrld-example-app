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

const float RatingImageWidth = 100.f;
const float RatingImageHeight = 30.f;
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
        [self addSubview: self.pControlContainer];
        
        self.pDetailsCardContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDetailsCardContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pDetailsCardContainer];
        
        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pDetailsCardContainer addSubview: self.pLabelsContainer];
        
        self.pTitleCardContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleCardContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pTitleCardContainer];
        
        self.pTagIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTagIconContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pTitleCardContainer addSubview: self.pTagIconContainer];
        
        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextTitleColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        self.pTitleLabel.adjustsFontSizeToFitWidth = YES;
        [self.pTitleCardContainer addSubview: self.pTitleLabel];
        
        self.pTitleCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview:self.pTitleCardHeaderLine];
        
        self.pDetailsCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDetailsCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview:self.pDetailsCardHeaderLine];
        
        self.pDescriptionCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview:self.pDescriptionCardHeaderLine];
        
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
        [self.pLabelsContainer addSubview: self.pPreviewImage];
        
        self.pPreviewImageSpinner = [[[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImageSpinner.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        self.pPreviewImageSpinner.center = CGPointZero;
        [self.pPreviewImage addSubview: self.pPreviewImageSpinner];
        
        self.pAddressContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pAddressContent];
        
        self.pPhoneContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextLinkColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        UITapGestureRecognizer* phoneTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnPhone:)];
        [self.pPhoneContent setUserInteractionEnabled:YES];
        [self.pPhoneContent addGestureRecognizer:phoneTappedGesture];
        
        [self.pLabelsContainer addSubview: self.pPhoneContent];
        
        self.pWebContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextLinkColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        UITapGestureRecognizer* webTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnLink:)];
        [self.pWebContent setUserInteractionEnabled:YES];
        [self.pWebContent addGestureRecognizer:webTappedGesture];
        [self.pLabelsContainer addSubview: self.pWebContent];
        
        self.pFacebookIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        UITapGestureRecognizer* facebookTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnFacebookLink:)];
        self.pFacebookIconContainer.image = [UIImage imageNamed:@"contact_icon_facebook"];
        [self.pFacebookIconContainer setUserInteractionEnabled:YES];
        [self.pFacebookIconContainer addGestureRecognizer:facebookTappedGesture];
        [self.pLabelsContainer addSubview: self.pFacebookIconContainer];
        
        self.pTwitterIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        UITapGestureRecognizer* twitterTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnTwitterLink:)];
        self.pTwitterIconContainer.image = [UIImage imageNamed:@"contact_icon_twitter"];
        [self.pTwitterIconContainer setUserInteractionEnabled:YES];
        [self.pTwitterIconContainer addGestureRecognizer:twitterTappedGesture];
        [self.pLabelsContainer addSubview: self.pTwitterIconContainer];
        
        self.pEmailIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        UITapGestureRecognizer* emailTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnEmailLink:)];
        self.pEmailIconContainer.image = [UIImage imageNamed:@"contact_icon_email"];
        [self.pEmailIconContainer setUserInteractionEnabled:YES];
        [self.pEmailIconContainer addGestureRecognizer:emailTappedGesture];
        [self.pLabelsContainer addSubview: self.pEmailIconContainer];
        
        self.pPinButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pPinButton setTitle:@"Drop Pin" forState:UIControlStateNormal];
        [self.pPinButton setTitleColor:ExampleApp::Helpers::ColorPalette::UiBorderColor forState:UIControlStateHighlighted];
        [self.pPinButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
        [self.pPinButton addTarget:self action:@selector(handlePinButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pDropPinContainer addSubview: self.pPinButton];
        
        self.pDescriptionContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        
        [self.pLabelsContainer addSubview: self.pDescriptionContent];
        
        self.pAddressIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pAddressIconContainer.image = [UIImage imageNamed:@"poi_address"];
        [self.pLabelsContainer addSubview: self.pAddressIconContainer];
        
        self.pPhoneIconContainer = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"poi_phone_active"]] autorelease];
        [self.pLabelsContainer addSubview: self.pPhoneIconContainer];
        
        self.pWebIconContainer = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"detail_icon_web_link_active"]] autorelease];
        [self.pLabelsContainer addSubview: self.pWebIconContainer];
        
        self.pTagsIconContainer = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"poi_tag"]] autorelease];
        [self.pLabelsContainer addSubview: self.pTagsIconContainer];
        
        self.pDescriptionIconContainer = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"detail_icon_description"]] autorelease];
        [self.pLabelsContainer addSubview: self.pDescriptionIconContainer];
        
        self.pFadeContainer = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"SearchResults_Fade"]] autorelease];
        self.pFadeContainer.hidden = YES;
        [self.pControlContainer addSubview: self.pFadeContainer];
        
        self.pTagsContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pTagsContent];
        
        self.pTagsCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTagsCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview:self.pTagsCardHeaderLine];
       
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

    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pCloseButtonContainer removeFromSuperview];
    [self.pCloseButtonContainer release];
    
    [self.pPinButton removeFromSuperview];
    [self.pPinButton release];
    
    [self.pDropPinContainer removeFromSuperview];
    [self.pDropPinContainer release];
    
    [self.pDropPinLabel removeFromSuperview];
    [self.pDropPinLabel release];
    
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
    
    [self.pTagIconContainer removeFromSuperview];
    [self.pTagIconContainer release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pAddressContent removeFromSuperview];
    [self.pAddressContent release];
    
    [self.pPhoneContent removeFromSuperview];
    [self.pPhoneContent release];
    
    [self.pTagsContent removeFromSuperview];
    [self.pTagsContent release];
    
    [self.pPreviewImage removeFromSuperview];
    //[self.pPreviewImage release];
    
    [self.pPreviewImageSpinner removeFromSuperview];
    [self.pPreviewImageSpinner release];
    
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
    
    [self.pDetailsCardHeaderLine removeFromSuperview];
    [self.pDetailsCardHeaderLine release];
    
    [self.pTagsCardHeaderLine removeFromSuperview];
    [self.pTagsCardHeaderLine release];
    
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
    const float closeButtonSectionOffsetY = mainWindowHeight - 46.f;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + headlineHeight);
    
    const float topMargin = 15.f;
    const float sideMargin = 10.f;
    const float cardMargin = 10.f;
    
    const float cardContainerWidth = 330.f;
    
    const float titleCardImageSize = 36.f;
    const float titleCardContainerHeight = 46.f;
    
    float currentCardYPos = 0.f;
    currentCardYPos += topMargin;
    
    self.pTitleCardContainer.frame = CGRectMake(sideMargin,
                                               currentCardYPos,
                                               cardContainerWidth,
                                               titleCardContainerHeight);
    
    currentCardYPos += titleCardContainerHeight + cardMargin;
    
    self.pDetailsCardContainer.frame = CGRectMake(sideMargin,
                                              currentCardYPos,
                                              cardContainerWidth,
                                              contentSectionHeight);
    
    currentCardYPos += 170 + cardMargin;
    
    const float labelsSectionOffsetX = 0.f;
    m_labelsSectionWidth = cardContainerWidth;
    
    self.pLabelsContainer.frame = CGRectMake(labelsSectionOffsetX,
                                             0.f,
                                             cardContainerWidth,
                                             contentSectionHeight);
    
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
                                                 1.f);
    
    self.pDropPinContainer.frame = CGRectMake(sideMargin,
                                              closeButtonSectionOffsetY - 15.f,
                                              330.f,
                                              42.f);
    
    
    self.pPinButton.frame = CGRectMake(0.f,
                                       0.f,
                                       330.f,
                                       42.f);
    
    self.pFadeContainer.frame = CGRectMake(0,
                                           closeButtonSectionOffsetY - 15.f - 40.f,
                                           330.f,
                                           40.f);

    [self.pPinButton setImageEdgeInsets:UIEdgeInsetsMake(6.f, 90.f, 6.f, 210.f)];

    [self.pPinButton setTitleEdgeInsets:UIEdgeInsetsMake(0.f, -self.pPinButton.titleLabel.frame.size.width + 40.f, 0.f, 0.f)];

    self.pPinButton.titleLabel.font = [UIFont systemFontOfSize:21.0f];
    
    self.pDropPinLabel.frame = CGRectMake(110.f,
                                          10.f,
                                          140.f,
                                          30.f);
    
    self.pTagIconContainer.frame = CGRectMake(0.f, 0.f, titleCardImageSize, titleCardImageSize);
    const float titlePadding = 10.0f;
    self.pTitleLabel.frame = CGRectMake(titleCardImageSize + titlePadding,
                                        0.f,
                                        240.f,
                                        titleCardImageSize);
    self.pTitleLabel.font = [UIFont systemFontOfSize:22.0f];
}

- (void) performDynamicContentLayout
{
    const float labelYSpacing = 8.f;
    const float headerTextPadding = 3.0f;
    const float detailsImageSize = 18.f;
    const float detailsImageToTextMargin = 6.f;
    const float headerMargin = 10.f;
    const float cardContainerWidth = 330.f;
    const float cardTextHorizontalSpace = 312.f;
    const float optionalPadding = 8.f;
    
    float currentLabelY = 8.f;
    
    if(!m_eegeoModel.GetImageUrl().empty())
    {
        currentLabelY = 0.f;
        self.pPreviewImage.frame = CGRectMake(0.0f, currentLabelY, cardContainerWidth, cardContainerWidth);
        self.pPreviewImageSpinner.center = [self.pPreviewImage convertPoint:self.pPreviewImage.center fromView:self.pPreviewImage.superview];
        currentLabelY += (cardContainerWidth + headerMargin);
        
        self.pDetailsCardHeaderLine.frame = CGRectMake(0.f,
                                                       currentLabelY,
                                                       cardContainerWidth,
                                                       1.f);
        
        currentLabelY += headerMargin;
    }
    
    if(!m_eegeoModel.GetAddress().empty())
    {
        self.pAddressContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin, currentLabelY, m_labelsSectionWidth - headerTextPadding, 85.f);
        self.pAddressContent.text = @"";
        self.pAddressContent.numberOfLines = 0;
        self.pAddressContent.adjustsFontSizeToFitWidth = NO;
        self.pAddressContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string addressText = m_eegeoModel.GetAddress();
        Eegeo::Helpers::SearchReplace(addressText,", ", "\n");
        self.pAddressContent.text = [NSString stringWithUTF8String:addressText.c_str()];
        self.pAddressContent.hidden = false;
        [self.pAddressContent sizeToFit];
        
        self.pAddressIconContainer.frame = CGRectMake(headerTextPadding, currentLabelY, detailsImageSize, detailsImageSize);
        
        currentLabelY += labelYSpacing + self.pAddressContent.frame.size.height;
    }
    
    if(!m_eegeoModel.GetPhone().empty())
    {
        self.pPhoneContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin, currentLabelY, cardTextHorizontalSpace, 32.f);
        self.pPhoneContent.text = [NSString stringWithUTF8String:m_eegeoModel.GetPhone().c_str()];
        self.pPhoneContent.hidden = false;
        [self.pPhoneContent sizeToFit];
        
        self.pPhoneIconContainer.frame = CGRectMake(headerTextPadding, currentLabelY, detailsImageSize, detailsImageSize);
        
        currentLabelY += labelYSpacing + self.pPhoneContent.frame.size.height;
    }
    
    if(!m_eegeoModel.GetWebUrl().empty())
    {
        self.pWebContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin, currentLabelY, cardTextHorizontalSpace, 32.f);
        self.pWebContent.text = [NSString stringWithUTF8String:m_eegeoModel.GetWebUrl().c_str()];
        self.pWebContent.hidden = false;
        [self.pWebContent sizeToFit];
        
        self.pWebIconContainer.frame = CGRectMake(headerTextPadding, currentLabelY, detailsImageSize, detailsImageSize);
        
        currentLabelY += labelYSpacing + self.pWebContent.frame.size.height + optionalPadding;
    }
    const float iconSize = 36.f;
    float contactIconCurrentXPos = 0.f;
    const float contactIconSpacing = 20.f;
    if(!m_eegeoModel.GetEmail().empty())
    {
        self.pEmailIconContainer.frame = CGRectMake(contactIconCurrentXPos, currentLabelY, iconSize, iconSize);
        contactIconCurrentXPos += iconSize + contactIconSpacing;
    }
    
    if(!m_eegeoModel.GetFacebookUrl().empty())
    {
        self.pFacebookIconContainer.frame = CGRectMake(contactIconCurrentXPos, currentLabelY, iconSize, iconSize);
        contactIconCurrentXPos += iconSize + contactIconSpacing;
    }
    
    if(!m_eegeoModel.GetTwitterUrl().empty())
    {
        self.pTwitterIconContainer.frame = CGRectMake(contactIconCurrentXPos, currentLabelY, iconSize, iconSize);
        contactIconCurrentXPos += iconSize + contactIconSpacing;
        currentLabelY += labelYSpacing + iconSize;
    }
    
    if(!m_model.GetHumanReadableTags().empty())
    {
        currentLabelY += optionalPadding;
        
        self.pTagsCardHeaderLine.frame = CGRectMake(0.f,
                                                    currentLabelY,
                                                    cardContainerWidth,
                                                    1.f);
        currentLabelY += headerMargin;

        self.pTagsContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin, currentLabelY, cardTextHorizontalSpace, 85.f);
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
        
        self.pTagsIconContainer.frame = CGRectMake(headerTextPadding, currentLabelY, detailsImageSize, detailsImageSize);
        
        currentLabelY += labelYSpacing + self.pTagsContent.frame.size.height;
    }
    
    if(!m_eegeoModel.GetDescription().empty())
    {
        self.pDescriptionCardHeaderLine.frame = CGRectMake(0.f,
                                                           currentLabelY,
                                                           cardContainerWidth,
                                                           1.f);
        currentLabelY += headerMargin;
        
        self.pDescriptionContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin, currentLabelY, cardTextHorizontalSpace - headerMargin * 2, 85.f);
        self.pDescriptionContent.text = @"";
        self.pDescriptionContent.numberOfLines = 0;
        self.pDescriptionContent.adjustsFontSizeToFitWidth = NO;
        self.pDescriptionContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string descriptionText = m_eegeoModel.GetDescription();
        self.pDescriptionContent.text = [NSString stringWithUTF8String:descriptionText.c_str()];
        self.pDescriptionContent.hidden = false;
        [self.pDescriptionContent sizeToFit];
        
        self.pDescriptionIconContainer.frame = CGRectMake(headerTextPadding, currentLabelY, detailsImageSize, detailsImageSize);
        
        currentLabelY += labelYSpacing + self.pDescriptionContent.frame.size.height + 20.f;
    }
    
    [self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, currentLabelY)];
}

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    m_eegeoModel = ExampleApp::Search::EegeoPois::SdkModel::TransformToEegeoSearchResult(m_model);

    m_isPinned = isPinned;
    [self updatePinnedButtonState];
    
    self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];
    
    [self.pTagIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
    std::string tagIcon = ExampleApp::Helpers::IconResources::GetSmallIconForTag(pModel->GetIconKey());
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pTagIconContainer, tagIcon, ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.pAddressContent.hidden = true;
    self.pWebContent.hidden = true;
    self.pPreviewImage.hidden = true;
    self.pTagsContent.hidden = true;
    self.pDescriptionContent.hidden = true;
    
    const CGFloat previewImagePlaceholderSize = 64.f;
    m_imageWidth = m_imageHeight = previewImagePlaceholderSize;
    m_ratingsImageWidth = RatingImageWidth;
    m_ratingsImageHeight = RatingImageHeight;
    
    [self performDynamicContentLayout];
    
    if(!m_eegeoModel.GetImageUrl().empty())
    {
        [self.pPreviewImage setImage:nil];
        [self.pPreviewImageSpinner startAnimating];
    }
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
    if(url == m_eegeoModel.GetImageUrl())
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
    NSString* preFormattedUrlString = [NSString stringWithUTF8String:m_eegeoModel.GetWebUrl().c_str()];
        
    NSString* webUrlString = ([preFormattedUrlString rangeOfString:@"http"].location != NSNotFound)
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
    NSString* preFormattedUrlString = [NSString stringWithUTF8String:m_eegeoModel.GetEmail().c_str()];
    
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
        [self.pPinButton setImage:self->m_pRemovePinButtonBackgroundImage forState:UIControlStateNormal];
        [self.pPinButton setImage:self->m_pRemovePinHighlightButtonBackgroundImage forState:UIControlStateHighlighted];
    }
    else
    {
        [self.pPinButton setImage:self->m_pAddPinButtonBackgroundImage forState:UIControlStateNormal];
        [self.pPinButton setImage:self->m_pAddPinHighlightButtonBackgroundImage forState:UIControlStateHighlighted];
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
