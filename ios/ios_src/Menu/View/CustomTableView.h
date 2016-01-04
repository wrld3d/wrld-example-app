// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

@class MenuView;

@interface CustomTableView : UITableView

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style
                    container:(UIScrollView*)container
                         menuView:(MenuView*)menuView
                  hasSubMenus:(bool)hasSubMenus;

- (BOOL)hasDynamicCellPresentation;

- (BOOL)isAnimating;

- (void)updateAnimation:(double)deltaSeconds;

@property (nonatomic, retain) UIView* pBackgroundView;

@end
