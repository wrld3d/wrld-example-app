// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CustomImagePickerController.h"

@implementation CustomImagePickerController

- (void) viewDidLoad
{
    [super viewDidLoad];
    NSLog(@"Custom viewDidLoad");
    
//    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7) {
//        CGRect viewBounds = [self.view bounds];
//        viewBounds.origin.y = -20;
////        viewBounds.size.height = viewBounds.size.height - 20;
//        self.view.frame = viewBounds;
//    }
    
    CGRect viewBounds = [self.view bounds];
    viewBounds.origin.y = -20;
    [self.view setBounds: viewBounds];
    
    self.view.backgroundColor = [UIColor blackColor];
}

@end