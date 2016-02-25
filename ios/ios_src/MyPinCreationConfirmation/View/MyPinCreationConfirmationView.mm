// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationConfirmationView.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "MyPinCreationConfirmationViewInterop.h"

#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"

@implementation MyPinCreationConfirmationView

- (ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewInterop*) getInterop
{
    return m_pInterop;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale
{
    if (self = [super init])
    {
        m_stateChangeAnimationTimeSeconds = 0.2f;
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;

        m_pInterop = new ExampleApp::MyPinCreation::View::MyPinCreationConfirmationViewInterop(self);
        
        const float containerWidth = 320.f;
        const float containerHeight = 40.f;

        m_yPosInactive = m_screenHeight + containerHeight;
        m_yPosActive = m_screenHeight - containerHeight;

        self.frame = CGRectMake((m_screenWidth * 0.5f) - (containerWidth * 0.5f),
                                m_screenHeight - containerHeight,
                                containerWidth,
                                containerHeight);

        const float buttonSize = containerHeight;

        // cancel button
        self.pCancelButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, buttonSize, buttonSize)] autorelease];
        [self.pCancelButton setDefaultStatesWithImageNames:@"button_close_place_pin_off" :@"button_close_place_pin_on"];
        [self.pCancelButton addTarget:self action:@selector(onCancelButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self addSubview: self.pCancelButton];

        // confirm button
        self.pConfirmButton = [[[UIButton alloc] initWithFrame: CGRectMake(containerWidth - buttonSize, 0, buttonSize, buttonSize)] autorelease];
        [self.pConfirmButton setDefaultStatesWithImageNames:@"button_ok_place_pin_off" :@"button_ok_place_pin_on"];
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
    float newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;

    self.hidden = onScreenState == 0.0f;
    CGRect f = self.frame;
    f.origin.y = newY;
    self.frame = f;
}

- (void) setFullyOnScreen
{
    if(self.frame.origin.y == m_yPosActive)
    {
        return;
    }

    [self animateToY:m_yPosActive];
}

- (void) setFullyOffScreen
{
    if(self.frame.origin.y == m_yPosInactive)
    {
        return;
    }

    [self animateToY:m_yPosInactive];
}

- (void) animateToY:(float)y
{
    CGRect f = self.frame;
    f.origin.y = y;

    if(y != m_yPosInactive)
    {
        self.hidden = false;
    }

    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
     animations:^
    {
        self.frame = f;
    }
    completion:^(BOOL finished)
    {
        self.hidden = (y == m_yPosInactive);
    }
    ];
}

@end