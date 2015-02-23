// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

@interface CustomTableView : UITableView

- (instancetype)initWithFrame:(CGRect)frame style:(UITableViewStyle)style container:(UIScrollView*)container;

-(BOOL)inAnimationCeremony;

@end
