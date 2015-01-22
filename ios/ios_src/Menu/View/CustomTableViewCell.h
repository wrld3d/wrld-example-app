// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import "CustomTableView.h"
#import <UIKit/UIKit.h>

@interface CustomTableViewCell : UITableViewCell
{
    bool m_rightAlignFrame;
    bool m_rightAlignImage;
    bool m_isHeader;
    float m_initialWidth;
    CustomTableView* m_tableView;
}

- (void)setAlignInfo:(bool)rightAlignFrame :(bool)rightAlignImage :(bool)isHeader;

- (void)initCell:(CGFloat)initialWidth :(CustomTableView*)tableView;

- (void)layoutSubviews;

- (BOOL)canInteract;

@end
