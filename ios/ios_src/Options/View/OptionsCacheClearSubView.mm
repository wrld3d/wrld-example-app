// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "Types.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "OptionsCacheClearSubView.h"
#import "UIView+TouchExclusivity.h"
#include "App.h"

@implementation OptionsCacheClearSubView

- (id)init
{
    self = [super init];
    
    if(self)
    {
        self.pDarkBackgroundPanel = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDarkBackgroundPanel.backgroundColor = ExampleApp::Helpers::ColorPalette::BlackTone;
        self.pDarkBackgroundPanel.alpha = 0.4f;
        [self addSubview: self.pDarkBackgroundPanel];
        
        self.pShadowContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pShadowContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::BlackTone;
        self.pShadowContainer.alpha = 0.1f;
        [self addSubview: self.pShadowContainer];
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self addSubview: self.pControlContainer];
        
        self.pOptionButtonsContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pOptionButtonsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pControlContainer addSubview: self.pOptionButtonsContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_off.png"] forState:UIControlStateNormal];
        [self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_on.png"] forState:UIControlStateHighlighted];
        [self.pCloseButton addTarget:self action:@selector(handleCloseClicked) forControlEvents:UIControlEventTouchUpInside];
        [self.pOptionButtonsContainer addSubview: self.pCloseButton];
        
        self.pConfirmButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pConfirmButton setBackgroundImage:[UIImage imageNamed:@"button_ok_off.png"] forState:UIControlStateNormal];
        [self.pConfirmButton setBackgroundImage:[UIImage imageNamed:@"button_ok_on.png"] forState:UIControlStateHighlighted];
        [self.pConfirmButton addTarget:self action:@selector(handleConfirmClicked) forControlEvents:UIControlEventTouchUpInside];
        [self.pOptionButtonsContainer addSubview: self.pConfirmButton];
        
        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pControlContainer addSubview: self.pContentContainer];
        
        self.pContainerShadowBottom = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pContentContainer, "shadow_03", 0.f, 0.f, 0, 0);
        
        self.pMessageContent = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pMessageContent.textColor = ExampleApp::Helpers::ColorPalette::BlackTone;
        self.pMessageContent.numberOfLines = 0;
        [self.pContentContainer addSubview: self.pMessageContent];
        
        self.pSpinner = [[[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pSpinner.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhiteLarge;
        self.pSpinner.color = [UIColor grayColor];
        [self.pContentContainer addSubview: self.pSpinner];
        
        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pControlContainer addSubview: self.pHeadlineContainer];
        
        self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pHeadlineContainer addSubview: self.pTitleLabel];
        
        self.pContainerShadowTop = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pContentContainer, "shadow_03", 0.f, 0.f, 0, 0);
        
        [self setTouchExclusivity:self];
        
        [self resetState];
    }
    
    return self;
}

- (void)dealloc
{
    [self.pDarkBackgroundPanel removeFromSuperview];
    [self.pDarkBackgroundPanel release];
    
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pConfirmButton removeFromSuperview];
    [self.pConfirmButton release];
    
    [self.pOptionButtonsContainer removeFromSuperview];
    [self.pOptionButtonsContainer release];
    
    [self.pShadowContainer removeFromSuperview];
    [self.pShadowContainer release];
    
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];
    
    [self.pHeadlineContainer removeFromSuperview];
    [self.pHeadlineContainer release];
    
    [self.pContainerShadowTop removeFromSuperview];
    [self.pContainerShadowTop release];
    
    [self.pContainerShadowBottom removeFromSuperview];
    [self.pContainerShadowBottom release];
    
    [self.pSpinner removeFromSuperview];
    [self.pSpinner release];
    
    [self.pMessageContent removeFromSuperview];
    [self.pMessageContent release];
    
    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void)layoutSubviews
{
    self.alpha = 1.f;
    
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = App::IsDeviceSmall();
    const float boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : (2.f/3.f);
    const float boundsOccupyHeightMultiplier = useFullScreenSize ? 0.9f : 0.5f;
    const float mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
    const float mainWindowHeight = boundsHeight * boundsOccupyHeightMultiplier;
    const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(0.f,
                            0.f,
                            boundsWidth,
                            boundsHeight);
    
    self.pDarkBackgroundPanel.frame = CGRectMake(0.f,
                                                 0.f,
                                                 boundsWidth,
                                                 boundsHeight);
    
    self.pControlContainer.frame = CGRectMake(mainWindowX,
                                              mainWindowY,
                                              mainWindowWidth,
                                              mainWindowHeight);
    
    self.pShadowContainer.frame = CGRectMake(mainWindowX + 2.f,
                                             mainWindowY + 2.f,
                                             mainWindowWidth,
                                             mainWindowHeight);
    
    const float headlineHeight = 50.f;
    const float headlineMargin = 10.f;
    const float optionButtonSectionHeight = 80.f;
    const float headlineOffsetY = 10.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - optionButtonSectionHeight;
    const float contentSectionOffsetY = headlineOffsetY + headlineHeight;
    const float contentSectionHeight = mainWindowHeight - (optionButtonSectionHeight + headlineHeight);
    const float shadowHeight = 10.f;
    
    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                               headlineOffsetY,
                                               mainWindowWidth,
                                               headlineHeight);
    
    self.pContentContainer.frame = CGRectMake(0.f,
                                              contentSectionOffsetY,
                                              mainWindowWidth,
                                              contentSectionHeight);
    
    const float messagePadding(10.f);
    
    self.pMessageContent.frame = CGRectMake(messagePadding,
                                            messagePadding,
                                            mainWindowWidth - messagePadding,
                                            contentSectionHeight - messagePadding);
    
    self.pMessageContent.textAlignment = NSTextAlignmentCenter;
    self.pMessageContent.userInteractionEnabled = NO;
    self.pMessageContent.font = [UIFont systemFontOfSize:18.0f];
    
    self.pSpinner.frame = CGRectMake(mainWindowWidth * 0.5f - 30.f,
                                     contentSectionHeight - 70.f,
                                     60.f,
                                     60.f);
    
    [self setSpinnerEnabled:NO];
    
    self.pContainerShadowTop.frame = CGRectMake(0.f, 0.f, mainWindowWidth, shadowHeight);
    
    self.pOptionButtonsContainer.frame = CGRectMake(0.f,
                                                    closeButtonSectionOffsetY,
                                                    mainWindowWidth,
                                                    optionButtonSectionHeight);
    
    self.pCloseButton.frame = CGRectMake(mainWindowWidth - optionButtonSectionHeight,
                                         0.f,
                                         optionButtonSectionHeight,
                                         optionButtonSectionHeight);
    
    self.pConfirmButton.frame = CGRectMake(0.f,
                                           0.f,
                                           optionButtonSectionHeight,
                                           optionButtonSectionHeight);
    
    self.pContainerShadowBottom.frame = CGRectMake(0.f, contentSectionHeight, mainWindowWidth, shadowHeight);
    
    const float headlineWidth = mainWindowWidth - headlineMargin;
    
    self.pTitleLabel.frame = CGRectMake(headlineMargin,
                                        0.f,
                                        headlineWidth,
                                        headlineHeight);
    self.pTitleLabel.font = [UIFont systemFontOfSize:18.0f];
}

- (bool) isDisplayed
{
    return m_displayed;
}

- (void) displayWarning:(UIView*)pConfirmedHandlerInstance :(SEL)confirmedHandler
{
    Eegeo_ASSERT(pConfirmedHandlerInstance != nil);
    Eegeo_ASSERT(confirmedHandler != nil);
    Eegeo_ASSERT(![self isDisplayed]);
    Eegeo_ASSERT(m_pConfirmedHandlerInstance == nil);
    Eegeo_ASSERT(m_confirmedHandler == nil);
    
    m_displayed = true;
    m_pConfirmedHandlerInstance = pConfirmedHandlerInstance;
    m_confirmedHandler = confirmedHandler;
    
    [pConfirmedHandlerInstance.superview addSubview:self];
    
    self.pTitleLabel.text = @"Warning";
    self.pMessageContent.text = @"Are you sure you want to remove all stored data?";
}

- (void) conclude
{
    Eegeo_ASSERT([self isDisplayed]);
    
    const double nowSeconds = [[NSDate date] timeIntervalSince1970];
    NSTimeInterval remainingIntervalUntilEndTime = m_cacheClearDialogMinimumEndTimeSeconds - nowSeconds;
    
    if(remainingIntervalUntilEndTime <= 0.0)
    {
        [self closeAsyncCacheClearDialog];
    }
    else
    {
        [NSTimer scheduledTimerWithTimeInterval:remainingIntervalUntilEndTime
                                         target:self
                                       selector:@selector(closeAsyncCacheClearDialog)
                                       userInfo:nil
                                        repeats:NO];
    }
}

- (void) closeAsyncCacheClearDialog
{
    self.pMessageContent.text = @"Map data deleted from device";
    self.pCloseButton.hidden = NO;
    [self setSpinnerEnabled:NO];
}

- (void) resetState
{
    [self setSpinnerEnabled:NO];
    
    m_displayed = false;
    m_pConfirmedHandlerInstance = nil;
    m_confirmedHandler = nil;
    self.pConfirmButton.hidden = NO;
    self.pCloseButton.hidden = NO;
    
    [self removeFromSuperview];
}

- (void) setSpinnerEnabled:(bool)enabled
{
    [self.pSpinner setHidden:!enabled];
    
    if(enabled)
    {
        [self.pSpinner startAnimating];
    }
    else
    {
        [self.pSpinner stopAnimating];
    }
}

- (void)handleCloseClicked
{
    [self resetState];
}

- (void)handleConfirmClicked
{
    self.pConfirmButton.hidden = YES;
    self.pCloseButton.hidden = YES;
    
    const double minimumAsyncDelaySeconds = 3.0;
    m_cacheClearDialogMinimumEndTimeSeconds = [[NSDate date] timeIntervalSince1970] + minimumAsyncDelaySeconds;
    
    self.pTitleLabel.text = @"Remove Stored Data";
    self.pMessageContent.text = @"Please wait, this may take a while...";
    [self setSpinnerEnabled:YES];
    [self->m_pConfirmedHandlerInstance performSelector:self->m_confirmedHandler];
}

@end

