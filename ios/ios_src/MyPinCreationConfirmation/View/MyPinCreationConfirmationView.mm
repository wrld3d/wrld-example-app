// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationView.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "MyPinCreationConfirmationViewInterop.h"
#include "ViewController.h"
#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"

@implementation MyPinCreationConfirmationView

- (ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewInterop*) getInterop
{
    return m_pInterop;
}

- (instancetype) initWithScreenWidth:(CGFloat)width screenHeight:(CGFloat)height
{
    if (self = [super init])
    {
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        m_screenWidth = width;
        m_screenHeight = height;

        m_pInterop = new ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewInterop(self);
        
        UIViewController *viewController = [UIApplication sharedApplication].delegate.window.rootViewController;
        UIEdgeInsets safeInsets = [viewController safeInsets];
        
        UIEdgeInsets margin =  UIEdgeInsetsMake(16, 16, 16, 16);
        CGFloat maxContainerWidth = 400;
        const float containerWidth = MIN( m_screenWidth - margin.left - margin.right, maxContainerWidth );
        const float containerHeight = 40.f;
        
        self.frame = CGRectMake(0.5*(m_screenWidth  - containerWidth),
                                m_screenHeight - containerHeight - margin.bottom - safeInsets.bottom,
                                containerWidth,
                                containerHeight);
        
        m_offscreen_offset = m_screenHeight - self.frame.origin.y;
        const float buttonSize = containerHeight;

        // cancel button
        self.pCancelButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, buttonSize, buttonSize)] autorelease];
        [self.pCancelButton setDefaultStatesWithNormalImageName:@"button_close_place_pin_off"
                                             highlightImageName:@"button_close_place_pin_off"
                                          normalBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor
                                       highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColorAlt];
        [self.pCancelButton addTarget:self action:@selector(onCancelButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview: self.pCancelButton];

        // confirm button
        self.pConfirmButton = [[[UIButton alloc] initWithFrame: CGRectMake(containerWidth - buttonSize, 0, buttonSize, buttonSize)] autorelease];
        [self.pConfirmButton setDefaultStatesWithNormalImageName:@"button_ok_place_pin_off"
                                              highlightImageName:@"button_ok_place_pin_off"
                                           normalBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColor
                                        highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::ButtonPressColorAlt];
        [self.pConfirmButton addTarget:self action:@selector(onOkayButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview: self.pConfirmButton];
        
        // main section with text
        const float mainSectionWidth = containerWidth - (buttonSize * 2.f);
        self.pMainSection = [[[UIView alloc] initWithFrame: CGRectMake(buttonSize, 0.f, mainSectionWidth, containerHeight)] autorelease];
        [self.pMainSection setBackgroundColor: [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"place_pin_background")]];
        
        const float textPadding = 2.f;
        self.pTitleBarText = [[[UILabel alloc] initWithFrame: CGRectMake(textPadding,
                                                                         textPadding,
                                                                         mainSectionWidth - textPadding,
                                                                         containerHeight - textPadding)] autorelease];
        
        self.pTitleBarText.font = [UIFont systemFontOfSize:13.0f];
        self.pTitleBarText.text = @"Drag the marker to place your pin";
        self.pTitleBarText.textAlignment = NSTextAlignmentCenter;
        self.pTitleBarText.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        
        [self.pMainSection addSubview: self.pTitleBarText];
        [self addSubview: self.pMainSection];
        
        [self setHidden:YES];
        [self setTouchExclusivity: self];
    }

    return self;
}

- (void)dealloc
{
    delete m_pInterop;

    [self.pCancelButton removeFromSuperview];
    [self.pCancelButton release];

    [self.pConfirmButton removeFromSuperview];
    [self.pConfirmButton release];

    [self.pTitleBarText removeFromSuperview];
    [self.pTitleBarText release];
    
    [self.pMainSection removeFromSuperview];
    [self.pMainSection release];

    [self removeFromSuperview];
    [super dealloc];
}

- (void) onCancelButtonPressed:(UIButton *)sender
{
    m_pInterop->OnDismissed();
}

- (void) onOkayButtonPressed:(UIButton *)sender
{
    m_pInterop->OnConfirmed();
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    self.hidden = onScreenState == 0.0f;
    CGFloat offScreenState = 1.0 - onScreenState;
    
    self.transform = CGAffineTransformMakeTranslation(0.0, m_offscreen_offset*offScreenState);
}

- (void) setFullyOnScreen
{
    self.hidden = false;
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^{ self.transform = CGAffineTransformIdentity;}];
}

- (void) setFullyOffScreen
{
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^{ self.transform = CGAffineTransformMakeTranslation(0.0, m_offscreen_offset);}
                     completion:^(BOOL finished){ self.hidden = true;}];
   
}

@end
