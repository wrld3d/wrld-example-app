// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

typedef void(^OnAnimationComplete)(void);

@interface CustomTableView : UITableView

- (instancetype)initWithFrame:(CGRect)frame
                        style:(UITableViewStyle)style
                    container:(UIScrollView*)container
                  hasSubMenus:(bool)hasSubMenus
                  onRowsAdded:(OnAnimationComplete)onRowsAdded
                onRowsDeleted:(OnAnimationComplete)onRowsDeleted;

-(BOOL)hasDynamicCellPresentation;

-(BOOL)inAnimationCeremony;

@end
