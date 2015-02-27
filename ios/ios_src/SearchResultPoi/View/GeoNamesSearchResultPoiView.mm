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
#include "GeoNamesSearchResultPoiView.h"
#include "App.h"

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
        self->m_pRemovePinButtonBackgroundImage = [[UIImage imageNamed:@"button_remove_pin_off.png"] retain];
        self->m_pRemovePinHighlightButtonBackgroundImage = [[UIImage imageNamed:@"button_remove_pin_on.png"] retain];
        self->m_pAddPinButtonBackgroundImage = [[UIImage imageNamed:@"button_add_pin_off.png"] retain];
        self->m_pAddPinHighlightButtonBackgroundImage = [[UIImage imageNamed:@"button_add_pin_on.png"] retain];
        
        m_pInterop = pInterop;
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        self.pShadowContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pShadowContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::BlackTone;
        self.pShadowContainer.alpha = 0.1f;
        [self addSubview: self.pShadowContainer];
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;
        [self addSubview: self.pControlContainer];
        
        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pControlContainer addSubview: self.pCloseButtonContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_off.png"] forState:UIControlStateNormal];
        [self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_on.png"] forState:UIControlStateHighlighted];
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
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;
        [self.pControlContainer addSubview: self.pHeadlineContainer];
        
        self.pCategoryIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pHeadlineContainer addSubview: self.pCategoryIconContainer];
        
        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pHeadlineContainer addSubview: self.pTitleLabel];
        
        self.pCountryHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCountryHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pLabelsContainer addSubview: self.pCountryHeaderContainer];
        
        self.pCountryHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
        [self.pCountryHeaderContainer addSubview: self.pCountryHeaderLabel];
        
        self.pCountryContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pCountryContent.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
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
    
    [self.pPinButton removeFromSuperview];
    [self.pPinButton release];
    
    [self.pCloseButtonContainer removeFromSuperview];
    [self.pCloseButtonContainer release];
    
    [self.pShadowContainer removeFromSuperview];
    [self.pShadowContainer release];
    
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
    
    [self.pCountryHeaderLabel removeFromSuperview];
    [self.pCountryHeaderLabel release];
    
    [self.pCountryHeaderContainer removeFromSuperview];
    [self.pCountryHeaderContainer release];
    
    [self.pCountryContent removeFromSuperview];
    [self.pCountryContent release];
    
    [self->m_pRemovePinButtonBackgroundImage release];
    [self->m_pRemovePinHighlightButtonBackgroundImage release];
    [self->m_pAddPinButtonBackgroundImage release];
    [self->m_pAddPinHighlightButtonBackgroundImage release];
    
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
    
    self.pShadowContainer.frame = CGRectMake(2.f,
                                             2.f,
                                             mainWindowWidth,
                                             mainWindowHeight);
    
    const float headlineHeight = 50.f;
    const float closeButtonSectionHeight = 80.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + headlineHeight);
    const float shadowHeight = 10.f;
    
    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                               0.f,
                                               mainWindowWidth,
                                               headlineHeight);
    
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pHeadlineContainer, "shadow_03", 0.f, headlineHeight, mainWindowWidth, shadowHeight);
    
    
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
    
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pContentContainer, "shadow_03", 0.f, contentSectionHeight, mainWindowWidth, shadowHeight);
    
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
}

- (void) performDynamicContentLayout:(CGFloat)imageWidth :(CGFloat)imageHeight
{
    const float headerLabelHeight = 16.f;
    const float labelYSpacing = 8.f;
    const float headerTextPadding = 3.0f;
    
    float currentLabelY = 8.f;
    
    if(!m_model.GetAddress().empty())
    {
        self.pCountryHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);
        self.pCountryHeaderContainer.hidden = false;
        
        self.pCountryHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, m_labelsSectionWidth - headerTextPadding, headerLabelHeight);
        self.pCountryHeaderLabel.text = @"Country";
        self.pCountryHeaderLabel.hidden = false;
        currentLabelY += labelYSpacing + self.pCountryHeaderLabel.frame.size.height;
        
        self.pCountryContent.frame = CGRectMake(headerTextPadding, currentLabelY, m_labelsSectionWidth - headerTextPadding, 85.f);
        self.pCountryContent.text = @"";
        self.pCountryContent.numberOfLines = 0;
        self.pCountryContent.adjustsFontSizeToFitWidth = NO;
        self.pCountryContent.lineBreakMode = NSLineBreakByTruncatingTail;
        
        std::string countryText = m_model.GetAddress();
        Eegeo::Helpers::SearchReplace(countryText,", ", "\n");
        self.pCountryContent.text = [NSString stringWithUTF8String:countryText.c_str()];
        self.pCountryContent.hidden = false;
        [self.pCountryContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pCountryContent.frame.size.height;
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
    
    self.pCountryHeaderContainer.hidden = true;
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

- (void) handlePinButtonSelected
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


@end
