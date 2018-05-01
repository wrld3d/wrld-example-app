//
//  CustomSwitch.h
//  
//
//  Created by David Crooks on 29/01/2018.
//

#import <UIKit/UIKit.h>

@interface CustomSwitch :UIControl

- (id) initWithOnImage:(UIImage *)onImage offImage:(UIImage *)offImage;

///A Boolean value that determines the off/on state of the switch.
@property (nonatomic,readonly) bool isOn;

///Set the state of the switch to On or Off, optionally animating the transition.
-(void) setOn:(bool)on  animated: (bool)animated;

-(void) setOn:(bool)on;

@end
