// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorStreamingDialogSpinner.h"

const float SpinnerPeriod = 2.0f;

@interface InteriorStreamingDialogSpinner()
{
    BOOL isAnimating;
}

@end

@implementation InteriorStreamingDialogSpinner

- (id)init
{
    const float size = 62.0f;
    
    [self initWithImage:[UIImage imageNamed:@"streaming_dialog_spinner"]];
    
    self.frame = CGRectMake(0.0f,
                            0.0f,
                            size,
                            size);
    
    isAnimating = NO;
    self.hidden = YES;
    
    return self;
}

- (void)startAnimating
{
    [self stopAnimating];
    
    isAnimating = YES;
    self.hidden = NO;
    
    [self animate];
}

- (void)stopAnimating
{
    isAnimating = NO;
    self.hidden = YES;
    
    [self.layer removeAllAnimations];
}

- (void)animate
{
    // adds a 90 degree rotation
    [UIView animateWithDuration: SpinnerPeriod / 4.0f
                          delay: 0.0f
                        options: UIViewAnimationOptionCurveLinear
                     animations: ^{
                         self.transform = CGAffineTransformRotate(self.transform, static_cast<float>(M_PI / 2.0));
                     }
                     completion: ^(BOOL finished){
                         if (finished)
                         {
                             if (isAnimating)
                             {
                                 [self animate];
                             }
                         }
                     }];
}

@end
