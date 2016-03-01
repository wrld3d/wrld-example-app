// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationInitiationView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "MyPinCreationInitiationViewInterop.h"

@implementation MyPinCreationInitiationView

- (ExampleApp::MyPinCreation::View::MyPinCreationInitiationViewInterop *)getInterop
{
    return m_pInterop;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale
{
    if(self = [super init])
    {
        m_stateChangeAnimationTimeSeconds = 0.2f;
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;

        m_pInterop = new ExampleApp::MyPinCreation::View::MyPinCreationInitiationViewInterop(self);

        m_width = 64 * m_pixelScale;
        m_height = m_width;
        m_yPosBase = m_yPosActive = m_screenHeight - (8 * m_pixelScale) - m_height;
        m_yPosInactive = m_screenHeight + m_height;
        self.frame = CGRectMake(((m_screenWidth * 0.5f) + (m_width*0.5f) + 16.f), m_yPosInactive, m_width, m_height);

        self.pPoiCreateButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pPoiCreateButton];

        [self.pPoiCreateButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_create_poi_off") forState:UIControlStateNormal];
        [self.pPoiCreateButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_create_poi_on") forState:UIControlStateHighlighted];
        self.pPoiCreateButton.frame = CGRectMake(0.f, 0.f, m_width, m_height);
        [self.pPoiCreateButton addTarget:self action:@selector(onClick:) forControlEvents:UIControlEventTouchUpInside];
        
        self.hidden = YES;
    }

    return self;
}

- (void) onClick:(UIButton *)sender
{
    m_pInterop->OnSelected();
}

- (void)dealloc
{
    delete m_pInterop;

    [self.pPoiCreateButton removeFromSuperview];
    [self.pPoiCreateButton release];

    [super dealloc];
}

- (void)layoutSubviews
{

}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) setFullyOnScreen
{
    self.hidden = NO;
    
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

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    float newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;

    self.hidden = false;
    CGRect f = self.frame;
    f.origin.y = newY;
    self.frame = f;
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

