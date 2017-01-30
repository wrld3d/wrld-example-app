// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "OptionsView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "OptionsViewInterop.h"
#include "UIHelpers.h"

#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"

@implementation OptionsView

- (id)initView
{
    self = [super init];

    if(self)
    {
        m_pInterop = Eegeo_NEW(ExampleApp::Options::View::OptionsViewInterop)(self);
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        const CGFloat buttonSize = 20.0;

        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self addSubview: self.pControlContainer];

        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview: self.pCloseButtonContainer];

        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
        [self.pCloseButton addTarget:self action:@selector(onCloseButtonTapped) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];

        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pContentContainer];

        self.pOptionsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pOptionsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentContainer addSubview: self.pOptionsContainer];

        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pHeadlineContainer];

        self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
        [self.pHeadlineContainer addSubview: self.pTitleLabel];
        
        self.pWifiOnlyCheckbox = [[[UILabelledCheckboxView alloc] initWithParams:buttonSize
                                                                                :"button_checkbox_off"
                                                                                :"button_checkbox_on"
                                                                                :"Stream over Wi-fi only"
                                                                                :false
                                                                                :self
                                                                                :@selector(wifiCheckboxSelectionHandler)] autorelease];

        [self.pOptionsContainer addSubview: self.pWifiOnlyCheckbox];
        
        self.pCacheEnabledCheckbox = [[[UILabelledCheckboxView alloc] initWithParams:buttonSize
                                                                                    :"button_checkbox_off"
                                                                                    :"button_checkbox_on"
                                                                                    :"Enable data caching on device"
                                                                                    :false
                                                                                    :self
                                                                                    :@selector(cacheCheckboxSelectionHandler)] autorelease];

        [self.pOptionsContainer addSubview: self.pCacheEnabledCheckbox];
        
        
        self.pClearCacheCheckbox = [[[UILabelledCheckboxView alloc] initWithParams:buttonSize
                                                                                    :"button_clear_cache_off"
                                                                                    :"button_clear_cache_on"
                                                                                    :"Clear cached map data"
                                                                                    :false
                                                                                    :self
                                                                                    :@selector(cacheClearSelectionHandler)] autorelease];
        
        [self.pOptionsContainer addSubview: self.pClearCacheCheckbox];
        
        [self setTouchExclusivity:self];
        
        self.pOptionsCacheClearSubView = [[[OptionsCacheClearSubView alloc] init] autorelease];
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

    [self.pHeadlineContainer removeFromSuperview];
    [self.pHeadlineContainer release];
    
    [self.pClearCacheLabel removeFromSuperview];
    [self.pClearCacheLabel release];
    
    [self.pClearCacheCheckbox removeFromSuperview];
    [self.pClearCacheCheckbox release];
    
    [self.pCacheEnabledCheckbox removeFromSuperview];
    [self.pCacheEnabledCheckbox release];
    
    [self.pWifiOnlyCheckbox removeFromSuperview];
    [self.pWifiOnlyCheckbox release];
    
    [self.pOptionsContainer removeFromSuperview];
    [self.pOptionsContainer release];

    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];

    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pOptionsCacheClearSubView removeFromSuperview];
    [self.pOptionsCacheClearSubView release];

    [self removeFromSuperview];
    [super dealloc];
    Eegeo_DELETE m_pInterop;
}

- (void)layoutSubviews
{
    self.alpha = 0.f;

    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const float boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f) * 0.6f);
    const float boundsOccupyHeightMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f));
    const float mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
    const float mainWindowHeight = boundsHeight * boundsOccupyHeightMultiplier;
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
    const float headlineMargin = 10.f;
    const float closeButtonSectionHeight = 64.f;
    const float headlineOffsetY = 10.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
    const float contentSectionOffsetY = headlineOffsetY + headlineHeight;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + contentSectionOffsetY);

    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                    headlineOffsetY,
                                    mainWindowWidth,
                                    headlineHeight);

    self.pContentContainer.frame = CGRectMake(0.f,
                                   contentSectionOffsetY,
                                   mainWindowWidth,
                                   contentSectionHeight);

    const float labelsSectionOffsetX = 8.f;
    const float labelsSectionWidth = mainWindowWidth - (2.f * labelsSectionOffsetX);
    
    self.pOptionsContainer.frame = CGRectMake(labelsSectionOffsetX,
                                              0.f,
                                              labelsSectionWidth,
                                              contentSectionHeight);

    self.pCloseButtonContainer.frame = CGRectMake(0.f,
                                       closeButtonSectionOffsetY,
                                       mainWindowWidth,
                                       closeButtonSectionHeight);

    self.pCloseButton.frame = CGRectMake(mainWindowWidth - closeButtonSectionHeight,
                                         0.f,
                                         closeButtonSectionHeight,
                                         closeButtonSectionHeight);

    const float headlineWidth = mainWindowWidth - headlineMargin;

    self.pTitleLabel.frame = CGRectMake(headlineMargin,
                                        0.f,
                                        headlineWidth,
                                        headlineHeight);
    self.pTitleLabel.font = [UIFont systemFontOfSize:18.0f];

    self.pTitleLabel.text = @"Options";

    const float optionsContentY = 20.f;
    const float optionsDeltaY = 40.f;
    
    CGRect wifiCheckboxFrame = self.pWifiOnlyCheckbox.frame;
    wifiCheckboxFrame.origin.y = optionsContentY + (optionsDeltaY * 0);
    self.pWifiOnlyCheckbox.frame = wifiCheckboxFrame;
    
    CGRect cacheEnabledCheckboxFrame = self.pCacheEnabledCheckbox.frame;
    cacheEnabledCheckboxFrame.origin.y = optionsContentY + (optionsDeltaY * 1);
    self.pCacheEnabledCheckbox.frame = cacheEnabledCheckboxFrame;
    
    CGRect clearCacheButtonFrame = self.pClearCacheCheckbox.frame;
    clearCacheButtonFrame.origin.y = optionsContentY + (optionsDeltaY * 2);
    self.pClearCacheCheckbox.frame = clearCacheButtonFrame;
    
    CGRect clearCacheLabelFrame = self.pClearCacheLabel.frame;
    clearCacheLabelFrame.origin.x = clearCacheButtonFrame.origin.x + clearCacheButtonFrame.size.width + 5.0;
    clearCacheLabelFrame.origin.y = clearCacheButtonFrame.origin.y + ((clearCacheButtonFrame.size.height / 2.0) - (clearCacheLabelFrame.size.height / 2.0));
    self.pClearCacheLabel.frame = clearCacheLabelFrame;
}

- (void) setStreamOverWifiOnlySelected:(bool)isStreamOverWifiOnlySelected
{
    [self.pWifiOnlyCheckbox setVisualSelectionState:isStreamOverWifiOnlySelected];
}

- (void) setCacheEnabledSelected:(bool)isCacheEnabledSelected
{
    [self.pCacheEnabledCheckbox setVisualSelectionState:isCacheEnabledSelected];
}

- (void) setReplayTutorialsSelected:(bool)isReplayTutorialsSelected
{
    // To be implemented in the future.
    // Currently only implented in windows.
}

- (bool)isStreamOverWifiOnlySelected
{
    return [self.pWifiOnlyCheckbox isSelected];
}

- (bool)isCacheEnabledSelected
{
    return [self.pCacheEnabledCheckbox isSelected];
}

- (void)concludeCacheClearCeremony
{
    Eegeo_ASSERT([[self pOptionsCacheClearSubView] isDisplayed]);
    [[self pOptionsCacheClearSubView] conclude];
}

- (void)wifiCheckboxSelectionHandler
{
    m_pInterop->HandleStreamOverWifiOnlySelectionStateChanged();
}

- (void)cacheCheckboxSelectionHandler
{
    m_pInterop->HandleCacheEnabledSelectionStateChanged();
}

- (void)cacheClearSelectionHandler
{
    Eegeo_ASSERT(![[self pOptionsCacheClearSubView] isDisplayed]);
    [[self pOptionsCacheClearSubView] displayWarning:self:@selector(clearCacheSelectionConfirmedHandler)];
}

- (void)clearCacheSelectionConfirmedHandler
{
    m_pInterop->HandleClearCacheSelected();
}

- (ExampleApp::Options::View::OptionsViewInterop*)getInterop
{
    return m_pInterop;
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

- (void)onCloseButtonTapped
{
    m_pInterop->HandleCloseSelected();
}

@end
