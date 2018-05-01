// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

@interface HeaderView : UIControl
-(instancetype) initWithWidth:(CGFloat)width title:(NSString*)title;
@property (nonatomic) CGFloat width;
@property (nonatomic,readonly) CGFloat margin;
@property (nonatomic,readonly) CGFloat seperatorMargin;
@property (nonatomic, retain) UIView* pHeaderSeparator;
@property (nonatomic,retain) UIButton* pCloseButton;
@property (nonatomic, retain) UILabel* pTitleLabel;
@end
