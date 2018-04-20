//
//  MessageView.h
//  ProjectSwallowApp
//
//  Created by David Crooks on 21/02/2018.
//
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
