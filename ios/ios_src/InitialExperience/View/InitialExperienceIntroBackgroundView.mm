// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroBackgroundView.h"
#include "InitialExperienceIntroViewInterop.h"
#include "App.h"

@implementation InitialExperienceIntroBackgroundView

- (id) initView
{
    self = [super init];
    
    if(self)
    {
        m_animationTimeSeconds = 0.6f;
        
        self.pBackground = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pBackground.backgroundColor = [[UIColor alloc] initWithRed:0.f green:0.0f blue:0.0f alpha:0.5f];
        [self addSubview: self.pBackground];
        
        [self setHidden:YES];
    }
    
    return self;
}

- (void)dealloc
{
    [self.pBackground removeFromSuperview];
    [self.pBackground release];
    
    [super dealloc];
}

- (void) layoutSubviews
{
    m_screenWidth = self.superview.bounds.size.width;
    m_screenHeight = self.superview.bounds.size.height;
    [self setFrame:CGRectMake(0, 0, m_screenWidth, m_screenHeight)];
    [self.pBackground setFrame:CGRectMake(0, 0, m_screenWidth, m_screenHeight)];

}

- (void) show
{
    [self setHidden:NO];
    self.pBackground.alpha = 0.0f;
    
    [UIView animateWithDuration:m_animationTimeSeconds
                          delay:0.0
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pBackground.alpha = 1.0f;
                     }
                     completion:nil];
    
    [self setNeedsLayout];
    [self layoutIfNeeded];
}

- (void) dismiss
{
    self.pBackground.alpha = 1.0f;
    [UIView animateWithDuration:m_animationTimeSeconds
                          delay:0.0
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pBackground.alpha = 0.0f;
                     }
                     completion:^(BOOL finished){
                         [self setHidden:YES];
                         [self setNeedsLayout];
                         [self layoutIfNeeded];
                     }];
}

- (BOOL) consumesTouch:(UITouch *)touch
{
    return ![self isHidden];
}

@end