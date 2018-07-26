// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#import "HeaderView.h"
#import "UIColors.h"
#import "UIButton+DefaultStates.h"

@implementation HeaderView

const CGFloat topMargin = 8.0;
const CGFloat height = 37;
const CGFloat seperatorHieght = 1;

-(instancetype) initWithWidth:(CGFloat)width title:(NSString*)title {
    self =  [super initWithFrame:CGRectMake(0.0,0.0,width,height + 1 + topMargin)];
    
    if (self) {
        self.width = width;
        self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
        self.pTitleLabel.text = title;
        self.pTitleLabel.font = [UIFont systemFontOfSize:24.f];
        [self addSubview:self.pTitleLabel];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        
        [self.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
        [self.pCloseButton addTarget:self action:@selector(onCloseButtonTapped) forControlEvents:UIControlEventTouchUpInside];
        
        [self addSubview:self.pCloseButton];
        
        self.pHeaderSeparator = [[[UIView alloc] init] autorelease];
        self.pHeaderSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
        [self addSubview:self.pHeaderSeparator];
        
    }
    
    return self;
}

-(CGFloat) margin {
    return 18;
}

-(CGFloat) seperatorMargin {
    return 8;
}

-(void) layoutSubviews{
    [super layoutSubviews];
    CGFloat centeringOffsetY = 4.0;
    
    self.frame = CGRectMake(0.0,0.0,self.width,height + self.margin + seperatorHieght);
    
    self.pTitleLabel.frame = CGRectMake(self.margin,topMargin+centeringOffsetY, 0.0 ,self.bounds.size.height);
    [self.pTitleLabel sizeToFit];
    
    self.pCloseButton.frame = CGRectMake(self.width - height - self.margin,topMargin, height,height);
    
    self.pHeaderSeparator.frame = CGRectMake(self.seperatorMargin, height + 2*topMargin, self.bounds.size.width-2*self.seperatorMargin, 1);
}

-(void) setWidth:(CGFloat)width {
    _width = width;
    
    [self setNeedsLayout];
}

- (void)dealloc
{
    [super dealloc];
    
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pHeaderSeparator removeFromSuperview];
    [self.pHeaderSeparator release];
}

-(void) onCloseButtonTapped {
    [self sendActionsForControlEvents:UIControlEventTouchUpInside];
}

@end
