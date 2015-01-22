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
        m_stateChangeAnimationTimeSeconds = 0.2;
    }

    return self;
}

- (void)dealloc
{
    Eegeo_DELETE m_pInterop;

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
    return self.alpha > 0.f;
}

- (void) animateToAlpha:(float)alpha
{
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
     animations:^
    {
        self.alpha = alpha;
    }];
}

@end
