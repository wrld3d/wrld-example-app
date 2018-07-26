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
        
        self.pHeaderView = [[[HeaderView alloc] initWithWidth:200 title:@"Remove Stored Data"] autorelease];
        [self addSubview:self.pHeaderView];
        self.pHeaderView.pTitleLabel.font = [UIFont systemFontOfSize:23.f];
        
        [self.pHeaderView addTarget:self action:@selector(handleCloseClicked) forControlEvents:UIControlEventTouchUpInside];
        
        self.pCancelButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCancelButton setTitle:@"No" forState:UIControlStateNormal];
        [self.pCancelButton setDefaultStatesWithNormalImageName:@""
                                             highlightImageName:@""
                                          normalBackgroundColor:ExampleApp::Helpers::ColorPalette::UiBackgroundColor
                                       highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor];
        [self.pCancelButton setTitleColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor
                                 forState:UIControlStateNormal];
        [self.pCancelButton setTitleColor:ExampleApp::Helpers::ColorPalette::UiBackgroundColor
                                 forState:UIControlStateHighlighted];
        self.pCancelButton.layer.borderWidth = 1.0f;
        self.pCancelButton.layer.borderColor = ExampleApp::Helpers::ColorPalette::UiBorderColor.CGColor;
        
        [self.pCancelButton addTarget:self action:@selector(handleCancelClicked) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview: self.pCancelButton];
        
        self.pConfirmButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pConfirmButton setTitle:@"Yes" forState:UIControlStateNormal];
        [self.pConfirmButton setDefaultStatesWithNormalImageName:@""
                                              highlightImageName:@""
                                           normalBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor
                                        highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColorAlt];
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
    
    [self.pCancelButton removeFromSuperview];
    [self.pCancelButton release];
    
    [self.pConfirmButton removeFromSuperview];
    [self.pConfirmButton release];
    
    [self.pSpinner removeFromSuperview];
    [self.pSpinner release];
    
    [self.pWarningLabel removeFromSuperview];
    [self.pWarningLabel release];
    
    [self.pMessageContent removeFromSuperview];
    [self.pMessageContent release];
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void)layoutSubviews
{
    
    CGFloat mainWindowWidth = self.frame.size.width;
    CGFloat mainWindowHeight = self.frame.size.height;
    self.pHeaderView.width = mainWindowWidth;
    [self.pHeaderView layoutIfNeeded];
    CGFloat seperatorMargin = self.pHeaderView.pHeaderSeparator.frame.origin.x;
    UIEdgeInsets outerMargin = UIEdgeInsetsMake(seperatorMargin, seperatorMargin, seperatorMargin, seperatorMargin);
    UIEdgeInsets innerMargin = UIEdgeInsetsMake(self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin);
    CGFloat innerMarginWidth = mainWindowWidth - innerMargin.left - innerMargin.right;
    CGFloat contentY = self.pHeaderView.frame.origin.y +  self.pHeaderView.frame.size.height;
    
    self.pWarningLabel.font = [UIFont systemFontOfSize:24.0f];
    [self.pWarningLabel sizeToFit];
    CGFloat warningLableHeight = self.pWarningLabel.frame.size.height;
    self.pWarningLabel.frame = CGRectMake(innerMargin.left,
                                          contentY + outerMargin.bottom + innerMargin.top,
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
    self.pHeaderView.pCloseButton.hidden = NO;
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
    self.pHeaderView.pCloseButton.hidden = YES;
    
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
    self.pHeaderView.pCloseButton.hidden = YES;
    
    const double minimumAsyncDelaySeconds = 3.0;
    m_cacheClearDialogMinimumEndTimeSeconds = [[NSDate date] timeIntervalSince1970] + minimumAsyncDelaySeconds;
    
    self.pWarningLabel.text = @"";
    self.pMessageContent.text = @"Please wait, this may take a while...";
    [self setSpinnerEnabled:YES];
    [m_pConfirmedHandlerInstance performSelector:m_confirmedHandler];
}

@end

