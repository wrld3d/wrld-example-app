// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include "Types.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "OptionsCacheClearSubView.h"
#include "UIHelpers.h"

#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"

@implementation OptionsCacheClearSubView

- (id)init
{
    self = [super init];
    
    if(self)
    {
        self.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        
        self.pHeaderView = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview:self.pHeaderView];
        
        self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
        self.pTitleLabel.text = @"Remove Stored Data";
        self.pTitleLabel.font = [UIFont systemFontOfSize:24.f];
        [self.pHeaderView addSubview:self.pTitleLabel];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButton.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        self.pCloseButton.imageView.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        UIImage *closeImage = [UIImage imageNamed:@"Close_Blue"];
        [self.pCloseButton setImage:closeImage forState:UIControlStateNormal];
        [self.pCloseButton addTarget:self action:@selector(handleCloseClicked) forControlEvents:UIControlEventTouchUpInside];
        [self.pHeaderView addSubview:self.pCloseButton];
        
        self.pHeaderSeparator = [[[UIView alloc] init] autorelease];
        self.pHeaderSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
        [self addSubview:self.pHeaderSeparator];
        
        self.pCancelButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCancelButton setTitle:@"No" forState:UIControlStateNormal];
        self.pCancelButton.backgroundColor = UIColor.whiteColor;
        [self.pCancelButton setTitleColor:ExampleApp::Helpers::ColorPalette::UiBorderColor
                                 forState:UIControlStateNormal];
        self.pCancelButton.layer.borderWidth = 1.0f;
        self.pCancelButton.layer.borderColor = ExampleApp::Helpers::ColorPalette::UiBorderColor.CGColor;
        
        [self.pCancelButton addTarget:self action:@selector(handleCancelClicked) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview: self.pCancelButton];
        
        self.pConfirmButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pConfirmButton setTitle:@"Yes" forState:UIControlStateNormal];
        self.pConfirmButton.backgroundColor  = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pConfirmButton addTarget:self action:@selector(handleConfirmClicked) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview: self.pConfirmButton];
        
        self.pWarningLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pWarningLabel.textColor = UIColor.blackColor;
        self.pWarningLabel.numberOfLines = 0;
        [self addSubview: self.pWarningLabel];
        
        self.pMessageContent = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pMessageContent.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pMessageContent.numberOfLines = 0;
        [self addSubview: self.pMessageContent];
        
        self.pSpinner = [[[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pSpinner.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhiteLarge;
        self.pSpinner.color = [UIColor grayColor];
        [self addSubview: self.pSpinner];
        
        [self setTouchExclusivity:self];
        
        [self resetState];
    }
    
    return self;
}

- (void)dealloc
{
    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];
    
    [self.pHeaderSeparator removeFromSuperview];
    [self.pHeaderSeparator release];
    
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pCancelButton removeFromSuperview];
    [self.pCancelButton release];
    
    [self.pConfirmButton removeFromSuperview];
    [self.pConfirmButton release];
    
    [self.pSpinner removeFromSuperview];
    [self.pSpinner release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pWarningLabel removeFromSuperview];
    [self.pWarningLabel release];
    
    [self.pMessageContent removeFromSuperview];
    [self.pMessageContent release];
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void)layoutSubviews
{
    const CGFloat boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const CGFloat boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const CGFloat boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f) * 0.6f);
    const CGFloat mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
  
    const CGFloat mainWindowHeight = 257;
    const CGFloat mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const CGFloat mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    UIEdgeInsets outerMargin = UIEdgeInsetsMake(8.0, 8.0, 8.0, 8.0);
    UIEdgeInsets innerMargin = UIEdgeInsetsMake(20.0, 20.0, 16.0, 16.0);
    
    
    CGFloat innerMarginWidth = mainWindowWidth - innerMargin.left - innerMargin.right;
    CGFloat outerMarginWidth = mainWindowWidth - outerMargin.left - outerMargin.right;
    
    
    CGFloat headerHeight = 37;
   
    self.pHeaderView.frame = CGRectMake(innerMargin.left, outerMargin.top, innerMarginWidth,headerHeight );
    
    CGFloat centeringOffsetY = 4.0;
    self.pTitleLabel.font = [UIFont systemFontOfSize:24.f];
    self.pTitleLabel.frame = CGRectMake(0.0,centeringOffsetY, innerMarginWidth - headerHeight,headerHeight);
    [self.pTitleLabel sizeToFit];
    self.pCloseButton.frame = CGRectMake(innerMarginWidth - headerHeight,0.0, headerHeight,headerHeight);
    
    self.pHeaderSeparator.frame = CGRectMake(outerMargin.left, self.pHeaderView.frame.origin.y + self.pHeaderView.frame.size.height + outerMargin.top, outerMarginWidth,1.0);
    
    self.pWarningLabel.font = [UIFont systemFontOfSize:24.0f];
    [self.pWarningLabel sizeToFit];
    CGFloat warningLableHeight = self.pWarningLabel.frame.size.height;
    self.pWarningLabel.frame = CGRectMake(innerMargin.left,
                                          headerHeight + outerMargin.bottom + innerMargin.top,
                                          innerMarginWidth,
                                          warningLableHeight);
    
    self.pWarningLabel.textAlignment = NSTextAlignmentCenter;
    self.pWarningLabel.userInteractionEnabled = NO;
    
    self.pMessageContent.font = [UIFont systemFontOfSize:18.0f];
    self.pMessageContent.frame = CGRectMake(0.0,0.0,innerMarginWidth,mainWindowHeight);
    [self.pMessageContent sizeToFit];
    CGFloat messageLableHeight = self.pMessageContent.frame.size.height;
    self.pMessageContent.frame = CGRectMake(innerMargin.left,
                                            self.pWarningLabel.frame.origin.y + self.pWarningLabel.frame.size.height + outerMargin.top,
                                            innerMarginWidth,
                                            messageLableHeight);
    
    self.pMessageContent.textAlignment = NSTextAlignmentCenter;
    self.pMessageContent.userInteractionEnabled = NO;
    
    CGFloat buttonWidth = 0.5*(innerMarginWidth - innerMargin.left - innerMargin.right - outerMargin.left - outerMargin.right) ;
    CGFloat buttonHeight = 60;
    
    CGFloat buttonY = self.pMessageContent.frame.origin.y + messageLableHeight + innerMargin.top;
    
    self.pCancelButton.frame = CGRectMake(mainWindowWidth - innerMargin.right - outerMargin.right - buttonWidth,
                                         buttonY,
                                         buttonWidth,
                                         buttonHeight);
    
    self.pConfirmButton.frame = CGRectMake(innerMargin.left + outerMargin.left,
                                           buttonY,
                                           buttonWidth,
                                           buttonHeight);
    
    
    self.pSpinner.frame = CGRectMake(0.5*mainWindowWidth - 30.0,
                                     buttonY,
                                     60.0,
                                     60.0);
    
    [self setSpinnerEnabled:NO];
    
}

- (bool) isDisplayed
{
    return m_displayed;
}

- (void) displayWarningInView:(UIView*)view target:(id)pConfirmedHandlerInstance action:(SEL)confirmedHandler
{
    Eegeo_ASSERT(pConfirmedHandlerInstance != nil);
    Eegeo_ASSERT(confirmedHandler != nil);
    Eegeo_ASSERT(![self isDisplayed]);
    Eegeo_ASSERT(m_pConfirmedHandlerInstance == nil);
    Eegeo_ASSERT(m_confirmedHandler == nil);
    
    m_displayed = true;
    m_pConfirmedHandlerInstance = pConfirmedHandlerInstance;
    m_confirmedHandler = confirmedHandler;
    
    [view addSubview:self];
    
    self.pWarningLabel.text = @"Warning!";
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
    self.pCancelButton.hidden = NO;
    self.pCloseButton.hidden = YES;
    
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

- (void)handleCancelClicked
{
    [self resetState];
}

- (void)handleConfirmClicked
{
    self.pConfirmButton.hidden = YES;
    self.pCancelButton.hidden = YES;
    self.pCloseButton.hidden = YES;
    
    const double minimumAsyncDelaySeconds = 3.0;
    m_cacheClearDialogMinimumEndTimeSeconds = [[NSDate date] timeIntervalSince1970] + minimumAsyncDelaySeconds;
    
    self.pWarningLabel.text = @"";
    self.pMessageContent.text = @"Please wait, this may take a while...";
    [self setSpinnerEnabled:YES];
    [m_pConfirmedHandlerInstance performSelector:m_confirmedHandler];
}

@end

