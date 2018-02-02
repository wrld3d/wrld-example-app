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
        
        self.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        
        self.pHeaderView = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview:self.pHeaderView];
        
        self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
        self.pTitleLabel.text = @"Options";
        self.pTitleLabel.font = [UIFont systemFontOfSize:24.f];
        [self.pHeaderView addSubview:self.pTitleLabel];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButton.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        self.pCloseButton.imageView.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        
        UIImage *closeImage = [UIImage imageNamed:@"Close_Blue"];
        
        [self.pCloseButton setImage:closeImage forState:UIControlStateNormal];
        [self.pCloseButton addTarget:self action:@selector(onCloseButtonTapped) forControlEvents:UIControlEventTouchUpInside];
       
        
        [self.pHeaderView addSubview:self.pCloseButton];
        
        self.pHeaderSeparator = [[[UIView alloc] init] autorelease];
        self.pHeaderSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
        [self addSubview:self.pHeaderSeparator];
        
        
        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pContentContainer];
        
        self.pWifiOnlyLabel = [[[UILabel alloc] init] autorelease];
        self.pWifiOnlyLabel.text = @"Stream over Wi-fi only";
        self.pWifiOnlyLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        [self.pContentContainer addSubview:self.pWifiOnlyLabel];
        
        self.pCacheEnabledLabel = [[[UILabel alloc] init] autorelease];
        self.pCacheEnabledLabel.text = @"Enable data caching on device";
        self.pCacheEnabledLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        [self.pContentContainer addSubview: self.pCacheEnabledLabel];
        
        self.pClearCacheLabel = [[[UILabel alloc] init] autorelease];
        self.pClearCacheLabel.text = @"Clear cached map data";
        self.pClearCacheLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        [self.pContentContainer addSubview:self.pClearCacheLabel];
        
        self.pReplayTutorialsLabel = [[[UILabel alloc] init] autorelease];
        self.pReplayTutorialsLabel.text = @"Play tutorial again";
        self.pReplayTutorialsLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        [self.pContentContainer addSubview:self.pReplayTutorialsLabel];
        
        UIImage *onImage =   [UIImage imageNamed:@"FullSwitchOn"];
        UIImage *offImage =  [UIImage imageNamed:@"FullSwitchOff"];
       
        self.pWifiOnlySwitch = [[[CustomSwitch alloc] initWithOnImage:onImage offImage:offImage] autorelease];
        [self.pWifiOnlySwitch addTarget:self action:@selector(wifiCheckboxSelectionHandler) forControlEvents:UIControlEventValueChanged];
        [self.pContentContainer addSubview:self.pWifiOnlySwitch];
        
        self.pCacheEnabledSwitch = [[[CustomSwitch alloc] initWithOnImage:onImage offImage:offImage] autorelease];
        
        [self.pCacheEnabledSwitch addTarget:self action:@selector(cacheEnabledCheckboxSelectionHandler) forControlEvents:UIControlEventValueChanged];
        [self.pContentContainer addSubview:self.pCacheEnabledSwitch];
        
        
        onImage =  [UIImage imageNamed:@"CheckboxRoundYes"];
        offImage = [UIImage imageNamed:@"CheckboxRound"];
        
        self.pClearCacheCheckbox = [[[CustomSwitch alloc] initWithOnImage:onImage offImage:offImage] autorelease];
        [self.pClearCacheCheckbox addTarget:self action:@selector(cacheClearSelectionHandler) forControlEvents:UIControlEventValueChanged];
        [self.pContentContainer addSubview:self.pClearCacheCheckbox];
        
        self.pReplayTutorialsCheckbox = [[[CustomSwitch alloc] initWithOnImage:onImage offImage:offImage] autorelease];
        [self.pReplayTutorialsCheckbox addTarget:self action:@selector(replayTutorialsSelectionHandler) forControlEvents:UIControlEventValueChanged];
        [self.pContentContainer addSubview:self.pReplayTutorialsCheckbox];
        
        self.pTickButton = [[UIButton alloc] init];
        
        self.pTickButton.backgroundColor = ExampleApp::Helpers::ColorPalette::TableSubCellColor;
        UIImage *tick = [UIImage imageNamed:@"LargeTick_Blue"];
        [self.pTickButton setImage:tick forState:UIControlStateNormal];
        [self.pTickButton addTarget:self action:@selector(onTickButtonTapped) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview:self.pTickButton];
        
        self.pContentSeparator = [[[UIView alloc] init] autorelease];
        self.pContentSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
        [self addSubview:self.pContentSeparator];
        
        self.pOptionsCacheClearSubView = [[[OptionsCacheClearSubView alloc] init] autorelease];
        
        [self setTouchExclusivity:self];
        
    }

    return self;
}

- (void)dealloc
{
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];

    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];
   
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    
    
    [self.pHeaderSeparator removeFromSuperview];
    [self.pHeaderSeparator release];
    
    [self.pContentSeparator removeFromSuperview];
    [self.pContentSeparator release];
    
    
    
    [self.pWifiOnlyLabel removeFromSuperview];
    [self.pWifiOnlyLabel release];
    
    [self.pCacheEnabledLabel removeFromSuperview];
    [self.pCacheEnabledLabel release];
    
    [self.pClearCacheLabel removeFromSuperview];
    [self.pClearCacheLabel release];
    
    [self.pReplayTutorialsLabel removeFromSuperview];
    [self.pReplayTutorialsLabel release];
    
    
    
    
    [self.pWifiOnlySwitch removeFromSuperview];
    [self.pWifiOnlySwitch release];
    
    [self.pCacheEnabledSwitch removeFromSuperview];
    [self.pCacheEnabledSwitch release];
    
    [self.pClearCacheCheckbox removeFromSuperview];
    [self.pClearCacheCheckbox release];
    
    [self.pReplayTutorialsCheckbox removeFromSuperview];
    [self.pReplayTutorialsCheckbox release];
    
   
    
    [self.pTickButton removeFromSuperview];
    [self.pTickButton release];
    
    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];
    
    
    [self.pOptionsCacheClearSubView removeFromSuperview];
    [self.pOptionsCacheClearSubView release];
    
    
    [self removeFromSuperview];
    [super dealloc];
    Eegeo_DELETE m_pInterop;
}

- (void)layoutSubviews
{
    self.alpha = 0.f;
    UIEdgeInsets outerMargin = UIEdgeInsetsMake(8.0, 8.0, 8.0, 8.0);
    UIEdgeInsets innerMargin = UIEdgeInsetsMake(20.0, 20.0, 16.0, 16.0);
    
    CGFloat headerHeight = 37;
    CGFloat tickHeight = 65;
    CGFloat rowHeight = 44;
    
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const float boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f) * 0.6f);
    const float mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
    const CGFloat contentHeight = 4*rowHeight + innerMargin.top + innerMargin.bottom;
    const float mainWindowHeight = headerHeight + contentHeight + tickHeight + outerMargin.top;
    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    CGFloat innerMarginWidth = mainWindowWidth - innerMargin.left - innerMargin.right;
    CGFloat outerMarginWidth = mainWindowWidth - outerMargin.left - outerMargin.right;
    
    self.pHeaderView.frame = CGRectMake(innerMargin.left, outerMargin.top, innerMarginWidth,headerHeight );
    
    CGFloat centeringOffsetY = 4.0;
    self.pTitleLabel.frame = CGRectMake(0.0,centeringOffsetY, innerMarginWidth - headerHeight,headerHeight);
    [self.pTitleLabel sizeToFit];
    self.pCloseButton.frame = CGRectMake(innerMarginWidth - headerHeight,0.0, headerHeight,headerHeight);
    
    self.pHeaderSeparator.frame = CGRectMake(outerMargin.left, self.pHeaderView.frame.origin.y + self.pHeaderView.frame.size.height + outerMargin.top, outerMarginWidth,1.0);
    
    CGFloat contentY = self.pHeaderSeparator.frame.origin.y +  self.pHeaderSeparator.frame.size.height;
    
    self.pContentContainer.frame  = CGRectMake(0.0,contentY , mainWindowWidth, contentHeight);
    
    CGFloat labelOffestY = 6.0;
    CGFloat switchOffestY = -8.0;
    CGFloat fontSize = 14.0;
    CGFloat switchWidth = 40;
    CGFloat switchHeight = rowHeight;
    
    self.pWifiOnlyLabel.frame = CGRectMake(innerMargin.left,innerMargin.top + 0.0*rowHeight + labelOffestY, innerMarginWidth, fontSize);
    self.pWifiOnlyLabel.font = [UIFont systemFontOfSize:fontSize];
    [self.pWifiOnlyLabel sizeToFit];
    
    self.pCacheEnabledLabel.frame = CGRectMake(innerMargin.left,innerMargin.top + 1.0*rowHeight + labelOffestY, innerMarginWidth, fontSize);
    self.pCacheEnabledLabel.font = [UIFont systemFontOfSize:fontSize];
    [self.pCacheEnabledLabel sizeToFit];
    
    self.pClearCacheLabel.frame = CGRectMake(innerMargin.left,innerMargin.top + 2.0*rowHeight + labelOffestY, innerMarginWidth, fontSize);
    self.pClearCacheLabel.font = [UIFont systemFontOfSize:fontSize];
    [self.pClearCacheLabel sizeToFit];
    
    self.pReplayTutorialsLabel.frame = CGRectMake(innerMargin.left,innerMargin.top + 3.0*rowHeight + labelOffestY, innerMarginWidth, fontSize);
    self.pReplayTutorialsLabel.font = [UIFont systemFontOfSize:fontSize];
    [self.pReplayTutorialsLabel sizeToFit];
    
    self.pWifiOnlySwitch.frame = CGRectMake(mainWindowWidth - switchWidth - innerMargin.right,innerMargin.top + 0.0*rowHeight + switchOffestY, switchWidth, switchHeight);
    [self.pWifiOnlySwitch layoutSubviews];
    
    self.pCacheEnabledSwitch.frame = CGRectMake(mainWindowWidth - switchWidth - innerMargin.right,innerMargin.top + 1.0*rowHeight + switchOffestY, switchWidth, switchHeight);
    [self.pCacheEnabledSwitch layoutSubviews];
    
    self.pClearCacheCheckbox.frame = CGRectMake(mainWindowWidth - switchWidth - innerMargin.right,innerMargin.top + 2.0*rowHeight + switchOffestY, switchWidth, switchHeight);
    [self.pClearCacheCheckbox layoutSubviews];
    
    self.pReplayTutorialsCheckbox.frame = CGRectMake(mainWindowWidth - switchWidth - innerMargin.right,innerMargin.top + 3.0*rowHeight + switchOffestY, switchWidth, switchHeight);
    [self.pReplayTutorialsCheckbox layoutSubviews];
    
    self.pContentSeparator.frame = CGRectMake(0.0 ,mainWindowHeight - tickHeight, mainWindowWidth, 1);
    self.pTickButton.frame = CGRectMake(0.0 ,mainWindowHeight - tickHeight, mainWindowWidth, tickHeight);
    self.pTickButton.imageView.frame = CGRectMake(mainWindowWidth-tickHeight,0.0,tickHeight,tickHeight);
    self.pTickButton.imageEdgeInsets = UIEdgeInsetsMake(0.0, mainWindowWidth-tickHeight, 0.0, 0.0);
    
  
}

- (void) setStreamOverWifiOnlySelected:(bool)isStreamOverWifiOnlySelected
{
    [self.pWifiOnlySwitch setOn:isStreamOverWifiOnlySelected];
}

- (void) setCacheEnabledSelected:(bool)isCacheEnabledSelected
{
    [self.pCacheEnabledSwitch setOn:isCacheEnabledSelected];
}

- (void) setReplayTutorialsSelected:(bool)isReplayTutorialsSelected
{
    [self.pReplayTutorialsCheckbox setOn:isReplayTutorialsSelected];
}

- (bool)isStreamOverWifiOnlySelected
{
    return self.pWifiOnlySwitch.isOn;
}

- (bool)isCacheEnabledSelected
{
    return self.pCacheEnabledSwitch.isOn;
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

- (void)cacheEnabledCheckboxSelectionHandler
{
    m_pInterop->HandleCacheEnabledSelectionStateChanged();
}

- (void)cacheClearSelectionHandler
{
    Eegeo_ASSERT(![[self pOptionsCacheClearSubView] isDisplayed]);
    
    [[self pOptionsCacheClearSubView] displayWarningInView:self.superview
                                                    target:self
                                                    action:@selector(clearCacheSelectionConfirmedHandler)];
    
}

- (void)replayTutorialsSelectionHandler
{
    bool isOn = self.pReplayTutorialsCheckbox.isOn;
    m_pInterop->HandleReplayTutorialsToggled(isOn);
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

- (void)onTickButtonTapped
{
    m_pInterop->HandleCloseSelected();
}

@end
