// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "ImmediatePanGestureRecognizer.h"
#import <UIKit/UIGestureRecognizerSubclass.h>

@implementation ImmediatePanGestureRecognizer

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    if(self.state >= UIGestureRecognizerStateBegan)
    {
        return;
    }
    
    [super touchesBegan:(NSSet*)touches withEvent:(UIEvent*) event];
    self.state = UIGestureRecognizerStateBegan;
}

@end
