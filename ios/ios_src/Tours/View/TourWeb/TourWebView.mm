// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "TourWebView.h"
#include "UIColors.h"
#include "App.h"
#include "ImageHelpers.h"

@implementation TourWebView

- (id) initWithParams:(float)width :(float)height :(float)pixelScale
{
    if (self = [super init])
    {
        BOOL isPhone = App::IsDeviceSmall();
        float percentOfScreenUse = isPhone ? 0.75f : 0.8f;
        float spacing = 10.0f;
        float buttonSize = 64;
        
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_pixelScale = pixelScale;
        
        self.frame = CGRectMake(0, 0, m_screenWidth, m_screenHeight);
        
        const float windowWidth = isPhone ? m_screenWidth : m_screenWidth * percentOfScreenUse;
        const float windowHeight = m_screenHeight * percentOfScreenUse;
        float windowX = m_screenWidth * 0.5f - windowWidth * 0.5f;
        float windowY = isPhone ? m_screenHeight - windowHeight : m_screenHeight * 0.5f - windowHeight * 0.5f;
        
        m_frameOn = CGRectMake(windowX,
                               windowY,
                               windowWidth,
                               windowHeight);
        m_frameOff = m_frameOn;
        m_frameOff.origin.y = m_screenHeight;
        
        self.backgroundColor = [UIColor colorWithRed:0.0f green:0.0f blue:0.0f alpha:0.5f];
        
        self.pWebView = [[UIWebView alloc] initWithFrame:m_frameOff];
        self.pWebView.layer.borderColor = ExampleApp::Helpers::ColorPalette::GoldTone.CGColor;
        self.pWebView.layer.borderWidth = 4.0f;
        self.pWebView.backgroundColor = [UIColor whiteColor];
        self.pWebView.scalesPageToFit = YES;
        [self addSubview:self.pWebView];
        [self setHidden:YES];
        self.alpha = 0.0f;
        
        m_tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapped:)];
        [m_tapGestureRecogniser setDelegate:self];
        [self addGestureRecognizer: m_tapGestureRecogniser];
        
        self.pBackButton = [[UIButton alloc] initWithFrame:CGRectMake(spacing, windowHeight - (spacing + buttonSize), buttonSize, buttonSize)];
        [self.pBackButton setImage:ExampleApp::Helpers::ImageHelpers::LoadImage("Tours/browser_back") forState:UIControlStateNormal];
        [self.pWebView addSubview:self.pBackButton];
        
        self.pForwardButton = [[UIButton alloc] initWithFrame:CGRectMake(spacing * 2 + buttonSize, windowHeight - (spacing + buttonSize), buttonSize, buttonSize)];
        [self.pForwardButton setImage:ExampleApp::Helpers::ImageHelpers::LoadImage("Tours/browser_forward") forState:UIControlStateNormal];
        [self.pWebView addSubview:self.pForwardButton];
        
        self.pWebView.delegate = self;
        
        [self updateButtons];
        
        [self.pBackButton addTarget:self action:@selector(handleBackButtonClicked) forControlEvents:UIControlEventTouchUpInside];
        [self.pForwardButton addTarget:self action:@selector(handleForwardButtonClicked) forControlEvents:UIControlEventTouchUpInside];
                         
    }
    return self;
}

- (void)dealloc
{
    [self.pBackButton removeFromSuperview];
    [self.pBackButton release];
    
    [self.pForwardButton removeFromSuperview];
    [self.pForwardButton release];
    
    [self removeGestureRecognizer:m_tapGestureRecogniser];
    [m_tapGestureRecogniser release];
    m_tapGestureRecogniser = nil;
    
    [self.pWebView removeFromSuperview];
    [self.pWebView release];
    
    [self removeFromSuperview];
    [self release];
    
    [super dealloc];
}

- (void) updateButtons
{
    self.pBackButton.enabled = self.pWebView.canGoBack;
    self.pBackButton.hidden = !self.pWebView.canGoBack;
    
    self.pForwardButton.enabled = self.pWebView.canGoForward;
    self.pForwardButton.hidden = !self.pWebView.canGoForward;
}

- (void)layoutSubviews
{
    self.pWebView.layer.shadowRadius = 5.0f;
    self.pWebView.layer.shadowColor = [UIColor blackColor].CGColor;
    self.pWebView.layer.shadowOffset = CGSizeMake(0.0f, 2.0f);
    self.pWebView.layer.shadowOpacity = 0.5f;
    self.pWebView.layer.shadowPath = [UIBezierPath bezierPathWithRect:self.pWebView.bounds].CGPath;
    self.pWebView.layer.masksToBounds = NO;
    
    [super layoutSubviews];
}

- (void)show:(const std::string &)urlString
{
    NSString* urlStr = [NSString stringWithUTF8String:urlString.c_str()];
    NSURL* url = [NSURL URLWithString:urlStr];
    [self.pWebView loadRequest:[NSURLRequest requestWithURL:url]];
    
    [self setHidden:NO];
    
    [UIView animateWithDuration:0.5f animations:^{
        self.pWebView.frame = m_frameOn;
        self.alpha = 1.0f;
    }];
}

- (void) hide
{
    [UIView animateWithDuration:0.5f animations:^{
        self.pWebView.frame = m_frameOff;
        self.alpha = 0.0f;
    } completion:^(BOOL finished) {
        [self setHidden:YES];
        [self.pWebView loadHTMLString:@"" baseURL:nil];
    }];
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return !self.isHidden && CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) onTapped:(UITapGestureRecognizer *)recognizer
{
    [self hide];
}

- (void) webViewDidStartLoad:(UIWebView *)webView
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    [self updateButtons];
}

- (void) webViewDidFinishLoad:(UIWebView *)webView
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    [self updateButtons];
}

- (void) webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    [self updateButtons];
}

- (void) handleBackButtonClicked
{
    if(self.pWebView.canGoBack)
    {
        [self.pWebView goBack];
    }
}

- (void) handleForwardButtonClicked
{
    if(self.pWebView.canGoForward)
    {
        [self.pWebView goForward];
    }
}

@end
