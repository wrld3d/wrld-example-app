// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#pragma once
#import <UIKit/UIKit.h>
#import "HeaderView.h"
@interface MessageView : UIControl
-(instancetype) initWithFrame:(CGRect)frame title:(NSString *)title message:(NSString *)message;
@property (nonatomic, retain) UILabel* pMessageLabel;
@property (nonatomic, retain) HeaderView* pHeaderView;
-(void)show;
-(void)hide;
@end
