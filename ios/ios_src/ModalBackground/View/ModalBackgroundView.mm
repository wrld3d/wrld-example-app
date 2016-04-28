// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ModalBackgroundViewInterop.h"

@implementation ModalBackgroundView

- (id)initWithParams:(float)screenWidth :(float)screenHeight
{
    self = [super init];

    if(self)
    {
        m_pInterop = Eegeo_NEW(ExampleApp::ModalBackground::View::ModalBackgroundViewInterop)(self);
        [self setFrame:CGRectMake(0, 0, screenWidth, screenHeight)];
        [self setBackgroundColor: ExampleApp::Helpers::ColorPalette::ModalBackgroundColor];
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        m_isAnimating = false;
        
        m_tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapGesture:)] autorelease];
        [m_tapGestureRecogniser setDelegate:self];
        
        [self addGestureRecognizer:m_tapGestureRecogniser];
    }

    return self;
}

- (void)dealloc
{
    Eegeo_DELETE m_pInterop;

    [self removeGestureRecognizer:m_tapGestureRecogniser];
    [self removeFromSuperview];
    [super dealloc];
}

- (ExampleApp::ModalBackground::View::ModalBackgroundViewInterop*) getInterop
{
    return m_pInterop;
}

- (void)layoutSubviews
{
    self.alpha = 0.f;
    self.frame = self.superview.bounds;
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
    return [self isVisible];
}

- (void) animateToAlpha:(float)alpha
{
    m_isAnimating = true;
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
     animations:^
    {
        self.alpha = alpha;
    }
    completion:^(BOOL finished)
    {
        if(finished)
        {
            m_isAnimating = false;
        }
    }];
}

- (void)tapGesture:(UITapGestureRecognizer *)recognizer
{
    if(!m_isAnimating && [self isVisible])
    {
        m_pInterop->HandleViewTapped();
    }
}

- (BOOL)isVisible
{
    return self.alpha > 0.0f;
}

@end
