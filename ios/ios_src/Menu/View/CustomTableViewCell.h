// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import "CustomTableView.h"
#import <UIKit/UIKit.h>

@interface CustomTableViewCell : UITableViewCell
{
    bool m_isHeader;
    CGFloat m_initialWidth;
    CGFloat m_leftInset;
    UIColor* m_pBackgroundColor;
    UIColor* m_pContentBackgroundColor;
    UIColor* m_pPressColor;
    CGRect m_imageFrame;
    CGRect m_textFrame;
    CGRect m_detailTextFrame;
    CustomTableView* m_tableView;
}

- (void)setInfo :(bool)isHeader
                :(UIColor*)pBackgroundColor
                :(UIColor*)pContentBackgroundColor
                :(UIColor*)pPressColor;

- (void)initCell:(CGFloat)initialWidth
                :(CGFloat)leftInset
                :(CustomTableView*)tableView;

- (void)setContentFrames:(CGRect)imageFrame
                        :(CGRect)textFrame
                        :(CGRect)detailTextFrame;

- (void)layoutSubviews;

- (BOOL)canInteract;

- (bool)requiresVisualRefresh;

- (CGRect)getContentViewRect;

@end
