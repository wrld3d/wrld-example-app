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
        
        self.pHeaderView = [[[HeaderView alloc] initWithWidth:200 title:@"Options"] autorelease];
        [self addSubview:self.pHeaderView];
        [self.pHeaderView addTarget:self action:@selector(onCloseButtonTapped) forControlEvents:UIControlEventTouchUpInside];
        
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
        
        self.pClearCacheButton = [[[UIButton alloc] init] autorelease];
        [self.pClearCacheButton setTitle:@"OK" forState:UIControlStateNormal];
        [self.pClearCacheButton.titleLabel setFont:[UIFont systemFontOfSize:14]];
        [self.pClearCacheButton setDefaultStatesWithNormalImageName:@""
                                                 highlightImageName:@""
                                              normalBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor
                                           highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColorAlt];
        [self.pClearCacheButton addTarget:self action:@selector(cacheClearSelectionHandler) forControlEvents:UIControlEventTouchUpInside];
        [self.pContentContainer addSubview:self.pClearCacheButton];
        
        self.pReplayTutorialsButton = [[[UIButton alloc] init] autorelease];
        [self.pReplayTutorialsButton addTarget:self action:@selector(replayTutorialsSelectionHandler) forControlEvents:UIControlEventTouchUpInside];
        [self.pReplayTutorialsButton setDefaultStatesWithNormalImageName:@""
                                                      highlightImageName:@""
                                                   normalBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor
                                                highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColorAlt];
        [self.pReplayTutorialsButton setTitle:@"OK" forState:UIControlStateNormal];
        [self.pReplayTutorialsButton.titleLabel setFont:[UIFont systemFontOfSize:14]];
        [self.pContentContainer addSubview:self.pReplayTutorialsButton];
        
        self.pOptionsCacheClearSubView = [[[OptionsCacheClearSubView alloc] init] autorelease];
        
        self.pReplayTutorialsMessage = [[[MessageView alloc] initWithFrame:self.bounds title:@"Replay Tutorials" message:@"The help panels will be visible again when you enter or leave a building."] autorelease];
        self.pReplayTutorialsMessage.hidden = true;
        [self addSubview:self.pReplayTutorialsMessage];

        [self setTouchExclusivity:self];
    }
    
    return self;
}

- (void)dealloc
{
    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];
    
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
    
    [self.pClearCacheButton removeFromSuperview];
    [self.pClearCacheButton release];
    
    [self.pReplayTutorialsButton removeFromSuperview];
    [self.pReplayTutorialsButton release];
    
    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];
    
    [self.pOptionsCacheClearSubView removeFromSuperview];
    [self.pOptionsCacheClearSubView release];
    
    [self.pReplayTutorialsMessage removeFromSuperview];
    [self.pReplayTutorialsMessage release];
    
    [self removeFromSuperview];
    [super dealloc];
    
    Eegeo_DELETE m_pInterop;
}

- (void)layoutSubviews
{
    self.alpha = 0.f;
    
    CGFloat rowHeight = 44;
    
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const float boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f) * 0.6f);
    const float mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
    
    self.pHeaderView.width = mainWindowWidth;
    [self.pHeaderView layoutIfNeeded];
    
    UIEdgeInsets innerMargin = UIEdgeInsetsMake(self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin);
    CGFloat innerMarginWidth = mainWindowWidth - innerMargin.left - innerMargin.right;
    CGFloat contentY = self.pHeaderView.frame.origin.y +  self.pHeaderView.frame.size.height;
    
    const CGFloat contentHeight = 4*rowHeight + innerMargin.top + innerMargin.bottom;
    const float mainWindowHeight = self.pHeaderView.frame.size.height + contentHeight;
    
    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    self.pReplayTutorialsMessage.frame = self.bounds;
    [self.pReplayTutorialsMessage setNeedsLayout];
    [self.pReplayTutorialsMessage layoutIfNeeded];
    
    self.pOptionsCacheClearSubView.frame = self.frame;
    
    
    self.pContentContainer.frame  = CGRectMake(0.0,contentY , mainWindowWidth, contentHeight);
    
    CGFloat labelOffestY = 6.0;
    CGFloat switchOffestY = -8.0;
    CGFloat fontSize = 14.0;
    CGFloat switchWidth = 40;
    CGFloat switchHeight = rowHeight;
    CGFloat buttonHeight = 20;
    CGFloat buttonOffsetY = switchOffestY + 0.5*(switchHeight - buttonHeight);
    
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
    [self.pWifiOnlySwitch setNeedsLayout];
    
    self.pCacheEnabledSwitch.frame = CGRectMake(mainWindowWidth - switchWidth - innerMargin.right,innerMargin.top + 1.0*rowHeight + switchOffestY, switchWidth, switchHeight);
    [self.pCacheEnabledSwitch setNeedsLayout];
    
    self.pClearCacheButton.frame = CGRectMake(mainWindowWidth - switchWidth - innerMargin.right,innerMargin.top + 2.0*rowHeight + buttonOffsetY, switchWidth, buttonHeight);
    [self.pClearCacheButton setNeedsLayout];
    
    self.pReplayTutorialsButton.frame = CGRectMake(mainWindowWidth - switchWidth - innerMargin.right,innerMargin.top + 3.0*rowHeight + buttonOffsetY, switchWidth, buttonHeight);
    [self.pReplayTutorialsButton setNeedsLayout];
   
}
- (void) setStreamOverWifiOnlySelected:(bool)isStreamOverWifiOnlySelected
{
    [self.pWifiOnlySwitch setOn:isStreamOverWifiOnlySelected];
}

- (void) setCacheEnabledSelected:(bool)isCacheEnabledSelected
{
    [self.pCacheEnabledSwitch setOn:isCacheEnabledSelected];
}

- (bool)isStreamOverWifiOnlySelected
{
    return self.pWifiOnlySwitch.isOn;
}

- (bool)isCacheEnabledSelected
{
    return self.pCacheEnabledSwitch.isOn;
}

- (void)openClearCacheWarning
{
    Eegeo_ASSERT(![[self pOptionsCacheClearSubView] isDisplayed]);
    
    [[self pOptionsCacheClearSubView] displayWarningInView:self.superview
                                                    target:self
                                                    action:@selector(clearCacheSelectionConfirmedHandler)];
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
    m_pInterop->HandleClearCacheSelected();
}

- (void)replayTutorialsSelectionHandler
{
    m_pInterop->HandleReplayTutorialsSelected();
    [self.pReplayTutorialsMessage show];
}

- (void)clearCacheSelectionConfirmedHandler
{
    m_pInterop->HandleClearCacheTriggered();
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
