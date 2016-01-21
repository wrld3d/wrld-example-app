// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import "CustomTableView.h"
#import <UIKit/UIKit.h>

@interface CustomTableViewCell : UITableViewCell
{
    bool m_hasSeparator;
    CGFloat m_initialWidth;
    CGFloat m_leftInset;
    UIColor* m_pBackgroundColor;
    UIColor* m_pContentBackgroundColor;
    UIColor* m_pPressColor;
    CGRect m_imageFrame;
    CGRect m_textFrame;
    CGRect m_detailTextFrame;
    CustomTableView* m_tableView;
    UITableViewController<UITableViewDelegate>* m_tableDataProvider;
    int m_row;
    int m_section;
}

- (void)setInfo :(bool)hasSeparator
                :(UIColor*)pBackgroundColor
                :(UIColor*)pContentBackgroundColor
                :(UIColor*)pPressColor;

- (void)initCell:(CGFloat)initialWidth
                :(CGFloat)leftInset
                :(NSIndexPath *)indexPath
                :(CustomTableView*)tableView
                :(UITableViewController<UITableViewDelegate>*)tableDataProvider;

- (void)setContentFrames:(CGRect)imageFrame
                        :(CGRect)textFrame
                        :(CGRect)detailTextFrame;

- (void)layoutSubviews;

- (BOOL)canInteract;

- (bool)requiresVisualRefresh;

- (CGRect)getContentViewRect;

@end
