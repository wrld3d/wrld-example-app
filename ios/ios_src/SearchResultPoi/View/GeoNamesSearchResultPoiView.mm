// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "SearchResultPoiView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "StringHelpers.h"
#include "GeoNamesSearchResultPoiView.h"
#include "App.h"
#include "UIHelpers.h"

#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"

@interface GeoNamesSearchResultPoiView()<UIGestureRecognizerDelegate>
{
}
@end

@implementation GeoNamesSearchResultPoiView

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop
{
    self = [super init];
    
    if(self)
    {
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
        [self.pControlContainer addSubview: self.pLabelsContainer];
        
        self.pTitleCardContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleCardContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pTitleCardContainer];
        
        self.pTagIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTagIconContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pTitleCardContainer addSubview: self.pTagIconContainer];
        
        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextTitleColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        self.pTitleLabel.adjustsFontSizeToFitWidth = YES;
        [self.pTitleCardContainer addSubview: self.pTitleLabel];
        
        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pTitleCardContainer addSubview: self.pCloseButtonContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButton.contentMode = UIViewContentModeScaleAspectFit;
        self.pCloseButton.clipsToBounds = YES;
        [self.pCloseButton setDefaultStatesWithImageNames:@"exit_blue_x_button" :@"exit_dark_blue_x_button"];
        [self.pCloseButton addTarget:self action:@selector(handleClosedButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];

        self.pCountryContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pCountryContent];
        
        [self setTouchExclusivity: self];
        
        self.alpha = 0.f;
    }
    
    return self;
}

- (void)dealloc
{
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pCloseButtonContainer removeFromSuperview];
    [self.pCloseButtonContainer release];
    
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];
    
    [self.pTitleCardContainer removeFromSuperview];
    [self.pTitleCardContainer release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pLabelsContainer removeFromSuperview];
    [self.pLabelsContainer release];
    
    [self.pTitleCardHeaderLine removeFromSuperview];
    [self.pTitleCardHeaderLine release];
    
    [self.pTagIconContainer removeFromSuperview];
    [self.pTagIconContainer release];
    
    [self.pCountryContent removeFromSuperview];
    [self.pCountryContent release];
    
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
    
    const float topMargin = 15.f;
    const float sideMargin = 15.f;
    const float cardMargin = 10.f;
    
    const float cardContainerWidth = mainWindowWidth - sideMargin * 2;
   
    const float titleCardImageSize = 36.f;
    const float titleCardContainerHeight = 46.f;
    
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
    
    const float headlineHeight = 50.f;
    const float closeButtonSectionHeight = 64.f;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + headlineHeight);
    
    self.pTitleCardContainer.frame = CGRectMake(sideMargin,
                                                currentCardYPos,
                                                cardContainerWidth,
                                                titleCardContainerHeight);
    
    currentCardYPos += titleCardContainerHeight + cardMargin;
    
    m_labelsSectionWidth = cardContainerWidth;
    
    self.pLabelsContainer.frame = CGRectMake(sideMargin,
                                             currentCardYPos,
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
                                                 headerLineThickness);
    
    self.pTagIconContainer.frame = CGRectMake(0.f,
                                              0.f,
                                              headlineHeight,
                                              headlineHeight);
    
    const float titlePadding = 10.0f;
    self.pTitleLabel.frame = CGRectMake(titleCardImageSize + titlePadding,
                                        0.f,
                                        cardContainerWidth - titleCardImageSize * 2 - titlePadding * 2,
                                        titleCardImageSize);
    self.pTitleLabel.textAlignment = NSTextAlignmentLeft;
    self.pTitleLabel.font = [UIFont systemFontOfSize:22.0f];
    
    
    self.pTitleCardHeaderLine = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    self.pTitleCardHeaderLine.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
    [self.pControlContainer addSubview:self.pTitleCardHeaderLine];
}

- (void) performDynamicContentLayout:(CGFloat)imageWidth :(CGFloat)imageHeight
{
    const float labelYSpacing = 8.f;
    const float headerTextPadding = 3.0f;
    
    float currentLabelY = 8.f;
    
    if(!m_model.GetSubtitle().empty())
    {
        self.pCountryContent.frame = CGRectMake(headerTextPadding, currentLabelY, m_labelsSectionWidth - headerTextPadding, 85.f);
        self.pCountryContent.text = @"";
        self.pCountryContent.numberOfLines = 0;
        self.pCountryContent.adjustsFontSizeToFitWidth = NO;
        self.pCountryContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string countryText = m_model.GetSubtitle();
        Eegeo::Helpers::SearchReplace(countryText,", ", "\n");
        self.pCountryContent.text = [NSString stringWithUTF8String:countryText.c_str()];
        self.pCountryContent.hidden = false;
        [self.pCountryContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pCountryContent.frame.size.height;
    }
    
    [self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, currentLabelY)];
}

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    
    self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];
    
    [self.pTagIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
    std::string tagIcon = ExampleApp::Helpers::IconResources::GetSmallIconForTag(pModel->GetIconKey());
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pTagIconContainer, tagIcon, ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.pCountryContent.hidden = true;
    
    const CGFloat previewImagePlaceholderSize = 64.f;
    [self performDynamicContentLayout :previewImagePlaceholderSize :previewImagePlaceholderSize];
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
    
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

- (void) handleClosedButtonSelected
{
    m_pInterop->HandleCloseClicked();
}

@end
