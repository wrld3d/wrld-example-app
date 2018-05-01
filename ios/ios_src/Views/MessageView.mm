// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#import "UIColors.h"
#import "HeaderView.h"
#import "MessageView.h"

@interface MessageView()
    @property (nonatomic,retain) UIButton *pCloseButton;
@end

@implementation MessageView

-(instancetype) initWithFrame:(CGRect)frame title:(NSString *)title message:(NSString *)message{
    self =  [super initWithFrame:frame];
    
    if (self) {
        self.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        self.pHeaderView = [[[HeaderView alloc] initWithWidth:frame.size.width title:title] autorelease];
        [self addSubview:self.pHeaderView];
        [self.pHeaderView addTarget:self action:@selector(onCloseButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
       
        self.pMessageLabel = [[[UILabel alloc] initWithFrame:CGRectZero] autorelease];
        self.pMessageLabel.text = message;
        self.pMessageLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pMessageLabel.numberOfLines = 0;
        self.pMessageLabel.font = [UIFont systemFontOfSize:18.0f];
        [self addSubview:self.pMessageLabel];
        [self.pMessageLabel sizeToFit];
    }
    
    return self;
}

-(void) layoutSubviews {
    self.pHeaderView.width = self.bounds.size.width;
    [self.pHeaderView layoutIfNeeded];
    [super layoutSubviews];
    self.pMessageLabel.frame = CGRectMake(self.pHeaderView.margin, self.pHeaderView.frame.size.height + 60, self.bounds.size.width - 2.0*self.pHeaderView.margin,100);
    [self.pMessageLabel sizeToFit];
    
}

- (void)dealloc
{
    [super dealloc];
    
    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];
    
    [self.pMessageLabel removeFromSuperview];
    [self.pMessageLabel release];
    
}

-(void)show {
    if(self.hidden){
        self.alpha = 0.0;
    }
    [UIView animateWithDuration:0.3 animations:^{
        self.alpha = 1.0;
        self.hidden = NO;
    }];
}

-(void)hide {
    [UIView animateWithDuration:0.3 animations:^{
        self.alpha = 0.0;
    }
     completion:^(BOOL finished) {
         if(finished) {
             self.hidden = YES;
         }
     }
     ];
}

-(void) onCloseButtonTapped:(id *) sender {
    [self sendActionsForControlEvents:UIControlEventTouchUpInside];
    [self hide];
}
@end
