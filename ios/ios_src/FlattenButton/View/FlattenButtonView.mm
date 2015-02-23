// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonView.h"
#include "FlattenButtonViewInterop.h"
#include "MathFunc.h"
#include "ScaleHelpers.h"

@implementation FlattenButtonView

- (ExampleApp::FlattenButton::View::FlattenButtonViewInterop *)getInterop
{
    return m_pInterop;
}

- (id) initWithDimensions:(float)width :(float)height :(float)pixelScale
{
    if(self = [super init])
    {
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;

        m_pInterop = new ExampleApp::FlattenButton::View::FlattenButtonViewInterop(self);
        [self addTarget:self action:@selector(onClick:) forControlEvents:UIControlEventTouchUpInside];
        [self setBackgroundImage:[UIImage imageNamed:@"button_streets_off.png"] forState:UIControlStateNormal];
        [self setBackgroundImage:[UIImage imageNamed:@"button_streets_on.png"] forState:UIControlStateSelected];

        float iphoneTweakScale = ExampleApp::Helpers::ScaleHelpers::GetScaleTweakValue();

        m_width = 60 * m_pixelScale * iphoneTweakScale;
        m_height = 60 * m_pixelScale * iphoneTweakScale;

        m_xPosActive = 0;
        m_xPosInactive = -m_width;

        [self setBounds: CGRectMake(0, 0, m_width, m_height)];
        [self setCenter: CGPointMake(m_xPosInactive, m_screenHeight * 0.5f)];

        m_stateChangeAnimationTimeSeconds = 0.2f;
    }

    return self;
}


- (void)dealloc
{
    delete m_pInterop;
    [super dealloc];
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) onClick:(UIButton *)sender
{
    [sender setSelected:!sender.selected];
    m_pInterop->OnToggle(sender.selected);
}

- (void) setFullyOnScreen
{
    if(self.frame.origin.x == m_xPosActive)
    {
        return;
    }

    [self animateToX:m_xPosActive];
}

- (void) setFullyOffScreen
{
    if(self.frame.origin.x == m_xPosInactive)
    {
        return;
    }

    [self animateToX:m_xPosInactive];
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    float newX = m_xPosInactive + abs(m_xPosActive - m_xPosInactive) * onScreenState;

    self.hidden = false;
    CGRect f = self.frame;
    f.origin.x = newX;
    self.frame = f;
}

- (void) animateToX:(float)x
{
    CGRect f = self.frame;
    f.origin.x = x;

    if(x != m_xPosInactive)
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
        self.hidden = (x == m_xPosInactive);
    }
    ];
}

@end

