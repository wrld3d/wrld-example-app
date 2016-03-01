// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonView.h"
#include "FlattenButtonViewInterop.h"
#include "MathFunc.h"
#include "ImageHelpers.h"

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
        [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_flatten_off") forState:UIControlStateNormal];
        [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_flatten_on") forState:UIControlStateHighlighted];
        [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_unflatten_off") forState:UIControlStateSelected];
        [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_unflatten_on") forState:UIControlStateSelected | UIControlStateHighlighted];

        m_width = 64 * m_pixelScale;
        m_height = 64 * m_pixelScale;
        
        m_yPosBase = m_yPosActive = m_screenHeight - (8 * m_pixelScale) - m_height;
        m_yPosInactive = m_screenHeight + m_height;
        
        self.frame = CGRectMake(((m_screenWidth * 0.5f) - (m_width + (m_width * 0.5f) + 16.f)), m_yPosInactive, m_width, m_height);
        
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        self.hidden = YES;
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

