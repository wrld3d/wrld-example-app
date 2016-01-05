// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import "CustomTableView.h"
#import <UIKit/UIKit.h>

@interface CustomTableViewCell : UITableViewCell
{
    bool m_isHeader;
    float m_initialWidth;
    float m_inset;
    UIColor* m_pBackgroundColor;
    UIColor* m_pContentBackgroundColor;
    CustomTableView* m_tableView;
}

- (void)setInfo :(bool)isHeader
                :(UIColor*)pBackgroundColor
                :(UIColor*)pContentBackgroundColor;

- (void)initCell:(CGFloat)initialWidth
                :(CGFloat)inset
                :(CustomTableView*)tableView;

- (void)layoutSubviews;

- (BOOL)canInteract;

- (bool)requiresVisualRefresh;

- (CGRect)getContentViewRect;

@end
