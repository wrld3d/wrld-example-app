//
//  CustomSwitch.m
//  
//
//  Created by David Crooks on 29/01/2018.
//

#import "CustomSwitch.h"

@interface CustomSwitch()
    @property (nonatomic,retain) UIButton *button;
@end

@implementation CustomSwitch{
    bool _isOn;
}


- (id) initWithOnImage:(UIImage *) onImage offImage:(UIImage *) offImage
{
    self = [super init];
    
    if(self)
    {
        _isOn = false;
        
        self.button = [[UIButton alloc] init];
        [self.button addTarget:self action:@selector(handelTap:) forControlEvents:UIControlEventTouchUpInside];
        [self.button setImage:offImage forState:UIControlStateNormal];
        [self.button setImage:onImage forState:UIControlStateSelected];
        [self addSubview:self.button];
        self.button.selected = _isOn;
        self.selected = _isOn;
        
        [self setNeedsLayout];
    }
    
    return self;
}

- (void)dealloc
{
    [super dealloc];
    
    [self.button removeFromSuperview];
    [self.button release];
}

-(void)layoutSubviews {
    [super layoutSubviews];
    self.button.frame = self.bounds;
}

-(void) setOn:(bool)on  animated: (bool)animated{
    _isOn = on;
    self.button.selected = _isOn;
    self.selected = _isOn;
}

-(void) setOn:(bool)on {
    [self setOn:on animated:true];
}

-(bool) isOn {
    return _isOn;
}

-(void) handelTap:(id *) sender {
    [self setOn:!self.isOn animated:true];
    [self sendActionsForControlEvents:UIControlEventValueChanged];
}

@end
